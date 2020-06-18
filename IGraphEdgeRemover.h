#ifndef IGRAPHEDGEREMOVER_H
#define IGRAPHEDGEREMOVER_H

#include <exception>
#include <sstream>

#include "graph_interfaces/VertexNotFoundException.h"


class CanNotRemoveEdgeException: public ::std::exception {
private:
    ::std::string whatS;
public:
    CanNotRemoveEdgeException(
            int firstVertex,
            int secondVertex
    ) {
        ::std::ostringstream stringStream;
        stringStream << "It is not possible to remove the edge between vertices"
                     << "#" << firstVertex << " and #" << secondVertex
                     << "because this will make the graph incoherent.";
        whatS = stringStream.str();
    }

    const char* what() const throw() {
        return whatS.c_str();
    }
};


class IGraphEdgeRemover {
public:

    virtual void removeEdge(
            int firstVertex,
            int secondVertex
    ) throw(CanNotRemoveEdgeException, VertexNotFoundException) = 0;
};

#endif // IGRAPHEDGEREMOVER_H
