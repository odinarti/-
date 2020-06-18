#include <QDebug>
#include "GraphOnAdjacencyMatrix.h"

GraphOnAdjacencyMatrix::GraphOnAdjacencyMatrix(
        VertexList vertexList,
        ::std::vector<::std::vector<short>> edgeMatrix
) {
    this->vertexList = vertexList;
    this->edgeMatrix = edgeMatrix;
}

GraphOnAdjacencyMatrix::~GraphOnAdjacencyMatrix() {}

EdgeList GraphOnAdjacencyMatrix::provideEdges() {
    EdgeList edgeList;
    for (int rowNumber = 1;
         rowNumber < this->vertexList.length();
         rowNumber++
    ) {
        for (int columnNumber = 0 + rowNumber;
             columnNumber < this->vertexList.length();
             columnNumber++
        ) {
            if (1 == this->edgeMatrix[rowNumber][columnNumber]) {
                edgeList.append(QPair<int, int>(rowNumber, columnNumber));
            }
        }
    }
    return edgeList;
}

VertexList GraphOnAdjacencyMatrix::provideVertex() {
    qDebug() << "provideVertex";
    return this->vertexList;
}

void GraphOnAdjacencyMatrix::removeEdge(
        int firstVertex,
        int secondVertex
) throw (CanNotRemoveEdgeException, VertexNotFoundException) {
    if (firstVertex >= this->vertexList.length()) {
        throw VertexNotFoundException(firstVertex);
    }
    if (secondVertex>= this->vertexList.length()) {
        throw VertexNotFoundException(secondVertex);
    }
    ::std::vector<::std::vector<short>> copyOfTheEdgeMatrix =
            this->createCopyOfEdgeMatrix();
    copyOfTheEdgeMatrix[firstVertex][secondVertex] = 0;
    copyOfTheEdgeMatrix[secondVertex][firstVertex] = 0;
    if (!graphIsFullConnected(copyOfTheEdgeMatrix)) {
        throw CanNotRemoveEdgeException(firstVertex, secondVertex);
    }
    edgeMatrix[firstVertex][secondVertex] = 0;
    edgeMatrix[secondVertex][firstVertex] = 0;
    for (int rowNumber = 0;
         rowNumber < this->vertexList.length();
         rowNumber++
    ) {
//        delete[] copyOfTheEdgeMatrix[rowNumber];
    }
//    delete[] copyOfTheEdgeMatrix;
}

::std::vector<::std::vector<short>> GraphOnAdjacencyMatrix::createCopyOfEdgeMatrix() {
    ::std::vector<::std::vector<short>> newEdgeMatrix(this->vertexList.length());
    for (int rowNumber = 1;
         rowNumber < this->vertexList.length();
         rowNumber++
    ) {
        newEdgeMatrix[rowNumber] = ::std::vector<short>(this->vertexList.length());
        for (int columnNumber = 1;
             columnNumber < this->vertexList.length();
             columnNumber++
        ) {
            newEdgeMatrix[rowNumber][columnNumber] =
                    this->edgeMatrix[rowNumber][columnNumber];
        }
    }
    return newEdgeMatrix;
}

// TODO[#1]: use in builder.
bool GraphOnAdjacencyMatrix::graphIsFullConnected(::std::vector<::std::vector<short>> edgeMatrix) {
    short* vertexState = new short[this->vertexList.length()];
    for (int vertexNumber = 1;
         vertexNumber < this->vertexList.length();
         vertexNumber++) {
        /// 1 - not checked, 2 - need check aka start of edge, 3 - checked
        vertexState[vertexNumber] = 1;
    }
    vertexState[1] = 2;
    /// start run
    int vertexNumberForCheck;
    bool allVertexWasChecked = false;
    do {
        allVertexWasChecked = true;
        for (int vertexNumber = 1;
             vertexNumber < this->vertexList.length();
             vertexNumber++
        ) {
            if (vertexState[vertexNumber] == 2) {
                vertexState[vertexNumber] = 3;
                vertexNumberForCheck = vertexNumber;
                break;
            }
        }
        for (int endOfEdge = 1;
             endOfEdge < this->vertexList.length();
             endOfEdge++
        ) {
            if (1 == edgeMatrix[vertexNumberForCheck][endOfEdge]
                    && 1 == vertexState[endOfEdge]
            ) {
                vertexState[endOfEdge] = 2;
            }
        }
        for (int vertexNumber = 1;
             vertexNumber < this->vertexList.length();
             vertexNumber++
        ) {
            if (vertexState[vertexNumber] == 2) {
                allVertexWasChecked = false;
            }
        }
    } while (allVertexWasChecked == false);
    /// run by vertices for check
    bool isFullConnected = true;
    for (int vertexNumber = 1;
         vertexNumber < this->vertexList.length();
         vertexNumber++
    ) {
        if (vertexState[vertexNumber] == 1) {
            isFullConnected = false;
        }
    }

    delete[] vertexState;
    return isFullConnected;
}
