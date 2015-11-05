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
#include "ZimbraAuthenticator.h"
#include "ASKServer.h"
#include "SessionsManager.h"
#include "Session.h"

using Poco::replace;
using Poco::Net::HTTPResponse;

namespace askeeper {
namespace server {

void BasicAuthRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    Application& app = Application::instance();
    app.logger().information("Request from " + request.clientAddress().toString());
//    logger->information("Request from " + request.clientAddress().toString());

    Session session = SessionsManager::instance().newSession();
//    cout << "## Session created with Session ID: " << session.id() << endl;
    app.logger().information("Session created with Session ID: " + session.id());

    Session theSession = SessionsManager::instance().getSession(session.id());
    app.logger().information("Session emplaced into the Sessions Map");

    if (request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials cred(request);
        const std::string& user = cred.getUsername();
        const std::string& pwd = cred.getPassword();
        app.logger().information("Basic Credentials: { Username: " + user + ", Password: " + pwd + " }");

        ZimbraAuthenticator zimbraAuthenticator;
        HTTPResponse::HTTPStatus status = zimbraAuthenticator.authenticate(user, pwd);

        if (status != HTTPResponse::HTTP_OK) {
            app.logger().information("AUTHENTICATTION REQUIRED");
            response.requireAuthentication("askeeper");
            response.setContentLength(0);
            response.send();
            return;
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
