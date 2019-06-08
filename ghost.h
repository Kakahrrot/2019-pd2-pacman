#ifndef GHOST_H
#define GHOST_H
#include <QDebug>
#include "pac.h"
#include <QGraphicsScene>
class ghost:public pac
{
public:
    ghost(int x, int y, int id);
    ~ghost();
    void move();
    static QGraphicsScene* scene;
private:
    int targetx,targety;
    void settarget1();
    void settarget2();
    void settarget3();
    void settarget4();
    QVector<block*> path;
    static int dx[5];
    static int dy[5];
    bool newtarget;
};

#endif // GHOST_H
