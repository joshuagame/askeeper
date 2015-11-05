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
 * BasicAuthRequestHandler.h
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

#ifndef ASKEEPER_REQUESTHANDLER_H
#define ASKEEPER_REQUESTHANDLER_H

#include <iostream>
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Util/Application.h"

using namespace std;
using namespace Poco::Net;
using namespace Poco::Util;

namespace askeeper {
namespace server {

class BasicAuthRequestHandler : public HTTPRequestHandler {
public:
    BasicAuthRequestHandler()
    {
        cout << "Basic Authentication request handler" << endl;
//        Application& app = Application::instance();
//        logger = &app.logger();
    }

    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response);

private:
//    Poco::Logger* logger;
};

}
}

#endif //ASKEEPER_REQUESTHANDLER_H
