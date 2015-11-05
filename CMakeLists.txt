cmake_minimum_required(VERSION 3.3)
project(askeeper)

# define the project
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp ASKServer.cpp ASKServer.h RequestHandlerFactory.cpp RequestHandlerFactory.h SiginRequestHandler.cpp SiginRequestHandler.h ZimbraAuthenticator.cpp ZimbraAuthenticator.h SessionsManager.cpp SessionsManager.h Session.cpp Session.h)
add_executable(askeeper ${SOURCE_FILES})

# set the POCO paths and libs
set(POCO_PREFIX      "/usr/local") # the directory containing "include" and "lib"
set(POCO_INCLUDE_DIR "${POCO_PREFIX}/include")
set(POCO_LIB_DIR     "${POCO_PREFIX}/lib")
set(POCO_LIBS        "${POCO_LIB_DIR}/libPocoNet.dll.a"
                     "${POCO_LIB_DIR}/libPocoNetSSL.dll.a"
                     "${POCO_LIB_DIR}/libPocoUtil.dll.a"
                     "${POCO_LIB_DIR}/libPocoJSON.dll.a"
                     "${POCO_LIB_DIR}/libPocoXML.dll.a"
                     "${POCO_LIB_DIR}/libPocoFoundation.dll.a"
                     "pthread")

# set the include path for the app
target_include_directories(askeeper PRIVATE "${POCO_INCLUDE_DIR}")
# link the app against POCO
target_link_libraries(askeeper "${POCO_LIBS}")
