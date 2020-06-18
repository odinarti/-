#ifndef GRAPHBUILDERIMPLEMENTATION_H
#define GRAPHBUILDERIMPLEMENTATION_H

#include "graph_interfaces/IGraphBuilder.h"
#include "graph_interfaces/IGraphEdgesProvider.h"
#include "graph_interfaces/IGraphVerticesProvider.h"


class GraphOnAdjacencyMatrixBuilder: public IGraphBuilder
{
private:
    /// vertexList[0] is zero, because vertex count from 1.
    VertexList* vertexList;
    EdgeList*   edgeList;
public:
    GraphOnAdjacencyMatrixBuilder();
    ~GraphOnAdjacencyMatrixBuilder();

    // IGraphBuilder interface
public:
    IGraphBuilder* addVertex(int coordinateX, int coordinateY) override;
    IGraphBuilder* addEdge(int firstVertex, int secondVertex) throw(
            VertexNotFoundException
    ) override;
    ::std::shared_ptr<IGraphComplete> build() throw (
            CanNotBuildAssociatedGraph, VertexNotFoundException
    ) override;
};

#endif // GRAPHBUILDERIMPLEMENTATION_H
