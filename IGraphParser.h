#ifndef IGRAPHPARSER_H
#define IGRAPHPARSER_H

#include <exception>
#include <memory>
#include <sstream>

#include "graph_interfaces/IGraphComplete.h"


class CanNotParceGraphException: public ::std::exception {
private:
    ::std::string whatS;
public:
    CanNotParceGraphException(::std::string reason) {
        ::std::ostringstream stringStream;
        stringStream << "Can not parse graph because " << reason << ".";
        whatS = stringStream.str();
    }
    const char* what() const throw() {
        return whatS.c_str();
    };
};


class IGraphParser {
public:

    virtual ::std::shared_ptr<IGraphComplete> provideGraph() throw (
            CanNotParceGraphException
    )= 0;


    virtual void saveGraph() = 0;
};

#endif // IGRAPHPARSER_H
