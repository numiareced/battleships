#include "onepalub.h"

#include <QtGui>
OnePalub::OnePalub(QWidget *parent)
     : QLabel(parent){
    pix = new QLabel(this);
    pix->setPixmap(QPixmap("images/ship1p.png"));
    pix->move(10,10);
    pix->show();
    setFixedSize(200,60);
}

void OnePalub::mousePressEvent(QMouseEvent *event){

    QLabel *child = static_cast<QLabel*>(childAt(event->pos()));
    if (!child)
        return;
    QString isVertical;

    isVertical="application/x-1s";
    QPixmap pixmap = *child->pixmap();
    QByteArray itemData;
    QDataStream dataStream(&itemData, QIODevice::WriteOnly);
    dataStream << pixmap << QPoint(event->pos() - child->pos());
    QMimeData *mimeData = new QMimeData;
    mimeData->setData(isVertical, itemData);

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    drag->setPixmap(pixmap);
    drag->setHotSpot(event->pos() - child->pos());

    QPixmap tempPixmap = pixmap;
    QPainter painter;
    painter.begin(&tempPixmap);
    painter.fillRect(pixmap.rect(), QColor(127, 127, 127, 127));
    painter.end();

    child->setPixmap(tempPixmap);


    if (drag->exec(Qt::CopyAction | Qt::MoveAction, Qt::CopyAction) == Qt::MoveAction)
        child->close();
    else {
        child->show();
        child->setPixmap(pixmap);
    }
}


void OnePalub::dragMoveEvent(QDragMoveEvent *event){

    if (event->mimeData()->hasFormat("image/png")) {
             event->setDropAction(Qt::MoveAction);
             event->accept();
     }
    else
             event->ignore();

}
