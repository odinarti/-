#ifndef IGRAPHPROVIDER_H
#define IGRAPHPROVIDER_H

#include "graph_interfaces/IGraphEdgesProvider.h"
#include "graph_interfaces/IGraphVerticesProvider.h"


class IGraphProvider:
        public IGraphVerticesProvider,
        public IGraphEdgesProvider {};

#endif // IGRAPHPROVIDER_H
