#ifndef IGRAPHEDGESPROVIDER_H
#define IGRAPHEDGESPROVIDER_H

#include <QList>
#include <QPair>


typedef QList<QPair<int, int>> EdgeList;


class IGraphEdgesProvider {
public:

    virtual EdgeList provideEdges() = 0;
};

#endif // IGRAPHEDGESPROVIDER_H
