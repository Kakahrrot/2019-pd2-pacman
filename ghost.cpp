#include "ghost.h"
QGraphicsScene* ghost::scene = nullptr;
int ghost::dx[5] = {0,0,-2,2,0};
int ghost::dy[5] = {-2,2,0,0,0};
ghost::ghost(int x, int y, int id):pac(x,y,id),targetx(0),targety(0)
{
    switch(id)
    {
    case 1:
        pic.load(":/picture/red-ghost.png");
        break;
    case 2:
        pic.load(":/picture/white-ghost.png");
        break;
    case 3:
        pic.load(":/picture/blue-ghost.png");
        break;
    case 4:
        pic.load(":/picture/mouse-ghost.png");
        break;
    }
    pic = pic.scaled(size,size);
    setPixmap(pic);
    setPos(x*size, y*size);
    newtarget = true;
}

ghost::~ghost()
{
    while(!path.isEmpty())
    {
        delete path.at(0);
        path.removeFirst();
    }
}

void ghost::move()
{
    if(eaten)
        return;
    while(!path.isEmpty())
    {
        delete path.at(0);
        path.removeFirst();
    }
    if(newtarget)
    {
        qDebug() << "trarget got" << id;
        switch(id)
        {
        case 1:
            settarget1();
            break;
        case 2:
            settarget2();
            break;
        case 3:
            settarget3();
            break;
        case 4:
            settarget4();
            break;
        }
    }
    if(!((targetx == 1 || targetx == 15) && (targety == 6 || targety == 11)))
    {
        targetx = (targetx < 2)?2:targetx;
        targety = (targety < 2)?2:targety;
        targetx = (targetx > 14)?14:targetx;
        targety = (targety > 15)?15:targety;
    }
    node* t = node::vertex.at(x - 1+ 15*(y-1));
    node* d = node::vertex.at(targetx - 1 + 15*(targety-1));

    t->start(d);
    while(t->next == nullptr || (t->next->getX() == x && t->next->getY() == y))
    {
        int a = rand()%15; int b = rand()%16;
        while(!node::vertex.at(a + b*15)->reachable)
        {
            d = node::vertex.at(a + b*15);
            a = rand()%15; b = rand()%16;
        }
        t->start(d);
        newtarget = true;
    }
    this->changePos(t->next->getX(),t->next->getY());
    if(x == targetx && y == targety)
        newtarget = true;
    if(id == 1)
    {
        block* p;
        t = t->next;
        while(t->next != nullptr)
        {
            t = t->next;
            p = new block(t->getX(), t->getY(),3);
            path.append(p);
            scene->addItem(p);
        }

    }
}

void ghost::settarget1()
{
    newtarget = false;
    targetx = 2;
    targety = 2;
    targetx = item.at(0)->getX();
    targety = item.at(0)->getY();
}

void ghost::settarget2()
{
    newtarget = false;
    //targetx = item.at(0)->getX();
    //targety = item.at(0)->getY();
    targetx = (item.at(0)->getX() + dx[direction]);
    targety = (item.at(0)->getY() + dy[direction]);
}

void ghost::settarget3()
{
    newtarget = false;
    targetx = 2*(item.at(0)->getX()+ dx[direction]) - item.at(1)->getX();
    targety = 2*(item.at(0)->getY()+ dy[direction]) - item.at(1)->getY();
}

void ghost::settarget4()
{
    newtarget = false;
    int dis = abs(x - item.at(0)->getX())*abs(x - item.at(0)->getX())
                    + abs(y - item.at(0)->getY())*abs(y - item.at(0)->getY());
    if(dis < 64)
    {
        targetx = 2;
        targety = 2;
    }
    else
    {
        targetx = item.at(0)->getX();
        targety = item.at(0)->getY();
    }
}
