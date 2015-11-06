//     _    ____  _  __
//    / \  / ___|| |/ /  ASK
//   / _ \ \___ \| ' /   Authentication Sessions Keeper Server
//  / ___ \ ___) | . \   -------------------------------------
// /_/   \_\____/|_|\_\  www.codegazoline.it/ask
//                 v1.0
// ===============================================================================
// Copyright (C) 2015, Luca Stasio - joshuagame@gmail.com //The CodeGazoline Team/
//
// main.c
// main entry point for the ASK Server
//
// This file is part of the ASK Server.
//
// The ASK Server is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// The ASK Server is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Nome - Programma.If not, see <http://www.gnu.org/licenses/>.

#include "ASKServer.h"
#include "Poco/UniqueExpireCache.h"
#include "Poco/ExpirationDecorator.h"
#include "Session.h"
#include <iostream>
#include <string>

typedef Poco::ExpirationDecorator<askeeper::server::Session> ExpSession;

int main(int argc, char** argv)
{

    Poco::UniqueExpireCache<string, ExpSession> cache;
    const std::string sid1("jkjfksjf-sfdsdfs-fdsfsdfs-sfd");
    const std::string sid2("dsgfgrge-jjkgkky-fdsfsdfs-sfd");
    askeeper::server::Session s1(sid1);
    askeeper::server::Session s2(sid2);

    ExpSession es1(s1, 5);
    ExpSession es2(s2, 5);

    cache.add(sid1, es1);
    cache.add(sid2, es2);

    std::cout << "cache size: " << cache.size() << std::endl;

    Poco::SharedPtr<ExpSession> ptrValS1 = cache.get(sid1);
    if (!ptrValS1.isNull()) {
        std::cout << "session1 found";
        askeeper::server::Session fs1 = ptrValS1->value();
        std::cout << " ID: " << fs1.id() << std::endl;
    }

    Poco::SharedPtr<ExpSession> ptrValS2 = cache.get(sid2);
    if (!ptrValS2.isNull()) {
        std::cout << "session2 found";
        askeeper::server::Session fs2 = ptrValS2->value();
        std::cout << " ID: " << fs2.id() << std::endl;
    }

    for (int i = 0; i < 1000000; i++) {
        std::cout << i << ".";
    }

    std::cout << "cache size: " << cache.size() << std::endl;
    if (cache.size() == 0) {
        std::cout << "all sessions expired" << std::endl;
    }

    return 0;

//    askeeper::server::ASKServer server;
//    return server.run(argc, argv);
}