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
 * RequestHandlerFactory.h
 * Request handler factory for the server. This is the requests url router.
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

#ifndef ASKEEPER_ASKREQUESTHANDLERFACTORY_H
#define ASKEEPER_ASKREQUESTHANDLERFACTORY_H

#include <iostream>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/NameValueCollection.h"
#include "SiginRequestHandler.h"

using namespace std;
using namespace Poco::Net;

namespace askeeper {
namespace server {

class RequestHandlerFactory : public HTTPRequestHandlerFactory {
public:
    RequestHandlerFactory()
    {
        Application::instance().logger().information("Request Handler Factory initialized");
    }

    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request);

private:
    static const std::string SIGNIN_PATH;
    static const std::string SIGNOUT_PATH;

};

inline HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const HTTPServerRequest& request)
{
    if (request.getURI() == SIGNIN_PATH) {

        return new SiginRequestHandler();
//        TODO: move this code into SigninRequestHandler
//        if (request.getMethod() == HTTPServerRequest::HTTP_GET) {
//            return new SiginRequestHandler();
//        } else if (request.getMethod() == HTTPServerRequest::HTTP_POST) {
//            return new SiginRequestHandler();
//        } else {
//            cout << "unknown method" << endl;
//        }
    } else {
        return 0;
    }
}

}
}

#endif //ASKEEPER_ASKREQUESTHANDLERFACTORY_H
