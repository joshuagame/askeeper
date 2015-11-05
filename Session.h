//
// Created by Luca on 04/11/2015.
//

#ifndef ASKEEPER_SESSION_H
#define ASKEEPER_SESSION_H

#include <string>

namespace askeeper {
namespace server {

class Session {
public:
    Session() {}
    Session(const std::string& id) : _id(id) {}
    std::string id()
    {
        return _id;
    }
private:
    std::string _id;
};

}
}

#endif //ASKEEPER_SESSION_H
