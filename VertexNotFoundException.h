#ifndef VERTEXNOTFOUNDEXCEPTION_H
#define VERTEXNOTFOUNDEXCEPTION_H

#include <exception>
#include <sstream>


class VertexNotFoundException: public ::std::exception {
private:
    ::std::string whatS;
public:
    VertexNotFoundException(
            int vertexNumber
    ) {
        ::std::ostringstream stringStream;
        stringStream << "Vertex #" << vertexNumber << " not found.";
        whatS = stringStream.str();
    }

    const char* what() const throw() {
        return whatS.c_str();
    }
};

#endif // VERTEXNOTFOUNDEXCEPTION_H
