#ifndef NODE_H
#define NODE_H
#include <QVector>
#include <QDebug>



class node
{
public:
    node(int x, int y);
    void start(node* destination);
    node* next;
    static QVector<node*> vertex;
    static void setrelation();
    static void setwall(int a, int b);
    int getX() const;
    int getY() const;
    bool reachable;
private:
    int x, y;
    int distance;
    node* parent, *left, *right, *up, *down;
    static void clear();
};

#endif // NODE_H
