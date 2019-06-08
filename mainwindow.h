#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QVector>
#include <QMouseEvent>
#include <QPalette>
#include <QTimer>
#include "pac.h"
#include "ghost.h"
#include "pacman.h"
#include "block.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *enent);

public slots:
    void moveghost();
    void movepacman();
private:
    void gameover();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QVector<block*> map;
    void setmap();
    void setitem();
    void setnode();
    QPalette *p;
    QPixmap *t;
    QTimer *timerghost;
    QTimer *timerpacman;
    QLabel *mylabel;
};

#endif // MAINWINDOW_H
