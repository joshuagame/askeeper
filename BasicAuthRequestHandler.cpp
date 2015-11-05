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
#include "Poco/Logger.h"
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
    std::string username;
    std::string password;
//    Application& app = Application::instance();
    Logger& logger = Application::instance().logger();

    logger.information("Request from " + request.clientAddress().toString());
//    logger->information("Request from " + request.clientAddress().toString());

    Session session = SessionsManager::instance().newSession();
//    cout << "## Session created with Session ID: " << session.id() << endl;
    logger.debug("Session created with Session ID: " + session.id());

    Session theSession = SessionsManager::instance().getSession(session.id());
    logger.debug("Session emplaced into the Sessions Map");

    if (request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials cred(request);
//        const std::string& user = cred.getUsername();
//        const std::string& pwd = cred.getPassword();
        username = cred.getUsername();
        password = cred.getPassword();
        logger.debug("Basic Credentials: [username: " + username + ", password: " + password + "]");

        ZimbraAuthenticator zimbraAuthenticator;
        HTTPResponse::HTTPStatus status = zimbraAuthenticator.authenticate(username, password);

        if (status != HTTPResponse::HTTP_OK) {
            logger.warning("user " + username + " unauthorized for request from " + request.clientAddress().toString());
            response.requireAuthentication("askeeper");
            response.setContentLength(0);
            response.send();
            return;
        }
    } else {
        logger.warning("no user credentials, so ask for authentication");
        response.requireAuthentication("askeeper");
        response.setContentLength(0);
        response.send();
        return;
    }


    logger.information("user " + username + " authenticated for request from " + request.clientAddress().toString());
    logger.information("session id for user " + username + " session is " + session.id());

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");

    std::ostream& ostr = response.send();
    ostr << "{ \"status\": \"success\", \"message\": \"user authenticated\" }";
}

}
}
