#ifndef IGRAPHVERTEXASSOCIATEDADDER_H
#define IGRAPHVERTEXASSOCIATEDADDER_H

#include <QPoint>

#include "graph_interfaces/VertexNotFoundException.h"


class IGraphVertexAssociatedAdder {
public:

    virtual void addVertex(
            QPoint const& coordinates,
            int associatedVertex
    ) throw(VertexNotFoundException) = 0;


    virtual void addVertex(
            int coordinateX,
            int coordinateY,
            int associatedVertex
    ) throw(VertexNotFoundException) = 0;
};

#endif // IGRAPHVERTEXASSOCIATEDADDER_H
