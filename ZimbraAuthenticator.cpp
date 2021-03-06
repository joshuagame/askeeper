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
 * ZimbraAuthenticator.cpp
 * the Zimbra https client for authentication
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

#include <iostream>
#include "ZimbraAuthenticator.h"

using namespace std;

namespace askeeper {
namespace server {


/*
 * NOTE:
 *  Using Session Factory:
 *
 *  //register http and https
    HTTPSessionFactory::defaultFactory().registerProtocol("http", new HTTPSessionInstantiator);
    HTTPSessionFactory::defaultFactory().registerProtocol("https", new HTTPSSessionInstantiator);
    //prepare for SSLManager
    SharedPtr ptrCert = new AcceptCertificateHandler(false);
    const Poco::Net::Context::Ptr context = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    SSLManager::instance().initializeClient(0, ptrCert, context);
    // now you have the HTTP(S)ClientSession
    HTTPClientSession *session = HTTPSessionFactory::defaultFactory().createClientSession(uri);
 */

HTTPResponse::HTTPStatus ZimbraAuthenticator::authenticate(const string& username, const string& password)
{
    Poco::Logger& logger = Application::instance().logger();
    HTTPResponse::HTTPStatus status = HTTPResponse::HTTP_OK;
    Application& app = Application::instance();
    Context::Ptr pClientContext = new Context(Context::CLIENT_USE, "", "", "", Context::VERIFY_NONE);

    logger.information("performing Zimbra user authentication for user " + username);
    try {

        HTTPSClientSession s(app.config().getString("zimbra.host"), (Poco::UInt16)app.config().getInt("zimbra.port"), pClientContext);
        std::string baseUrl = app.config().getString("zimbra.url");
        string url(replace(baseUrl, "$username$", username.c_str()));
        logger.debug("Zimbra authentication url: " + url);


        HTTPRequest request(HTTPRequest::HTTP_GET, url);
        Poco::Net::HTTPBasicCredentials creds(username, password);


        HTTPResponse zimbraResponse;
        logger.debug("setting Zimbra credentials in request");
        creds.authenticate(request);

        logger.debug("sending authentication request to Zimbra");
        s.sendRequest(request);
        std::istream& rs = s.receiveResponse(zimbraResponse);
        logger.debug("Zimbra authentication response status: %d", zimbraResponse.getStatus());

        status = zimbraResponse.getStatus();
    } catch (Poco::Exception& e) {
        logger.error("Exception: %s - %s", e.what(), e.message());
        status = HTTPResponse::HTTP_UNAUTHORIZED;
    }

    return status;
}

}
}
