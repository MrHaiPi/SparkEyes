/**********************???????****************************

???????????www.yafeilinux.com????????????Qt????????????????????????

????????????????????????????????????????

??????????????www.yafeilinux.com????????????????????


**********************************************************/

#ifndef GAMEAREA_H
#define GAMEAREA_H

#include <QFrame>
#include "myitem.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QDesktopWidget>
#include <QApplication>

namespace gameArea {
    class GameArea;
}

class GameArea : public QFrame {
    Q_OBJECT

public:
    GameArea(QWidget *parent = 0); //????????????????
    GameArea(int speed,QWidget *parent = 0); //??????????????

    ~GameArea();

public:
    int left_right=0;
    bool is_stop=true;//游戏暂停指示变量
	bool mode=0;//游戏模式
    int color_model=0;//颜色模式指示变量
    int ismoveend=0;//方块是否落到底指示变量
    float transparency=255;//透明度
    QColor green_change=QColor(0,255,0,transparency);//可调节的绿色
    //??????????????????
    void init_gameArea(int X,int Y,int frame_width,int frame_height,int width,int height,int boxStep,int start_x,int start_y);
    void moveOneStep();
    bool isMoveEnd();
    bool isGame_Over();
    void init_Game();
    void gameStart();
    void nextItem();
    int getFullRowNum();
    void do_MoveNext();
    void draw_gameArea();

    //?????????????????
    //左侧区域设置
    void setGameAreaColor(QColor color=Qt::white);
    void setBoxBrushColor(QColor color=Qt::green);
    void setBoxPenColor(QColor color=Qt::black);
    //左侧区域设置
    void setGameAreaColor1(QColor color=Qt::white);
    void setBoxBrushColor1(QColor color=Qt::green);
    void setBoxPenColor1(QColor color=Qt::black);

    void set_draw_box_picture(bool Bool=false);
    void setBoxPicture(QString fileName);

    //??????????????????
    void setPlaySound_moveLeft(QString fileName,bool Bool=false);
    void setPlaySound_moveRight(QString fileName,bool Bool=false);
    void setPlaySound_moveDown(QString fileName,bool Bool=false);
    void setPlaySound_itemChange(QString fileName,bool Bool=false);
    void setPlaySound_clear(QString fileName,bool Bool=false);
    void setPlaySound(bool Bool=false);

    //????????????????????????
    void setRotate(bool Bool=false);
    void setGameAreaPixOrigin(int x,int y);
    void setGameAreaPix(int x,int y);
    void setRotateAngle(int angle);

    //?????????????????
    void setKey_Down_Move_oneStep(bool Bool = false);
    void setDrawGrid(bool Bool = true);
    void setDrawNextItem(bool Bool =true);
    void setbox(int row,int col);

private:
    void playSound(QString fileName);
    void init_Map(unsigned char *initMap,int row,int col);
    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);
    void draw_Grid();
    void currentItem_to_currentMap();
    void copy_Map(unsigned char *theMap,unsigned char *toMap,int row,int col);
    void draw_currentMap();
    bool isMoveLeft();
    bool isMoveRight();
    void draw_nextItem();
    void do_itemChange();
    void clearRow();

private:

    int gameArea_width;
    int gameArea_height;
    int map_row;
    int map_col;
    int startX;
	int startX1;
    int startY;
    int step;
    int init_startX;
	int init_startX1;
    int init_startY;
    unsigned char *currentMap;
    unsigned char *copyMap;

    QPixmap *pix_gameArea;
    QPixmap *pix_gameArea1;

    MyItem *myItem;
    unsigned char *currentItem;
    unsigned char *theNextItem;
    bool isFirstItem;
    bool isGameOver;
    int fullRowNum;
    //左区域颜色
    QColor gameAreaColor;
    QColor boxPenColor;
    QColor boxBrushColor;
    //右区域颜色
    QColor gameAreaColor1;
    QColor boxPenColor1;
    QColor boxBrushColor1;

    bool isKey_Down_Move_OneStep;

    bool isDrawGrid;
    bool isDrawNextItem;
    bool isPlaySound_moveLeft;
    bool isPlaySound_moveRight;
    bool isPlaySound_moveDown;
    bool isPlaySound_itemChange;
    bool isPlaySound_clear;
    QString sound_moveLeft;
    QString sound_moveRight;
    QString sound_moveDown;
    QString sound_itemChange;
    QString sound_clear;

    bool isRotate;
    int theAngle;
    int gameArea_X;
	int gameArea_X1;
    int gameArea_Y;
    int pix_X;
	int pix_X1;
    int pix_Y;

    bool is_draw_box_picture;
    QString boxPicture;
    QTimer *moveTimer;

    int moveSpeed;

private slots:
    void moveTimer_upDate();

};

#endif // GAMEAREA_H
