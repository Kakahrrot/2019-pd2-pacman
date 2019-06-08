#include "block.h"
int block::size = 50;
block::block(int x, int y, int ID):x(x), y(y), ID(ID)
{
    switch(ID)
    {
        case 0:
            pic.load(":/picture/stone.png");
            break;
        case 1:
            pic.load(":/picture/yellow-dot.png");
            break;
        case 2:
            pic.load(":/picture/red-dot.png");
            break;
        case 3:
            pic.load(":/picture/log1.png");
            break;
    }
    pic = pic.scaled(size,size);
    if(ID == 1 || ID == 3)
        pic = pic.scaled(size/2,size/2);
    setPixmap(pic);
    setPos(x*size,y*size);
    if(ID == 1 || ID == 3)
        setPos(x*size + size/4,y*size + size/4);
}

int block::getX() const
{
    return x;
}

int block::getY() const
{
    return y;
}

void block::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
   qDebug() << x << y;
}

int block::getID() const
{
    return ID;
}
