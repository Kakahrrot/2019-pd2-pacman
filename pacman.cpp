#include "pacman.h"
pacman::pacman(int x, int y):pac(x, y)
{
    pic.load(":/picture/pacman.png");
    pic = pic.scaled(size,size);
    setPixmap(pic);
    setPos(x*size, y*size);
}

pacman::~pacman()
{
    qDebug() << "pacmen dtor called";

}

void pacman::move()
{
    switch(direction)
    {
    case 0:
        if(check(x,y-1))
            y--;
        break;
    case 1:
        if(check(x,y+1))
            y++;
        break;
    case 2:
        if(check(x-1,y))
            x--;
        break;
    case 3:
        if(check(x+1,y))
            x++;
        break;
    }
    qDebug() << "pacman coordinate" << x << y << end;
    if(x == 0 && ( y == 11 || y == 6))
        x = 15;
    else if(x == 16 && ( y == 11 || y == 6))
        x = 1;
    changePos(x,y);
}

void pacman::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Up:
        direction = 0;
        break;
    case Qt::Key_Down:
        direction = 1;
        break;
    case Qt::Key_Left:
        direction = 2;
        break;
    case Qt::Key_Right:
        direction = 3;
        break;
    }
    /*
    if(event->key() == Qt::Key_Up && !(direction = 0 )&& check(x,y-1))
        y--;
    else if(event->key() == Qt::Key_Down  && (direction = 1 )&& check(x,y+1))
        y++;
    else if(event->key() == Qt::Key_Left  && (direction = 2 )&& check(x-1,y))
        x--;
    else if(event->key() == Qt::Key_Right  && (direction = 3 )&& check(x+1,y))
        x++;
    qDebug() << "pacman coordinate" << x << y;
    setPos(x*size, y*size);
    */
}

void pacman::changepix()
{
    static int num = 0;
    if(num % 2 == 0)
    {
        pic.load(":/picture/knight.png");
        attack = true;
    }
    else
    {
        pic.load(":/picture/pacman.png");
        attack = false;
    }
    num++;
    pic = pic.scaled(size,size);
    setPixmap(pic);
}
