#ifndef GRAPHCOMPLETEIMPLEMENTATION_H
#define GRAPHCOMPLETEIMPLEMENTATION_H

#include "graph_interfaces/IGraphComplete.h"


class GraphOnAdjacencyMatrix: public IGraphComplete
{
private:
    /// vertexList[0] is zero, because vertex count from 1.
    VertexList vertexList;
    /// edgeMatrix's first line and first column are empty for convenience.
    ::std::vector<::std::vector<short>> edgeMatrix;
public:
    GraphOnAdjacencyMatrix(
            VertexList vertexList,
            ::std::vector<::std::vector<short>> edgeMatrix
    );
    ~GraphOnAdjacencyMatrix();
private:
    ::std::vector<::std::vector<short>> createCopyOfEdgeMatrix();
    bool graphIsFullConnected(::std::vector<::std::vector<short>> edgeMatrix);

    // IGraphEdgesProvider interface
public:
    EdgeList provideEdges() override;

    // IGraphVerticesProvider interface
public:
    VertexList provideVertex() override;

    // IGraphEdgeRemover interface
public:
    void removeEdge(int firstVertex, int secondVertex) throw(
            CanNotRemoveEdgeException, VertexNotFoundException
    ) override;
};

#endif // GRAPHCOMPLETEIMPLEMENTATION_H
