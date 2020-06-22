#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include "gamearea.h"
#include <QColor>
#include <QDesktopWidget>
#include <QApplication>
namespace Ui {
class gamewidget;
}

class gamewidget : public QWidget
{
    Q_OBJECT

public:
    explicit gamewidget(QWidget *parent = 0);
    ~gamewidget();

    int a;//记录分数
    int b;
    int mode=0;//显示模式指示变量,0为左右分视，1为偏正显示
    void score_change();
    QColor boxBrushColor=Qt::green;
    QColor boxBrushColor1=Qt::green;

private:

    Ui::gamewidget *ui;

};

#endif // GAMEWIDGET_H
