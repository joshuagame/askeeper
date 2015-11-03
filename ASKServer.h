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
 * ASKServer.h
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

#ifndef ASKEEPER_ASKSERVER_H
#define ASKEEPER_ASKSERVER_H

#include <iostream>
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Net/HTTPServer.h"

using namespace std;
using namespace Poco;
using namespace Poco::Util;
using namespace Poco::Net;

namespace askeeper {
namespace server {

class ASKServer : public ServerApplication {
public:
    ASKServer() : requiredHelp(false)
    { }

    ~ASKServer()
    {
        uninitializeSSL();
    }

protected:
    void initialize(Application& app);
    void uninitialize();
    void defineOptions(OptionSet& options);
    void handleOption(const std::string& name, const std::string& value);
    void displayHelp();
    int main(const std::vector<std::string>& args);

private:
    bool requiredHelp;

};

/* inlines */

inline void ASKServer::initialize(Application& app)
{
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(app);

    if (config().getBool("ASKServer.ssl")) {
        initializeSSL();
        cout << "HTTPS initialized" << std::endl;
    }
}

inline void ASKServer::uninitialize()
{
    ServerApplication::uninitialize();
}

inline void ASKServer::defineOptions(OptionSet& options)
{
    ServerApplication::defineOptions(options);

    options.addOption(
            Option("help", "h", "display help information on command line arguments")
                    .required(false)
                    .repeatable(false));
}

inline void ASKServer::handleOption(const std::string& name, const std::string& value)
{
    ServerApplication::handleOption(name, value);

    if (name == "help")
        requiredHelp = true;
}

inline void ASKServer::displayHelp()
{
    HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("ASKEEPER v1.0\nAuthentication Sessions Keeper Server");
    helpFormatter.format(std::cout);
}

}
}


#endif //ASKEEPER_ASKSERVER_H
