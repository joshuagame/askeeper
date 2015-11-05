//
// Created by Luca on 04/11/2015.
//

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
