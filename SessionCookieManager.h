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
#include <iostream>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPCookie.h"
#include "Poco/Util/Application.h"

using namespace Poco::Net;

namespace askeeper {
namespace server {

class SessionCookieManager {
public:
    std::string getSessionIdFromCookie(HTTPServerRequest& request);
    void setSessionCookie(HTTPServerResponse& response, const std::string& sessionId, bool remove = false);
    void removeSessionCookie(HTTPServerResponse& response);

protected:
    static const std::string SESSION_COOKIE_NAME;
    static const std::string NOID;

};

inline std::string SessionCookieManager::getSessionIdFromCookie(HTTPServerRequest& request)
{
    std::cout << "Getting session cookie" << std::endl;
    std::string sessionId = NOID;
    NameValueCollection cookies;

    // get cookies from request
    request.getCookies(cookies);
    std::cout << "got cookies" << std::endl;

    // and search for ASKSESSION cookie to grab the sessionId
    Poco::Net::NameValueCollection::ConstIterator it = cookies.find(SESSION_COOKIE_NAME);
    std::cout << "got it" << std::endl;
    if (it != cookies.end()) {
        sessionId = it->second;
        std::cout << "cookie found" << std::endl;
    }

    return sessionId;
}

// TODO: set a way to enable browser session age for cookie
inline void SessionCookieManager::setSessionCookie(HTTPServerResponse& response, const std::string& sessionId, bool remove)
{
    int sessionExpirationTime = Poco::Util::Application::instance().config().getInt("session.expiration", 360000);
    int maxAge = remove ? 0 : (sessionExpirationTime > 1000 ? sessionExpirationTime / 1000 : 1);

    HTTPCookie cookie(SESSION_COOKIE_NAME, sessionId);
    cookie.setPath("/");
    cookie.setMaxAge(maxAge);

    response.addCookie(cookie);
}

inline void SessionCookieManager::removeSessionCookie(HTTPServerResponse& response)
{
    setSessionCookie(response, "", true);
}


}
}

#endif //ASKEEPER_SESSIONCOOKIECHECKER_H
