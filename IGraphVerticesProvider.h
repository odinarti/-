#ifndef IGRAPHVERTICESPROVIDER_H
#define IGRAPHVERTICESPROVIDER_H

#include <QList>
#include <QPair>


typedef QList<QPair<int, int>> VertexList;


class IGraphVerticesProvider {
public:

    virtual VertexList provideVertex() = 0;
};

#endif // IGRAPHVERTICESPROVIDER_H
