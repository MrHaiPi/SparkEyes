#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamearea.h"
#include "gamewidget.h"
#include <QDesktopWidget>
#include <QApplication>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{   Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    gamewidget *gamewid;

    ~Widget();
    void doScore(int);
    void doHightestScore();

private slots:
    void timer_upDate();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_comboBox_activated(int index);

    void on_comboBox_2_activated(int index);

	void on_comboBox_3_activated(int index);

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_comboBox_4_activated(int index);

    void on_horizontalSlider_actionTriggered(int action);

private:
    Ui::Widget *ui;
    GameArea *gameArea;
    QTimer *timer;
    int score;//记录分数
    int leftright=0;//左右眼选择
    int speed=800;//游戏难度(初始简单，数值越小越难)

};

#endif // WIDGET_H
