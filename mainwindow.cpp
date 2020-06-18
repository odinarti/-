#include <QDebug>
#include <QKeyEvent>
#include <QTextEdit>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QLabel>
#include <QVBoxLayout>

#include "mainwindow.h"

#include "MyTextEdit.h"
#include "file_parser/TextFileParser.h"
#include "graph_implemented/GraphOnAdjacencyMatrixBuilder.h"

MainWindow::MainWindow(QWidget *parent): QWidget(parent) {
    TextFileParser* t = new TextFileParser(
                new GraphOnAdjacencyMatrixBuilder(),
                ":/res/graph"
    );
    try {
        this->graph = t->provideGraph();
        qDebug() << "vertices";
        VertexList vl = graph->provideVertex();
        for (QPair<int, int> vertex: vl) {
            qDebug() << vertex.first << " " << vertex.second;
        }
        qDebug() << "edges";
        EdgeList el = graph->provideEdges();
        for (QPair<int, int> edge: el) {
            qDebug() << edge.first << " " << edge.second;
        }
        /*try {
            graph->removeEdge(2, 3);
        } catch (CanNotRemoveEdgeException e) {
            qDebug() << "remove E "<< e.what();
        } catch (VertexNotFoundException e) {
            qDebug() << "remove E "<< e.what();
        }
        qDebug() << "remove without e";
        qDebug() << "vertices";
        VertexList vl2 = graph->provideVertex();
        for (QPair<int, int> vertex: vl2) {
            qDebug() << vertex.first << " " << vertex.second;
        }
        qDebug() << "edges";
        EdgeList el2 = graph->provideEdges();
        for (QPair<int, int> edge: el2) {
            qDebug() << edge.first << " " << edge.second;
        }*/
    } catch (CanNotParceGraphException e) {
        qDebug() << e.what();
    } catch (...) {
        qDebug() << "anotherEXC";
    }

    qDebug() << "without exception";

    this->scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, this->sceneWidth, this->sceneHeight);
    QGraphicsView* viewForScene = new QGraphicsView(this);
    viewForScene->setScene(scene);
    viewForScene->setMouseTracking(true);
    viewForScene->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewForScene->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewForScene->setRenderHint(QPainter::Antialiasing, false);
    informationLabel = new QLabel(this);
    informationLabel->setText("TEST");
    MyTextEdit* editText = new MyTextEdit();
    QVBoxLayout* rootLayout = new QVBoxLayout(this);
    rootLayout->addWidget(informationLabel);
    rootLayout->addWidget(editText);
    rootLayout->addWidget(viewForScene);

    connect(editText, SIGNAL(removeEdge(int, int)), this, SLOT(removeEdge(int, int)));

//    VertexList vl = ::std::dynamic_pointer_cast<IGraphVerticesProvider, IGraphComplete>(graph).get()->provideVertex();

//    = ( (IGraphVerticesProvider*) graph.get())->provideVertex();

    this->setLayout(rootLayout);
}

MainWindow::~MainWindow() {
    delete this->scene;
    delete this->informationLabel;
}

void MainWindow::printGraph() {
    VertexList vl = graph->provideVertex();
    int maxX = 0, maxY = 0;
    for (QPair<int, int> vertex: vl) {
        if (vertex.first > maxX) maxX = vertex.first;
        if (vertex.second > maxY) maxY = vertex.second;
    }
    int scale = this->sceneHeight / maxY < this->sceneWidth / maxX ?
                this->sceneHeight / maxY - 1 : this->sceneWidth / maxX - 1;
    for (int i = 1; i < vl.length(); i++) {
        // TODO[#2]: fix memory leak
        QGraphicsTextItem* item = new QGraphicsTextItem();
        item->setPlainText(QString::number(i));
        item->setX(vl.at(i).first * scale);
        item->setY(vl.at(i).second * scale);
        qDebug() << "i " << i << " first " << vl.at(i).first << " second "
                 << vl.at(i).second << " first scale " << vl.at(i).first * scale
                 << " second scale " << vl.at(i).second * scale;
        this->scene->addItem(item);
    }

    EdgeList el = graph->provideEdges();
    for (int i = 0; i < el.length(); i++) {
        // TODO[#2]: fix memory leak
        QGraphicsLineItem* item = new QGraphicsLineItem(
                    vl.at(el.at(i).first).first * scale,
                    vl.at(el.at(i).first).second * scale,
                    vl.at(el.at(i).second).first * scale,
                    vl.at(el.at(i).second).second * scale
        );
        this->scene->addItem(item);
    }

//    ::std::shared_ptr<QGraphicsTextItem> item =
//            ::std::make_shared<QGraphicsTextItem>();

}

void MainWindow::removeEdge(int fv, int sv) {
    try {
        this->graph->removeEdge(fv, sv);
    } catch (CanNotRemoveEdgeException& e) {
        qDebug() << "catch" << e.what();
        this->informationLabel->setText(QString(e.what()));
        return;
    } catch (VertexNotFoundException& e) {
        qDebug() << "catch" << e.what();
        this->informationLabel->setText(QString(e.what()));
        return;
    }
    this->scene->clear();
    this->printGraph();

}
