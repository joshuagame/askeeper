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
 * ASKServer.cpp
 * the server application for askeeper
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

#include "ASKServer.h"
#include "RequestHandlerFactory.h"

namespace askeeper {
namespace server {

int ASKServer::main(const std::vector<std::string>& args)
{
    logger().information("starting server app main");
    if (requiredHelp) {
        displayHelp();
    } else {
        // get parameters from configuration file
        unsigned short port = (unsigned short)config().getInt("ASKServer.port", 8765);
        logger().information("starting server on port " + config().getString("ASKServer.port"));

        // set-up a server socket
        SecureServerSocket svs(port);
        // set-up a HTTPServer instance
        HTTPServer srv(new RequestHandlerFactory(), svs, new HTTPServerParams);
        // start the HTTPServer
        srv.start();
        // wait for CTRL-C or kill
        waitForTerminationRequest();

        logger().information("server is shutting down");
        // Stop the HTTPServer
        srv.stop();
        logger().information("server is down... Bye!");
    }

    return Application::EXIT_OK;
}

ASKServer::~ASKServer()
{
    uninitializeSSL();
}


}
}
