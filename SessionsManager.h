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
 * SessionManager.h
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

#ifndef ASKEEPER_SESSIONSMANAGER_H
#define ASKEEPER_SESSIONSMANAGER_H

#include <iostream>
#include <string>
#include <functional>
#include <exception>
#include <unordered_map>
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/MD5Engine.h"
#include "Poco/UniqueExpireCache.h"
#include "Poco/ExpirationDecorator.h"
#include "Session.h"

using Poco::UUID;
using Poco::UUIDGenerator;
using Poco::MD5Engine;

// NOTE:
// ---> http://silviuardelean.ro/2012/06/05/few-singleton-approaches/
// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
// http://stackoverflow.com/questions/270947/can-any-one-provide-me-a-sample-of-singleton-in-c/271104#271104

namespace askeeper {
namespace server {

class SessionsManager {
    SessionsManager() = delete;
    SessionsManager(SessionsManager&) = delete;
    void operator=(SessionsManager&) = delete;

public:
    static SessionsManager& instance()
    {
        static SessionsManager* _instance{};
        return *_instance;
    }

    Session newSession();

    Session getSession(const std::string& sessionId)
    {
        return sessions[sessionId];
    }

private:
    ~SessionsManager() {}
    static std::unordered_map<std::string, Session> sessions;

};


}
}


#endif //ASKEEPER_SESSIONSMANAGER_H
