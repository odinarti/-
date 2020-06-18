#include <QDebug>

#include "TextFileParser.h"
#include "graph_interfaces/VertexNotFoundException.h"

TextFileParser::TextFileParser(
        IGraphBuilder* iGraphBuilder,
        const char* filePath
) {
        this->iGraphBuilder = iGraphBuilder;
        this->storage = new QFile(QString(filePath));
}

TextFileParser::TextFileParser(
        IGraphBuilder* iGraphBuilder,
        ::std::string filePath
) {
    this->iGraphBuilder = iGraphBuilder;
    this->storage = new QFile(QString(filePath.c_str()));
}

TextFileParser::TextFileParser(
        IGraphBuilder* iGraphBuilder,
        QString filePath
) {
    this->iGraphBuilder = iGraphBuilder;
    this->storage = new QFile(filePath);
}

TextFileParser::~TextFileParser() {
    if (nullptr != this->iGraphBuilder) {
        delete this->iGraphBuilder;
        this->iGraphBuilder = nullptr;
    }
    if (nullptr != this->storage) {
        delete this->storage;
        this->storage = nullptr;
    }
}

::std::shared_ptr<IGraphComplete> TextFileParser::provideGraph() throw (
        CanNotParceGraphException
) {
    if (nullptr == this->parsedGraph.get()) {
        try {
            this->parse();
        } catch (CanNotParceGraphException e) {
            throw std::move(e);
        }
    }
    return parsedGraph;
}

void TextFileParser::saveGraph() {
    qDebug() << "void TextFileParser::saveGraph() not implemented";
}

void TextFileParser::parse() throw(CanNotParceGraphException) {
    if (!storage->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Can not open file withgraph for read.";
        throw CanNotParceGraphException(
                    "Can not open file withgraph for read."
        );
    }
    QTextStream textStream(storage);
    bool ok;
    /// Parsing vertices.
    int vertexCounter = textStream.readLine().toInt(&ok);
    if (!ok) {
        qDebug() << "Can not read count of vertex.";
        throw CanNotParceGraphException(
                    "Can not read count of vertex."
        );
    }
    for (int vertexNumber = 0; vertexNumber < vertexCounter; vertexNumber++) {
        QStringList vertexCoordinatesAsStrings =
                textStream.readLine().split(" ");
        if (2 != vertexCoordinatesAsStrings.size()) {
            ::std::ostringstream stringStream;
            stringStream << "On vertex #" << vertexNumber + 1
                         << " founded " << vertexCoordinatesAsStrings.size()
                         << " elements instead 2.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        int coordinateX = vertexCoordinatesAsStrings[0].toInt(&ok);
        if (!ok) {
            ::std::ostringstream stringStream;
            stringStream << "On vertex #" << vertexNumber + 1
                         << " x-coordinate can not be parse to int.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        int coordinateY = vertexCoordinatesAsStrings[1].toInt(&ok);
        if (!ok) {
            ::std::ostringstream stringStream;
            stringStream << "On vertex #" << vertexNumber + 1
                         << " y-coordinate can not be parse to int.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        iGraphBuilder->addVertex(coordinateX, coordinateY);
    }
    /// Parsing edges.
    int edgeCounter = textStream.readLine().toInt(&ok);
    if (!ok) {
        qDebug() << "Can not read count of edge.";
        throw CanNotParceGraphException(
                    "Can not read count of edge."
        );
    }
    for (int edgeNumber = 0; edgeNumber < edgeCounter; edgeNumber++) {
        QStringList pairOfVerticesAsStrings =
                textStream.readLine().split(" ");
        if (2 != pairOfVerticesAsStrings.size()) {
            ::std::ostringstream stringStream;
            stringStream << "On edge #" << edgeNumber + 1
                         << " founded " << pairOfVerticesAsStrings.size()
                         << " elenments instead 2.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        int firstVertex = pairOfVerticesAsStrings[0].toInt(&ok);
        if (!ok) {
            ::std::ostringstream stringStream;
            stringStream << "On edge #" << edgeNumber + 1
                         << " firstVertex can not be parse to int.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        if (firstVertex > vertexCounter) {
            ::std::ostringstream stringStream;
            stringStream << "On edge #" << edgeNumber + 1
                         << " firstVertex is " << firstVertex
                         << " but total vertices is " << vertexCounter;
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        int secondVertex = pairOfVerticesAsStrings[1].toInt(&ok);
        if (!ok) {
            ::std::ostringstream stringStream;
            stringStream << "On edge #" << edgeNumber + 1
                         << " secondVertex can not be parse to int.";
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        if (secondVertex > vertexCounter) {
            ::std::ostringstream stringStream;
            stringStream << "On edge #" << edgeNumber + 1
                         << " secondVertex is " << firstVertex
                         << " but total vertices is " << vertexCounter;
            qDebug() << stringStream.str().c_str();
            throw CanNotParceGraphException(stringStream.str());
        }
        try {
            iGraphBuilder->addEdge(firstVertex, secondVertex);
        } catch (VertexNotFoundException exception) {
            throw CanNotParceGraphException(exception.what());
        }
    }
    this->parsedGraph = this->iGraphBuilder->build();
}
