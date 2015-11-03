////     _    ____  _  __
////    / \  / ___|| |/ /  ASK
////   / _ \ \___ \| ' /   Authentication Sessions Keeper Server
////  / ___ \ ___) | . \   -------------------------------------
//// /_/   \_\____/|_|\_\  www.codegazoline.it/ask
////                 v1.0
//// ===============================================================================
//// Copyright (C) 2015, Luca Stasio - joshuagame@gmail.com //The CodeGazoline Team/
////
//// main.c
//// main entry point for the ASK Server
////
//// This file is part of the ASK Server.
////
//// The ASK Server is free software: you can redistribute it and/or modify
//// it under the terms of the GNU General Public License as published by
//// the Free Software Foundation, either version 3 of the License, or
//// (at your option) any later version.
////
//// The ASK Server is distributed in the hope that it will be useful,
//// but WITHOUT ANY WARRANTY; without even the implied warranty of
//// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
//// GNU General Public License for more details.
////
//// You should have received a copy of the GNU General Public License
//// along with Nome - Programma.If not, see <http://www.gnu.org/licenses/>.
////
//
//#include "Poco/Net/HTTPServer.h"
//#include "Poco/Net/HTTPRequestHandler.h"
//#include "Poco/Net/HTTPRequestHandlerFactory.h"
//#include "Poco/Net/HTTPServerParams.h"
//#include "Poco/Net/HTTPServerRequestImpl.h"
//#include "Poco/Net/HTTPServerResponse.h"
//#include "Poco/Net/HTTPServerParams.h"
//#include "Poco/Net/SecureStreamSocket.h"
//#include "Poco/Net/SecureServerSocket.h"
//#include "Poco/Net/X509Certificate.h"
//#include "Poco/Timestamp.h"
//#include "Poco/DateTimeFormatter.h"
//#include "Poco/DateTimeFormat.h"
//#include "Poco/Exception.h"
//#include "Poco/SharedPtr.h"
//#include "Poco/Util/ServerApplication.h"
//#include "Poco/Util/Option.h"
//#include "Poco/Util/OptionSet.h"
//#include "Poco/Util/HelpFormatter.h"
//#include "Poco/Net/SSLManager.h"
//#include "Poco/Net/KeyConsoleHandler.h"
//#include "Poco/Net/AcceptCertificateHandler.h"
//#include "Poco/Net/NetException.h"
//#include "Poco/Net/HTTPBasicCredentials.h"
//#include "Poco/Net/HTTPServer.h"
//#include "Poco/Net/HTTPRequestHandler.h"
//#include "Poco/Net/HTTPRequestHandlerFactory.h"
//#include "Poco/Net/HTTPServerParams.h"
//#include "Poco/Net/HTTPServerRequest.h"
//#include "Poco/Net/HTTPServerResponse.h"
//#include "Poco/Net/HTTPServerParams.h"
//#include "Poco/Net/HTMLForm.h"
//#include "Poco/Net/PartHandler.h"
//#include "Poco/Net/MessageHeader.h"
//#include "Poco/Net/ServerSocket.h"
//#include "Poco/CountingStream.h"
//#include "Poco/NullStream.h"
//#include "Poco/StreamCopier.h"
//#include "Poco/Exception.h"
//#include "Poco/Util/ServerApplication.h"
//#include "Poco/Util/Option.h"
//#include "Poco/Util/OptionSet.h"
//#include "Poco/Util/HelpFormatter.h"
//#include "Poco/Net/HTTPCredentials.h"
//#include "Poco/Base64Decoder.h"
//#include <iostream>
//#include <sstream>
//
//
//using Poco::Net::SecureServerSocket;
//using Poco::Net::SecureStreamSocket;
//using Poco::Net::HTTPRequestHandler;
//using Poco::Net::HTTPRequestHandlerFactory;
//using Poco::Net::HTTPServer;
//using Poco::Net::HTTPServerRequest;
//using Poco::Net::HTTPServerRequestImpl;
//using Poco::Net::X509Certificate;
//using Poco::Net::HTTPServerResponse;
//using Poco::Net::HTTPServerParams;
//using Poco::Timestamp;
//using Poco::DateTimeFormatter;
//using Poco::DateTimeFormat;
//using Poco::SharedPtr;
//using Poco::Util::ServerApplication;
//using Poco::Util::Application;
//using Poco::Util::Option;
//using Poco::Util::OptionSet;
//using Poco::Util::HelpFormatter;
//using Poco::Net::SSLManager;
//using Poco::Net::Context;
//using Poco::Net::KeyConsoleHandler;
//using Poco::Net::PrivateKeyPassphraseHandler;
//using Poco::Net::InvalidCertificateHandler;
//using Poco::Net::AcceptCertificateHandler;
//using Poco::Net::NotAuthenticatedException;
//using Poco::Net::ServerSocket;
//using Poco::Net::HTTPRequestHandler;
//using Poco::Net::HTTPRequestHandlerFactory;
//using Poco::Net::HTTPServer;
//using Poco::Net::HTTPServerRequest;
//using Poco::Net::HTTPServerResponse;
//using Poco::Net::HTTPServerParams;
//using Poco::Net::HTTPBasicCredentials;
//using Poco::Net::MessageHeader;
//using Poco::Net::HTMLForm;
//using Poco::Net::NameValueCollection;
//using Poco::Util::ServerApplication;
//using Poco::Util::Application;
//using Poco::Util::Option;
//using Poco::Util::OptionSet;
//using Poco::Util::HelpFormatter;
//using Poco::CountingInputStream;
//using Poco::NullOutputStream;
//using Poco::StreamCopier;
//using Poco::Net::HTTPCredentials;
//using Poco::Base64Decoder;
//
//
//class TimeRequestHandler : public HTTPRequestHandler
//    /// Return a HTML document with the current date and time.
//{
//public:
//    TimeRequestHandler(const std::string& format) :
//            _format(format)
//    {}
//
//    void handleRequest(HTTPServerRequest& request, HTTPServerResponse& response)
//    {
//        Application& app = Application::instance();
//        app.logger().information("Request from " + request.clientAddress().toString());
//
////        SecureStreamSocket socket = static_cast<HTTPServerRequestImpl&>(request).socket();
////        if (socket.havePeerCertificate()) {
////            X509Certificate cert = socket.peerCertificate();
////            app.logger().information("Client certificate: " + cert.subjectName());
////        } else {
////            app.logger().information("No client certificate available.");
////        }
//
//        if (request.hasCredentials()) {
//            Poco::Net::HTTPBasicCredentials cred(request);
//            const std::string& user = cred.getUsername();
//            const std::string& pwd = cred.getPassword();
//            std::cout << "Request Basic Credentials" << std::endl;
//            std::cout << "Username: " << user << std::endl;
//            std::cout << "Password: " << pwd << std::endl;
//        } else {
//            response.requireAuthentication("askeeper");
//            response.setContentLength(0);
//            response.send();
//            return;
//        }
//
//        Timestamp now;
//        std::string dt(DateTimeFormatter::format(now, _format));
//
//        response.setChunkedTransferEncoding(true);
//        response.setContentType("text/html");
//
//        std::ostream& ostr = response.send();
//        ostr << "<html><head><title>HTTPTimeServer powered by POCO C++ Libraries</title>";
//        ostr << "<meta http-equiv=\"refresh\" content=\"1\"></head>";
//        ostr << "<body><p style=\"text-align: center; font-size: 48px;\">";
//        ostr << dt;
//        ostr << "</p></body></html>";
//    }
//
//private:
//    std::string _format;
//};
//
//class TimeRequestHandlerFactory : public HTTPRequestHandlerFactory {
//public:
//    TimeRequestHandlerFactory(const std::string& format) :
//            _format(format)
//    {}
//
//    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request)
//    {
////        std::cout << "REQUEST METHOD: " << request.getMethod() << std::endl;
////        std::cout << "REQUEST Content-Type: " << request.getContentType() << std::endl;
////
////
////        std::string scheme;
////        std::string info;
////        try {
////            request.getCredentials(scheme, info);
////            std::cout << "Auth Scheme: " << scheme << std::endl;
////            std::cout << "Auth Info:   " << info << std::endl;
////            HTTPCredentials credentials;
////            credentials.fromUserInfo(decodeAuthInfo(info));
////            std::cout << "username: " << credentials.getUsername() << std::endl;
////            std::cout << "password: " << credentials.getPassword() << std::endl;
////        } catch (NotAuthenticatedException& nae) {
////            std::cout << "****************************************" << std::endl;
////            std::cout << "EXCEPTION: " << nae.displayText() << std::endl;
////            std::cout << "****************************************" << std::endl;
////            throw nae;
////        }
//
//
//        if (request.getURI() == "/")
//            return new TimeRequestHandler(_format);
//        else
//            return 0;
//    }
//
//private:
//    std::string decodeAuthInfo(const std::string& authInfo)
//    {
//        std::istringstream istr(authInfo);
//        Base64Decoder decoder(istr);
//        std::string s;
//        decoder >> s;
//
//        return s;
//    }
//
//private:
//    std::string _format;
//};
//
//
//class HTTPSTimeServer : public Poco::Util::ServerApplication
//    /// The main application class.
//    ///
//    /// This class handles command-line arguments and
//    /// configuration files.
//    /// Start the HTTPTimeServer executable with the help
//    /// option (/help on Windows, --help on Unix) for
//    /// the available command line options.
//    ///
//    /// To use the sample configuration file (HTTPTimeServer.properties),
//    /// copy the file to the directory where the HTTPTimeServer executable
//    /// resides. If you start the debug version of the HTTPTimeServer
//    /// (HTTPTimeServerd[.exe]), you must also create a copy of the configuration
//    /// file named HTTPTimeServerd.properties. In the configuration file, you
//    /// can specify the port on which the server is listening (default
//    /// 9443) and the format of the date/time string sent back to the client.
//    ///
//    /// To test the TimeServer you can use any web browser (https://localhost:9443/).
//{
//public:
//    HTTPSTimeServer() : _helpRequested(false)
//    {
////        Poco::Net::initializeSSL();
//    }
//
//    ~HTTPSTimeServer()
//    {
//        Poco::Net::uninitializeSSL();
//    }
//
//protected:
//    void initialize(Application& self)
//    {
//        loadConfiguration(); // load default configuration files, if present
//        ServerApplication::initialize(self);
//
//        if (config().getBool("HTTPSTimeServer.ssl")) {
//            Poco::Net::initializeSSL();
//            std::cout << "HTTPS initialized" << std::endl;
//        }
//    }
//
//    void uninitialize()
//    {
//        ServerApplication::uninitialize();
//    }
//
//    void defineOptions(OptionSet& options)
//    {
//        ServerApplication::defineOptions(options);
//
//        options.addOption(
//                Option("help", "h", "display help information on command line arguments")
//                        .required(false)
//                        .repeatable(false));
//    }
//
//    void handleOption(const std::string& name, const std::string& value)
//    {
//        ServerApplication::handleOption(name, value);
//
//        if (name == "help")
//            _helpRequested = true;
//    }
//
//    void displayHelp()
//    {
//        HelpFormatter helpFormatter(options());
//        helpFormatter.setCommand(commandName());
//        helpFormatter.setUsage("OPTIONS");
//        helpFormatter.setHeader("A web server that serves the current date and time.");
//        helpFormatter.format(std::cout);
//    }
//
//    int main(const std::vector<std::string>& args)
//    {
//        if (_helpRequested) {
//            displayHelp();
//        } else {
//            // get parameters from configuration file
//            unsigned short port = (unsigned short)config().getInt("HTTPSTimeServer.port", 8765);
//            std::cout << "Starting on port " << port << std::endl;
//            std::string format(config().getString("HTTPSTimeServer.format", DateTimeFormat::SORTABLE_FORMAT));
//
//            // set-up a server socket
//            SecureServerSocket svs(port);
//            // set-up a HTTPServer instance
//            HTTPServer srv(new TimeRequestHandlerFactory(format), svs, new HTTPServerParams);
//            // start the HTTPServer
//            srv.start();
//            // wait for CTRL-C or kill
//            waitForTerminationRequest();
//
//            std::cout << "a-keeper server shutting down" << std::endl;
//            // Stop the HTTPServer
//            srv.stop();
//        }
//        return Application::EXIT_OK;
//    }
//
//private:
//    bool _helpRequested;
//};

#include "ASKServer.h"

int main(int argc, char** argv)
{
    askeeper::server::ASKServer server;
    return server.run(argc, argv);
}