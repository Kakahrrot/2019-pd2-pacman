#ifndef PAC_H
#define PAC_H
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QVector>
#include <QLabel>
#include <QObject>
#include <QTimer>
#include "block.h"
#include "node.h"

class pac :public QObject, public QGraphicsPixmapItem
{
Q_OBJECT
public:
    pac(int x, int y, int id = 0);
    virtual ~pac();
    virtual void move() = 0;
    static int size;
    static QVector<pac*> item;
    static QVector<block*> map;
    static int map_info[16][17];
    static int s;
    static QLabel *score;
    int getX() const;
    int getY() const;
    static void renewgame();//set the position of ghost after dying
    bool eaten;
    static bool attack;
    static int life;
    static bool end;
public slots:
    virtual void changepix();
    void reset_eaten();
protected:
    QPixmap pic;
    int x, y;
    int id;
    bool check(int tx, int ty);
    void changePos(int a, int b);
    static int direction;
};

#endif // PAC_H
