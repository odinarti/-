#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QLabel>
#include <QWidget>

#include "graph_interfaces/IGraphComplete.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printGraph();

    ::std::shared_ptr<IGraphComplete> graph;
    QGraphicsScene* scene;
    QLabel* informationLabel;
    int sceneHeight = 480;
    int sceneWidth = 640;
public slots:
    void removeEdge(int, int);
};
#endif // MAINWINDOW_H
