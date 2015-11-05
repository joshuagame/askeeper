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
 * SiginRequestHandler.cpp
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
#include "SiginRequestHandler.h"
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

// TODO: ******* REWRITE THIS CODE, PLEASE!!!! *******
void SiginRequestHandler::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
{
    std::string username;
    std::string password;
    Logger& logger = Application::instance().logger();

    logger.information("Request from " + request.clientAddress().toString());

    //
    // COOKIE AND SESSIONID CHECKS
    //
    // check for sessionId from cookie in request
    std::string sessionId = getSessionIdFromCookie(request);
    if (sessionId == NOID) {
        logger.information("no sessionId from request: probably there is no ASKSESSION cookie in request");
    } else {
        // now check for the sessionId in the sessions map
        Session theSession = SessionsManager::instance().getSession(sessionId);
        if (sessionId == theSession.id()) {
            logger.debug("found an active session for sessionId " + sessionId);
        } else {
            logger.warning("no active session for sessionId " + sessionId + ", so ask for authentication");
            response.requireAuthentication("askeeper");
            response.setContentLength(0);
            response.send();
            return;
        }
        response.setChunkedTransferEncoding(true);
        response.setContentType("application/json");
        std::ostream& ostr = response.send();
        ostr << "{ \"status\": \"success\", \"message\": \"user authenticated by sessionId in ASKSESSION cookie\" }";
        return;
    }

    //
    // AUTHENTICATION
    //

    if (request.hasCredentials()) {
        Poco::Net::HTTPBasicCredentials cred(request);
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

    //
    // AUTHENTICATION OK. SESSION START.
    //

    // user has been authenticated. So, start a new session and send the response
    Session session = SessionsManager::instance().newSession();
    logger.debug("Session created with Session ID: " + session.id());

    logger.information("user " + username + " authenticated for request from " + request.clientAddress().toString());
    logger.information("session id for user " + username + " session is " + session.id());

    response.setChunkedTransferEncoding(true);
    response.setContentType("application/json");
    setSessionCookie(response, session.id());

    std::ostream& ostr = response.send();
    ostr << "{ \"status\": \"success\", \"message\": \"user authenticated\" }";
}

}
}
