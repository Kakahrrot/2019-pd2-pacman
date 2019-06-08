#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ghost::scene = scene;
    view = new QGraphicsView(this);
    view->setScene(scene);
    view->setGeometry(0,0,1850,900);
    setmap();
    setitem();
    setnode();
    timerghost = new QTimer(this);
    timerpacman = new QTimer(this);
    connect(timerghost,SIGNAL(timeout()), this, SLOT(moveghost()));
    connect(timerpacman,SIGNAL(timeout()), this, SLOT(movepacman()));
    timerghost->start(500);
    timerpacman->start(250);
    QFont f( "Arial", 50, QFont::Bold);
    pac::score = new QLabel(this);
    pac::score->setFont(f);
    pac::score->setGeometry(0,0,900,50);
    pac::score->setText(QString::number(pac::s));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug() << event->pos();
}


void MainWindow::setmap()
{
    block *b;
    for(int i = 1; i < 16; i++)
    {
        b = new block(i,1);
        map.append(b);
        scene->addItem(b);
        b = new block(i,16);
        map.append(b);
        scene->addItem(b);
    }
    for(int j = 2; j < 16; j++)
    {
        if(j != 6 && j != 11)
        {
            b = new block(1,j);
            map.append(b);
            scene->addItem(b);
            b = new block(15,j);
            map.append(b);
            scene->addItem(b);
        }
    }

    for(int i = 5; i < 12; i++)//middle rec
    {
        if(i != 8)
        {
            b = new block(i,7);
            map.append(b);
            scene->addItem(b);
        }
        b = new block(i,10);
        map.append(b);
        scene->addItem(b);
    }
    for(int j = 8; j < 10; j++)
    {
        b = new block(5,j);
        map.append(b);
        scene->addItem(b);
        b = new block(11,j);
        map.append(b);
        scene->addItem(b);
    }
    for(int j = 4; j < 14; j++)
    {
        if(j != 9)
        {
            b = new block(3,j);
            map.append(b);
            scene->addItem(b);
            b = new block(13,j);
            map.append(b);
            scene->addItem(b);
        }
    }
    for(int i = 4; i < 7;i++)
    {
        b = new block(i, 5);
        map.append(b);
        scene->addItem(b);
        b = new block(i+6, 5);
        map.append(b);
        scene->addItem(b);
        b = new block(i, 12);
        map.append(b);
        scene->addItem(b);
        b = new block(i+6, 12);
        map.append(b);
        scene->addItem(b);
    }
    b = new block(10, 3);
    map.append(b);
    scene->addItem(b);
    b = new block(11, 3);
    map.append(b);
    scene->addItem(b);
    b = new block(5, 3);
    map.append(b);
    scene->addItem(b);
    b = new block(6, 3);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 3);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 4);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 5);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 12);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 13);
    map.append(b);
    scene->addItem(b);
    b = new block(8, 14);
    map.append(b);
    scene->addItem(b);
    b = new block(10, 14);
    map.append(b);
    scene->addItem(b);
    b = new block(11, 14);
    map.append(b);
    scene->addItem(b);
    b = new block(5, 14);
    map.append(b);
    scene->addItem(b);
    b = new block(6, 14);
    map.append(b);
    scene->addItem(b);
    // set map information
    for(int i = 0; i < map.size();i++)
        pac::map_info[map.at(i)->getX()][map.at(i)->getY()] = 1;
    // red dots
    b = new block(2,2,2);
    map.append(b);
    scene->addItem(b);
    pac::map_info[2][2] = 2;
    b = new block(14,2,2);
    map.append(b);
    scene->addItem(b);
    pac::map_info[14][2] = 2;
    b = new block(2,15,2);
    map.append(b);
    scene->addItem(b);
    pac::map_info[2][15] = 2;
    b = new block(14,15,2);
    map.append(b);
    scene->addItem(b);
    pac::map_info[14][15] = 2;

    //yellow dots
    //for(int i = 2; i < 15; i++)
    for(int i = 2; i < 3; i++)
    {
        for(int j = 2; j < 16; j++)
        {
            if(pac::map_info[i][j] == 0)
            {
                b = new block(i,j,1);
                map.append(b);
                pac::map_info[i][j] = 1;
                scene->addItem(b);
            }
        }
    }
    for(int i = 0; i < map.size();i++)//set static map in pac
        pac::map.append(map.at(i));
}

