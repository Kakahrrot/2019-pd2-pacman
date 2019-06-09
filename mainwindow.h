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
    void startgame();
    void Pause_Resume_game();
private:
    void gameover();
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    void setmap();
    void setitem();
    void setnode();
    QPalette *p;
    QPixmap *t;
    QTimer *timerghost;
    QTimer *timerpacman;
    QLabel *mylabel;
    QPushButton *start;
    QPushButton *pause_resume;
};

#endif // MAINWINDOW_H
