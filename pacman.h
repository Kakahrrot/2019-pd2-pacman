#ifndef PACMAN_H
#define PACMAN_H
#include "pac.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class pacman :public pac
{
public:
    pacman(int x, int y);
    ~pacman();
    void move();
    void keyPressEvent(QKeyEvent *event);
public slots:
    void changepix();

};

#endif // PACMAN_H