void MainWindow::setitem()
{
    pac *p = new pacman(2,4);
    p->setFlag(QGraphicsItem::ItemIsFocusable);
    p->setFocus();
    scene->addItem(p);
    pac::item.append(p);
    p = new ghost(14,13,1);
    pac::item.append(p);
    scene->addItem(p);
    p = new ghost(10,8,2);
    pac::item.append(p);
    scene->addItem(p);
    p = new ghost(6,9,3);
    pac::item.append(p);
    scene->addItem(p);
    p = new ghost(10,9,4);
    pac::item.append(p);
    scene->addItem(p);
}

void MainWindow::setnode()
{
    int i,j;
    node* t;
    for(j = 1; j <= 16; j++)
    {
        for(i = 1; i <= 15; i++)
        {
            t = new node(i, j);
            node::vertex.append(t);
        }
    }
    node::setrelation();
    for(i = 0; pac::map.at(i)->getID() == 0;i++)
        node::setwall(pac::map.at(i)->getX(), pac::map.at(i)->getY());
}

void MainWindow::moveghost()
{
    for(int i = 1; i < pac::item.size(); i++)
        pac::item.at(i)->move();
}

void MainWindow::movepacman()
{
    pac::item.at(0)->move();
    static int prex[5] = {0,1,2,3,4};
    static int prey[5] = {0,1,2,3,4};
    prex[0] = pac::item.at(0)->getX();
    prey[0] = pac::item.at(0)->getY();
    for(int i = 1; i < pac::item.size();i++)
    {
        if((pac::item.at(0)->getX() == pac::item.at(i)->getX()
            && pac::item.at(0)->getY() == pac::item.at(i)->getY())
            ||(prex[0] == prex[i] && prey[0] == prey[i]))
        {
            if(pac::attack)
                pac::item.at(i)->eaten = true;
            else
            {
                pac::item.at(0)->eaten = true;
                pac::renewgame();
                break;
            }
            pac::renewgame();
        }
    }
    for(int i = 1; i < pac::item.size();i++)
    {
        prex[i] = pac::item.at(i)->getX();
        prey[i] = pac::item.at(i)->getY();
    }
    if(pac::end)
        gameover();
    /*
    if((pac::item.at(0)->getX() == pac::item.at(1)->getX() && pac::item.at(0)->getY() == pac::item.at(1)->getY())
        ||(pac::item.at(0)->getX() == pac::item.at(2)->getX() && pac::item.at(0)->getY() == pac::item.at(2)->getY())
        ||(pac::item.at(0)->getX() == pac::item.at(3)->getX() && pac::item.at(0)->getY() == pac::item.at(3)->getY())
        ||(pac::item.at(0)->getX() == pac::item.at(4)->getX() && pac::item.at(0)->getY() == pac::item.at(4)->getY()))
        pac::renewgame();
        */
}

void MainWindow::gameover()
{
   qDebug() << "gameover";
   timerghost->stop();
   timerpacman->stop();
   delete timerghost;
   delete timerpacman;
   for(int i = 0; i < pac::item.size();i++)
       delete pac::item.at(i);
   mylabel = new QLabel();
   mylabel->setGeometry(100,100,170,100);
   QFont f( "Arial", 50, QFont::Bold);
   mylabel->setFont(f);
   if(pac::life == 0)
       mylabel->setText("Lose");
   else
       mylabel->setText("Win");
   mylabel->show();

}
