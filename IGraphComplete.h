#ifndef IGRAPHCOMPLETE_H
#define IGRAPHCOMPLETE_H

#include "graph_interfaces/IGraphEdgeRemover.h"
#include "graph_interfaces/IGraphProvider.h"


class IGraphComplete: public IGraphEdgeRemover, public IGraphProvider {};

#endif // IGRAPHCOMPLETE_H
