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
 * SessionCookieManager.h
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

#ifndef ASKEEPER_SESSIONCOOKIECHECKER_H
#define ASKEEPER_SESSIONCOOKIECHECKER_H

#include <string>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPCookie.h"

using namespace Poco::Net;

namespace askeeper {
namespace server {

class SessionCookieManager {
public:
    std::string getSessionIdFromCookie(HTTPServerRequest& request);
    void setSessionCookie(HTTPServerResponse& response, const std::string& sessionId);

protected:
    static const std::string SESSION_COOKIE_NAME;
    static const std::string NOID;

};

inline std::string SessionCookieManager::getSessionIdFromCookie(HTTPServerRequest& request)
{
    std::string sessionId = NOID;
    NameValueCollection cookies;

    // get cookies from request
    request.getCookies(cookies);

    // and search for ASKSESSION cookie to grab the sessionId
    Poco::Net::NameValueCollection::ConstIterator it = cookies.find(SESSION_COOKIE_NAME);
    if (it != cookies.end()) {
        sessionId = it->second;
    }

    return sessionId;
}

inline void SessionCookieManager::setSessionCookie(HTTPServerResponse& response, const std::string& sessionId)
{
    HTTPCookie cookie(SESSION_COOKIE_NAME, sessionId);
    cookie.setPath("/");
    cookie.setMaxAge(3600); // 1 hour
    response.addCookie(cookie);
}

}
}

#endif //ASKEEPER_SESSIONCOOKIECHECKER_H
