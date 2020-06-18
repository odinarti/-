#ifndef TEXTFILEPARSER_H
#define TEXTFILEPARSER_H

#include <QFile>

#include <string>

#include "graph_interfaces/IGraphBuilder.h"
#include "graph_interfaces/IGraphParser.h"


class TextFileParser: public IGraphParser {
private:
    IGraphBuilder* iGraphBuilder;
    QFile* storage;
    ::std::shared_ptr<IGraphComplete> parsedGraph;
public:
    TextFileParser(IGraphBuilder* iGraphBuilder, const char* filePath);
    TextFileParser(IGraphBuilder* iGraphBuilder, ::std::string filePath);
    TextFileParser(IGraphBuilder* iGraphBuilder, QString filePath);
    ~TextFileParser();
private:
    void parse() throw(CanNotParceGraphException);

// IGraphParser interface
public:
    ::std::shared_ptr<IGraphComplete> provideGraph() throw(
            CanNotParceGraphException
    ) override;
    void saveGraph() override;
};

#endif // TEXTFILEPARSER_H
