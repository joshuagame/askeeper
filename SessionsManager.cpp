//
// Created by Luca on 04/11/2015.
//

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