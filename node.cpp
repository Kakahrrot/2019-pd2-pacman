#include "node.h"
QVector<node*> node:: vertex;
node::node(int x, int y):x(x), y(y)
{
    distance = -1;
    parent = nullptr;
    next = nullptr;
    left = nullptr;
    right = nullptr;
    up = nullptr;
    down = nullptr;
    reachable = true;
}

void node::start(node *destination)
{
    clear();
    if(!destination->reachable)
    {
        qDebug() << "change des";
        int a = destination->x;
        int b = destination->y;
        if(a - 2 > 0 && vertex.at(a - 1 - 1 + 15*(b-1))->reachable)
            destination = vertex.at(a - 1 - 1 + 15*(b-1));
        else if(a < 15 && vertex.at(a - 1 + 1 + 15*(b-1))->reachable)
            destination = vertex.at(a - 1 + 1 + 15*(b-1));
        else if(b - 2 > 0 && vertex.at(a - 1 + 15*(b-1-1))->reachable)
            destination = vertex.at(a - 1 + 15*(b-1-1));
        else if(b < 16 && vertex.at(a - 1 + 15*(b-1+1))->reachable)
            destination = vertex.at(a - 1 + 15*(b-1+1));
        else
            return;
    }
    /*
    if(!destination->reachable)
    {
            int a = rand()%15; int b = rand()%16;
            while(!vertex.at(a + b*15)->reachable)
            {
                destination = vertex.at(a + b*15);
                a = rand()%15; b = rand()%16;
            }
    }
    */
    QVector<node*> tmp;
    distance = 0;
    tmp.append(this);
    node *t;
    while(destination->distance == -1)
    {
        int n = tmp.size();
        for(int i = 0; i < n; i++)
        {
            t = tmp.at(i);
            if(t->left != nullptr && t->left->distance == -1)
            {
                t->left->parent = t;
                t->left->distance = t->distance + 1;
                tmp.append(t->left);
            }
            if(t->right != nullptr && t->right->distance == -1)
            {
                t->right->parent = t;
                t->right->distance = t->distance + 1;
                tmp.append(t->right);
            }
            if(t->up != nullptr && t->up->distance == -1)
            {
                t->up->parent = t;
                t->up->distance = t->distance + 1;
                tmp.append(t->up);
            }
            if(t->down != nullptr && t->down->distance == -1)
            {
                t->down->parent = t;
                t->down->distance = t->distance + 1;
                tmp.append(t->down);
            }
        }
        if(tmp.size() > 0)
        {
            n = tmp.at(0)->distance;
            while(tmp.size() > 0 && tmp.at(0)->distance == n)
                tmp.removeFirst();
        }
        //if(unreachable && tmp.size() == 0)
          //  break;
    }
    t = destination;
    while(t->parent != nullptr)
    {
        t->parent->next = t;
        t = t->parent;
    }
}

//16X17


//1 1 ~ 15 16
//15 1 ->15
//1 2 ->16
void node::setrelation()
{
   int i, j;
   for(i = 1; i < vertex.size();i++)
   {
       vertex.at(i - 1)->right = vertex.at(i);
       vertex.at(i)->left = vertex.at(i - 1);
   }
   for(j = 1; j < 17; j++)
   {
       vertex.at(15*(j - 1))->left = nullptr;
       vertex.at(15 - 1 + 15*(j - 1))->right = nullptr;
   }
    for(i = 1; i < 16; i++)
    {
        for(j = 2; j < 17; j++)
        {
            vertex.at(i - 1 + 15*(j - 1))->up = vertex.at(i - 1 + 15*(j - 2));
            vertex.at(i - 1 + 15*(j - 2))->down = vertex.at(i - 1 + 15*(j - 1));
        }
    }
    //1 15 6 11
    vertex.at(1 - 1 + 15*(6-1))->left = vertex.at(15 - 1 + 15*(6-1));
    vertex.at(15 - 1 + 15*(6-1))->right = vertex.at(1 - 1 + 15*(6-1));
    vertex.at(1 - 1 + 15*(11-1))->left = vertex.at(15 - 1 + 15*(11-1));
    vertex.at(15 - 1 + 15*(11-1))->right = vertex.at(1 - 1 + 15*(11-1));
}

void node::setwall(int a, int b)
{
    node* t = vertex.at(a - 1 + 15*(b - 1));
    t->reachable = false;
    if(t->right != nullptr)
        t->right->left = nullptr;
    if(t->left != nullptr)
        t->left->right = nullptr;
    if(t->up != nullptr)
        t->up->down = nullptr;
    if(t->down != nullptr)
        t->down->up = nullptr;
    t->right = nullptr;
    t->left = nullptr;
    t->up = nullptr;
    t->down = nullptr;
}

int node::getX() const
{
    return x;
}

int node::getY() const
{
    return y;
}

void node::clear()
{
    for(int i = 0; i < vertex.size(); i++)
    {
        vertex.at(i)->parent = nullptr;
        vertex.at(i)->next = nullptr;
        vertex.at(i)->distance = -1;
    }
}
