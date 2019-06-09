#include "pac.h"
int pac::size = 50;
QVector<block*> pac::map;
QVector<pac*> pac::item;
int pac::map_info[16][17] = {{0}};
int pac::s = 0;
QLabel* pac::score = nullptr;
int pac::direction = 4;
bool pac::attack = false;
int pac::life = 5;
bool pac::end = false;
int pac::ghostspeed = 500;

pac::pac(int x, int y, int id): eaten(false), x(x), y(y),id(id)
{

}

pac::~pac()
{

}

int pac::getX() const
{
    return x;
}

int pac::getY() const
{
    return y;
}

void pac::changepix()
{
}

void pac::reset_eaten()
{
   eaten = false;
}

bool pac::check(int tx, int ty)
{
    int i;
    for(i = 0; i < map.size() && map.at(i)->getID() == 0;i++)
        if(map.at(i)->getX() == tx && map.at(i)->getY() == ty)
            return false;
    static int num = i;//for gameover
    for(;i < map.size() && map.at(i) != nullptr;i++)
    {
        //id == 0 -> player
        if(id == 0 && map.at(i)->getID() == 1 && map.at(i)->getX() == tx && map.at(i)->getY() == ty)
        {
            //yellow dot
            ghostspeed--;
            delete map.at(i);
            map.remove(i);
            s += 100;
            score->setText(QString::number(s));
            qDebug() << "yellow";
            if(map.size() == num)
                end = true;
        }
        else if(id == 0 && map.at(i)->getID() == 2 && map.at(i)->getX() == tx && map.at(i)->getY() == ty)
        {
            //red dot
            ghostspeed -= 25;
            delete map.at(i);
            map.remove(i);
            s += 1000;
            score->setText(QString::number(s));
            changepix();
            QTimer::singleShot(10000, this, SLOT(changepix()));
            if(map.size() == num)
                end = true;
        }
    }
    return true;
}

void pac::changePos(int a, int b)
{
    x = a;y = b;
    setPos(a*size, b*size);
}

void pac::renewgame()
{
    static int newx[5] = {7,6,10,6,10};
    static int newy[5] = {15,8,8,9,9};
    if(!attack)
    {
        item.at(0)->changePos(newx[0],newy[0]);
        item.at(0)->eaten = false;
        life--;
        direction = 4;
        if(life == 0)
            end = true;
    }
    else {
    for(int i = 1; i < item.size();i++)
    {
        if(item.at(i)->eaten)
        {
            item.at(i)->changePos(newx[i],newy[i]);
            s += 5000;
            score->setText(QString::number(s));
            QTimer::singleShot(5000,item.at(i), SLOT(reset_eaten()));
        }
    }
    }
    /*
    item.at(0)->changePos(7, 15);
    item.at(1)->changePos(6, 8);
    item.at(2)->changePos(10, 8);
    item.at(3)->changePos(6, 9);
    item.at(4)->changePos(10, 9);
    */
}
