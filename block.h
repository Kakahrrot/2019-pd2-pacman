#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>

class block: public QGraphicsPixmapItem
{
public:
    block(int x, int y, int ID = 0);
    static int size;
    int getX() const;
    int getY() const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    int getID() const;
private:
    QPixmap pic;
    int x;
    int y;
    int ID;
};

#endif // BLOCK_H
