#include <QDebug>

#include "MyTextEdit.h"

MyTextEdit::MyTextEdit()
{}

void MyTextEdit::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return)
   {
        QString s = this->text();
        QStringList sl = s.split(" ");
        if (sl.length() != 2) {
            qDebug() << "THIS IS NOT PAIR of vertex";
            this->clear();
            return;
        }
        bool ok;
        int fv = sl[0].toInt(&ok);
        if (!ok) {
            qDebug() << sl[0] << " NAN";
            this->clear();
            return;
        }
        int sv = sl[1].toInt(&ok);
        if (!ok) {
            qDebug() << sl[1] << " NAN";
            this->clear();
            return;
        }
        qDebug() << fv << sv;
        this->clear();
        emit removeEdge(fv, sv);
   }
   else
   {
       QLineEdit::keyPressEvent(event);
   }
}
