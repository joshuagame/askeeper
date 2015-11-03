/*
 *     _    ____  _  _______ _____ ____  _____ ____
 *    / \  / ___|| |/ / ____| ____|  _ \| ____|  _ \
 *   / _ \ \___ \| ' /|  _| |  _| | |_) |  _| | |_) |
 *  / ___ \ ___) | . \| |___| |___|  __/| |___|  _ <
 * /_/   \_\____/|_|\_\_____|_____|_|   |_____|_| \_\ v1.0
 * Authentication Sessions Keeper Server
 * www.codegazoline.it/askeeper
 * ===============================================================================
 * Copyright (C) 2015, Luca Stasio - joshuagame@gmail.com
 * //The CodeGazoline Team/
 *
 * BasicAuthRequestHandler.cpp
 * the http GET Basic authentication request handler
 *
 * This file is part of the ASKEEPER Server.
 *
 * The ASKEEPER Server is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The ASKEEPER Server is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nome - Programma.If not, see <http://www.gnu.org/licenses/>.
 */

#include <iterator>
#include "BasicAuthRequestHandler.h"
#include "Poco/URI.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/String.h"

using Poco::replace;

namespace askeeper {
namespace server {

void BasicAuthRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());

    if (request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials cred(request);
        const std::string& user = cred.getUsername();
        const std::string& pwd = cred.getPassword();
        std::cout << "Request Basic Credentials" << std::endl;
        std::cout << "Username: " << user << std::endl;
        std::cout << "Password: " << pwd << std::endl;

        // call Zimbra
        Context::Ptr pClientContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE);
        try {

            HTTPSClientSession s(app.config().getString("zimbra.host"), (unsigned int)app.config().getInt("zimbra.port"), pClientContext);
            string baseUrl = app.config().getString("zimbra.url");
            string url(replace(baseUrl, "$username$", user.c_str()));
            cout << "Zimbra auth url: " << url << endl;
            HTTPRequest request(HTTPRequest::HTTP_GET, url);
            Poco::Net::HTTPBasicCredentials creds(user, pwd);


            HTTPResponse response;
            cout << "Set Zimbra credentials in request" << endl;
            creds.authenticate(request);
            s.sendRequest(request);
            std::istream& rs = s.receiveResponse(response);
            cout << "Zimbra authentication response status: " << response.getStatus() << endl;

            pClientContext->release();
        } catch (Poco::Exception& e) {
            std::cerr << "Exception: " << e.what() << " - " << e.message() << std::endl;
            pClientContext->release();
        }



    } else {
        response.requireAuthentication("askeeper");
        response.setContentLength(0);
        response.send();
        return;
    }

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream& ostr = response.send();
    ostr << "{ \"status\": \"success\", \"message\": \"user authenticated\" }";
}

}
}
