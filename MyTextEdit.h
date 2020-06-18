#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QLineEdit>
#include <QKeyEvent>

class MyTextEdit: public QLineEdit
{
    Q_OBJECT
public:
    MyTextEdit();
signals:
    void removeEdge(int, int);
    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MYTEXTEDIT_H


//class MyTextEdit
//{
//    Q_OBJECT
//public:
//    MyTextEdit(QWidget* parrent = nullptr) {
//    }
//    void keyPressEvent(QKeyEvent *event)
//    {
//        if (event->key() == Qt::Key_Return)
//        {
//            qDebug() << this->toPlainText();
//        }
//        else
//        {
//            QTextEdit::keyPressEvent(event);
//        }
//    }
//signals:
//    void printed(int, int);
//};
