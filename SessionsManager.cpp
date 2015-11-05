//
// Created by Luca on 04/11/2015.
//

#include "SessionsManager.h"

namespace askeeper {
namespace server {

std::unordered_map<std::string, Session> SessionsManager::sessions{};

Session SessionsManager::newSession()
{
    UUIDGenerator& generator = UUIDGenerator::defaultGenerator();
    MD5Engine md5Engine;
    UUID uuid(generator.createFromName(UUID::uri(), generator.create().toString(), md5Engine));
    std::cout << "UUID generated" << std::endl;

    Session session(uuid.toString());
    std::cout << "Session generated" << std::endl;

    sessions.emplace(session.id(), session);
    std::cout << "Session emplaced into the static sessions map" << std::endl;

    std::unordered_map<std::string, Session>::iterator it = sessions.find(session.id());
    if (it != sessions.end()) {
        std::cout << "SESSION FOUND" << std::endl;
    } else {
        std::cout << "SESSION NOT FOUND" << std::endl;
    }


    return session;
}


}
}