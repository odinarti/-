#ifndef IGRAPHBUILDER_H
#define IGRAPHBUILDER_H

#include <exception>
#include <memory>

#include "graph_interfaces/IGraphComplete.h"
#include "graph_interfaces/VertexNotFoundException.h"


class CanNotBuildAssociatedGraph: public ::std::runtime_error {
public:
    const char* what() const throw() {
        return "Can not build graph, because he in not associated.";
    }
};


class IGraphBuilder {
public:

    virtual IGraphBuilder* addVertex(int coordinateX, int coordinateY) = 0;


    virtual IGraphBuilder* addEdge(
            int firstVertex,
            int secondVertex
    ) throw(VertexNotFoundException) = 0;


    virtual ::std::shared_ptr<IGraphComplete> build() throw (
            CanNotBuildAssociatedGraph, VertexNotFoundException
    ) = 0;
};

#endif // IGRAPHBUILDER_H
