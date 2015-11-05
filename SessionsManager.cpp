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
 * SessionsManager.cpp
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

#include "SessionsManager.h"
#include "Poco/Logger.h"
#include "Poco/Util/Application.h"

namespace askeeper {
namespace server {

std::unordered_map<std::string, Session> SessionsManager::sessions{};

Session SessionsManager::newSession()
{
    Poco::Logger& logger = Poco::Util::Application::instance().logger();
    UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
    MD5Engine md5Engine;

    UUID uuid(generator.createFromName(UUID::uri(), generator.create().toString(), md5Engine));
    logger.debug("UUID generated");

    Session session(uuid.toString());
    logger.debug("Session started");

    sessions.emplace(session.id(), session);
    logger.debug("Session emplaced into the sessions map");

//    std::unordered_map<std::string, Session>::iterator it = sessions.find(session.id());
//    if (it != sessions.end()) {
//        std::cout << "SESSION FOUND" << std::endl;
//    } else {
//        std::cout << "SESSION NOT FOUND" << std::endl;
//    }

    return session;
}


}
}