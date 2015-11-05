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
 * ZimbraAuthenticator.h
 * the Zimbra https client for authentication
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

#ifndef ASKEEPER_ZIMBRAAUTHENTICATOR_H
#define ASKEEPER_ZIMBRAAUTHENTICATOR_H

#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Util/Application.h"
#include "Poco/String.h"


using Poco::Net::HTTPResponse;
using Poco::Net::Context;
using Poco::Net::HTTPSClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPBasicCredentials;
using Poco::Util::Application;
using Poco::replace;

namespace askeeper {
namespace server {

class ZimbraAuthenticator {
public:
    ZimbraAuthenticator() {}
    HTTPResponse::HTTPStatus authenticate(const std::string& username, const std::string& password);
};

}
}


#endif //ASKEEPER_ZIMBRAAUTHENTICATOR_H
