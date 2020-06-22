/**********************版权声明****************************

所有源代码由www.yafeilinux.com原创，我们遵循Qt开源版的所有相关条款和协议。

您有权使用，传播和更改我们的代码，但请保证代码的开源。

以下源代码版权归www.yafeilinux.com所有，请不要用作商业用途。


**********************************************************/

//这个类中实现了游戏的所有功能
#include "gamearea.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QSound>
#include <QDesktopWidget>
#include <QApplication>
/****************************以下是构造函数和析构函数*********************************************************/


GameArea::GameArea(QWidget *parent) :
    QFrame(parent)
{
	setWindowState(Qt::WindowMaximized);
	this->init_gameArea(110, 20, QApplication::desktop()->width(), QApplication::desktop()->height(), QApplication::desktop()->width() / 3 - 8 - QApplication::desktop()->width() / 3 / 7, QApplication::desktop()->height() - 134, QApplication::desktop()->width() / 3 / 14, 220, 0);
	this->init_Game();
}


GameArea::GameArea(int speed,QWidget *parent) :
    QFrame(parent)
{
    this->init_gameArea(QApplication::desktop()->width() / 10, 15, QApplication::desktop()->width(), QApplication::desktop()->height(), QApplication::desktop()->width() / 4 - 3, QApplication::desktop()->height() - 128, QApplication::desktop()->width() / 4 / 14, 60, 0);
    this->init_Game();
    this->moveTimer = new QTimer(this);
    connect(this->moveTimer,SIGNAL(timeout()),this,SLOT(moveTimer_upDate()));
    this->moveSpeed = speed;
    this->gameStart();
}

GameArea::~GameArea()
{

}
/****************************以下是主要功能函数*********************************************************/

//方块下移一步
void GameArea::moveOneStep()
{
     startY += step;
}

//显示下移一步后的界面
void GameArea::do_MoveNext()
{
    this->currentItem_to_currentMap();
    this->draw_gameArea();
}

//先将现在的游戏区域备份再消行
void GameArea::nextItem()
{
    copy_Map(currentMap,copyMap,map_row,map_col);
    this->clearRow();
}

//游戏是否已经结束
bool GameArea::isGame_Over()
{
    if(this->isGameOver) return true;
    else return false;
}

//获取已满的行数
int GameArea::getFullRowNum()
{
    return fullRowNum;
}

//设置方块颜色或贴图(left)
void GameArea::setGameAreaColor(QColor color)
{
    gameAreaColor = color;
}

void GameArea::setBoxBrushColor(QColor color)
{
    boxBrushColor = color;
}

void GameArea::setBoxPenColor(QColor color)
{
    boxPenColor = color;
}

//设置方块颜色或贴图(right)
void GameArea::setGameAreaColor1(QColor color)
{
    gameAreaColor1 = color;
}

void GameArea::setBoxBrushColor1(QColor color)
{
    boxBrushColor1 = color;
}

void GameArea::setBoxPenColor1(QColor color)
{
    boxPenColor1 = color;
}

//设置方块颜色或贴图
void GameArea::set_draw_box_picture(bool Bool)
{
    this->is_draw_box_picture = Bool;
}

void GameArea::setBoxPicture(QString fileName)
{
    this->boxPicture = fileName;
}


//是否下移一步,如果不是则一次下移到底
void GameArea::setKey_Down_Move_oneStep(bool Bool)
{
    this->isKey_Down_Move_OneStep = Bool;
}



//是否显示网格
void GameArea::setDrawGrid(bool Bool)
{
    isDrawGrid = Bool;
}

//是否显示下一个要出现的图形
void GameArea::setDrawNextItem(bool Bool)
{
    isDrawNextItem = Bool;
}

//自己往游戏区添加方块
void GameArea::setbox(int row,int col)
{
    *(copyMap+row*map_col+col) = 1;
}


//是否播放声音
void GameArea::setPlaySound_moveLeft(QString fileName,bool Bool)
{
    this->isPlaySound_moveLeft = Bool;
    this->sound_moveLeft = fileName;
}

void GameArea::setPlaySound_moveRight(QString fileName,bool Bool)
{
    this->isPlaySound_moveRight = Bool;
    this->sound_moveRight = fileName;
}

void GameArea::setPlaySound_moveDown(QString fileName,bool Bool)
{
    this->isPlaySound_moveDown = Bool;
    this->sound_moveDown = fileName;
}

void GameArea::setPlaySound_itemChange(QString fileName,bool Bool)
{
    this->isPlaySound_itemChange = Bool;
    this->sound_itemChange = fileName;
}

void GameArea::setPlaySound_clear(QString fileName,bool Bool)
{
    this->isPlaySound_clear = Bool;
    this->sound_clear = fileName;
}

void GameArea::setPlaySound(bool Bool)
{
    this->isPlaySound_moveLeft = Bool;
    this->isPlaySound_moveRight = Bool;
    this->isPlaySound_moveDown = Bool;
    this->isPlaySound_itemChange = Bool;
    this->isPlaySound_clear = Bool;
}
//是否播放声音



/***设置游戏区域旋转****/

void GameArea::setRotate(bool Bool) //开启旋转
{
    this->isRotate = Bool;
}

void GameArea::setRotateAngle(int angle) //顺时针旋转角度
{
    this->theAngle = angle;
}

void GameArea::setGameAreaPixOrigin(int x,int y) //新的坐标原点
{
    this->gameArea_X = x;
    this->gameArea_X1 = x;
    this->gameArea_Y = y;
}

void GameArea::setGameAreaPix(int x,int y) //游戏区域的位置
{
    this->pix_X = x;
    this->pix_X1 = x;
    this->pix_Y = y;
}

/*****设置旋转******/


/****************************以上是主要功能函数*********************************************************/



/****************************以下是核心功能函数*********************************************************/


void GameArea::init_gameArea(int X,int Y,int frame_width,int frame_height,int width,int height,int boxStep,int start_x,int start_y)
        //初始化游戏区域,起始位置，宽，高，小方块边长,图形出现位置
{
    this->gameArea_width = width;
    this->gameArea_height = height;
    this->step = boxStep;
    this->init_startX = start_x;
	this->init_startX1 = start_x;
    this->init_startY = start_y;
    this->map_row = gameArea_height / step;
	if(mode==0)
    this->map_col = gameArea_width /step;
	if (mode ==1)
	this->map_col = gameArea_width *2/ step;

    this->resize(frame_width,frame_height);
    //将游戏区域设置为较大的正方形
    this->move(X,Y);
	if (mode == 0) {
		pix_gameArea = new QPixmap(this->gameArea_width, this->gameArea_height);
		pix_gameArea1 = new QPixmap(this->gameArea_width, this->gameArea_height);
	}
	if (mode == 1) {
		pix_gameArea = new QPixmap(this->gameArea_width-5, this->gameArea_height);
		pix_gameArea1 = new QPixmap(this->gameArea_width-5, this->gameArea_height);
	}
    this->isKey_Down_Move_OneStep =false;

    //默认状态设置
    this->isDrawGrid = true;
    this->isDrawNextItem=true;
    this->isPlaySound_moveLeft = false;
    this->isPlaySound_moveRight = false;
    this->isPlaySound_moveDown = false;
    this->isPlaySound_itemChange =false;
    this->is_draw_box_picture = false;

    //默认颜色设置(left_area)
    this->gameAreaColor = Qt::black;
    this->boxBrushColor = Qt::green;
    this->boxPenColor = Qt::black;
    //默认颜色设置(right_area)
    this->gameAreaColor1 = Qt::black;
    this->boxBrushColor1 = Qt::green;
    this->boxPenColor1 = Qt::black;

    this->isRotate = false;
    this->theAngle = 0;
    this->gameArea_X = 0;
	this->gameArea_X1 = QApplication::desktop()->width() / 2;
    this->gameArea_Y = 0;
    this->pix_X = 10;
	this->pix_X1 = QApplication::desktop()->width() / 2+10;
    this->pix_Y = 10;

    myItem = new MyItem();

    this->currentMap = new unsigned char[map_row*map_col];
    this->copyMap = new unsigned char[map_row*map_col];

}

void GameArea::init_Game() //第一次进入游戏时对一些变量进行初始化
{
    this->init_Map(currentMap,map_row,map_col);
    this->init_Map(copyMap,map_row,map_col);

    this->currentItem = this->currentMap;   //对两个指针进行初始化
    this->theNextItem = this->currentMap;   //让两个指针均指向清空的数组

    isFirstItem = true;
    isGameOver = false;
    fullRowNum = 0;

    this->draw_gameArea();
}

void GameArea::gameStart() //游戏开始运行，而且每次出现新的方块都调用一次这个函数
{
    ismoveend=0;

    this->startX = this->init_startX;
	this->startX1 = this->init_startX1;
    this->startY = this->init_startY;
    fullRowNum = 0; //每次出现一个新的图形都将上次满的行数清0
    if(isFirstItem)
    {
        this->currentItem = myItem->getItem();
        isFirstItem = false;
    }
    else this->currentItem = this->theNextItem;
    this->theNextItem = myItem->getItem();
    this->currentItem_to_currentMap();
    this->draw_gameArea();


}

void GameArea::init_Map(unsigned char *initMap,int row,int col)
        //用于让一个数组中的数全部为0
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            *(initMap+i*col+j)= 0;
        }
    }
}

void GameArea::draw_gameArea()  //绘制游戏区域，包括网格和游戏区的方块
{
    this->pix_gameArea->fill(gameAreaColor);
    this->pix_gameArea1->fill(gameAreaColor1);

    if(this->isDrawGrid)//画网格
    {
        draw_Grid();
    }
    draw_currentMap();
    update();
}

void GameArea::draw_Grid()   //绘制游戏区域背景的网格
{
    QPainter painter(this->pix_gameArea);
    QPainter painter1(this->pix_gameArea1);   
    painter.setPen(QPen(Qt::white,0.25,Qt::DotLine));
    painter1.setPen(QPen(Qt::white,0.25,Qt::DotLine));

    for(int i=0; i<map_row+1; i++)
    {
        painter.drawLine(QPoint(0,i*step),QPoint(this->gameArea_width,i*step));
        painter1.drawLine(QPoint(0,i*step),QPoint(this->gameArea_width,i*step));
    }
    for(int j=0; j<map_col+1; j++)
    {
		if (mode == 1) {
			painter.drawLine(QPoint(j*(step / 2), 0), QPoint(j*(step / 2), this->gameArea_height));//一半宽
			painter1.drawLine(QPoint(j*(step / 2), 0), QPoint(j*(step / 2), this->gameArea_height));//一半宽
		}
		if (mode == 0) {
			painter.drawLine(QPoint(j*step , 0), QPoint(j*step , this->gameArea_height));
			painter1.drawLine(QPoint(j*step, 0), QPoint(j*step , this->gameArea_height));
		}
    }
}

void GameArea::draw_currentMap()
        //绘制游戏区域现在已有的方块
{
    QPainter painter(this->pix_gameArea);
    painter.setPen(this->boxPenColor);
    painter.setBrush(this->boxBrushColor);

    QPainter painter1(this->pix_gameArea1);
    painter1.setPen(this->boxPenColor1);
    painter1.setBrush(this->boxBrushColor1);

    for(int i=0;i<map_row;i++)    //将网格上的图形显示到界面上
    {
        for(int j=0;j<map_col;j++)
       {

             if(*(currentMap+i*map_col+j)-*(copyMap+i*map_col+j)==1)//绘制所有方块
             {
                 if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
                    if (mode == 1) {
                        painter.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//一半宽
                        painter1.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//一半宽
                    }
                    if (mode == 0) {
                        painter.drawPixmap(j*step, i*step, step , step, pix);
                        painter1.drawPixmap(j*step , i*step, step , step, pix);
                    }
                 }
//                 if(color_model==0&&ismoveend==1){

////                     painter.setPen(Qt::black);
////                     painter.setBrush(green_change);
////                     painter1.setPen(Qt::black);
////                     painter1.setBrush(green_change);
//                     painter1.setPen(this->boxPenColor);
//                     painter1.setBrush(this->boxBrushColor);
//                     painter.setPen(this->boxPenColor1);
//                     painter.setBrush(this->boxBrushColor1);

//                  }
                 if (mode == 1) {
                     painter.drawRect(j*(step / 2), i*step, step / 2, step);//一半宽
                     painter1.drawRect(j*(step / 2), i*step, step / 2, step);//一半宽
                 }
                 if (mode == 0) {
                     painter.drawRect(j*step, i*step, step, step);
                     painter1.drawRect(j*step, i*step, step , step);
                 }

             }

             if(*(copyMap+i*map_col+j)==1)//绘制已经落下的方块
             {
                 if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
                    if (mode == 1) {
                        painter.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//一半宽
                        painter1.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//一半宽
                    }
                    if (mode == 0) {
                        painter.drawPixmap(j*step, i*step, step , step, pix);//一半宽
                        painter1.drawPixmap(j*step, i*step, step , step, pix);//一半宽
                    }
                 }
                 if(color_model==0){
                     painter1.setPen(this->boxPenColor);
                     painter1.setBrush(this->boxBrushColor);
                     painter.setPen(this->boxPenColor1);
                     painter.setBrush(this->boxBrushColor1);
                      }

                     if (mode == 1) {
                         painter.drawRect(j*(step / 2), i*step, step / 2, step);
                         painter1.drawRect(j*(step / 2), i*step, step / 2, step);
                     }
                     if (mode == 0) {
                         painter.drawRect(j*step , i*step, step , step);
                         painter1.drawRect(j*step, i*step, step , step);
                     }

             }

        }
    }

}

void GameArea::currentItem_to_currentMap()
        //将当前图形加入到游戏区域网格上
{
    copy_Map(copyMap,currentMap,map_row,map_col);//使用备份的网格数组，作为当前数组，这样就避免了显示出图形以前的位置
    int m_row = startY/step;
    int m_col = startX/step;
    for(int i=m_row;i<m_row+4;i++)
    {
        for(int j=m_col;j<m_col+4;j++)
        {
            *(currentMap+i*map_col+j)|=*(currentItem+(i-m_row)*4+(j-m_col));//坐标转换
        }
    }
}

void GameArea::copy_Map(unsigned char *theMap,unsigned char *toMap,int row,int col)
        //游戏区域备份
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            *(toMap+i*col+j)= *(theMap+i*col+j);
        }
    }
}

void GameArea::draw_nextItem()
{
    QPainter painter(this);//显示下一个要出现的图形(left)
	if (mode == 1) 
    painter.drawRect(gameArea_width+20,10,2*step,4*step);
	else
	painter.drawRect(gameArea_width + 20, 10, 4 * step, 4 * step);
    if(this->boxBrushColor==QColor(0,0,0,0))painter.setBrush(green_change);
    else painter.setBrush(this->boxBrushColor);

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            if(*(theNextItem + i*4 +j)==1)
            {
                if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
					if (mode == 1)
                    painter.drawPixmap(gameArea_width+20+ j * (step / 2),10+i*step,step/2,step,pix);
					if (mode == 0)
						painter.drawPixmap(gameArea_width + 20 + j * step, 10 + i * step, step , step, pix);
                 }
				if (mode == 1)
                painter.drawRect(gameArea_width+20+j*(step/2),10+i*step,step/2,step);//提示图形一半宽
				if (mode == 0)
					painter.drawRect(gameArea_width + 20 + j * step , 10 + i * step, step , step);
            }
        }

    QPainter painter1(this);//显示下一个要出现的图形(right)
	if (mode == 1)
    painter1.drawRect(gameArea_width + 20+ QApplication::desktop()->width()/2, 10, 2 * step, 4 * step);
	if (mode == 0)
		painter1.drawRect(gameArea_width + 20 + QApplication::desktop()->width() / 2, 10, 4 * step, 4 * step);
    if(this->boxBrushColor1==QColor(0,0,0,0))painter1.setBrush(green_change);
    else painter1.setBrush(this->boxBrushColor1);

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            if(*(theNextItem + i*4 +j)==1)
            {
                if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
					if (mode == 1)
                    painter1.drawPixmap(gameArea_width+20+ j * (step / 2) +QApplication::desktop()->width()/2,10+i*step,step/2,step,pix);
					if (mode == 0)
						painter1.drawPixmap(gameArea_width + 20 + j * step  + QApplication::desktop()->width() / 2, 10 + i * step, step , step, pix);
                 }
				if (mode == 1)
                painter1.drawRect(gameArea_width+20+ j * (step / 2) +QApplication::desktop()->width()/2,10+i*step,step/2,step);//提示图形一半宽
				if (mode == 0)
					painter1.drawRect(gameArea_width + 20 + j * step  + QApplication::desktop()->width() / 2, 10 + i * step, step , step);//提示图形一半宽
            }
        }

}

void GameArea::paintEvent(QPaintEvent *e)  //重绘事件
{
    QPainter painter(this);
    QPainter painter1(this);
    painter.setRenderHint(QPainter::Antialiasing,true);//这样可以反锯齿
    painter1.setRenderHint(QPainter::Antialiasing,true);
    if(this->isRotate)  //如果旋转游戏区域
    {
        painter.translate(gameArea_X,gameArea_Y);
        painter1.translate(gameArea_X1, gameArea_Y);

        painter.rotate(this->theAngle);
        painter1.rotate(this->theAngle);

        painter.drawPixmap(QPoint(pix_X,pix_Y),*pix_gameArea);
        painter1.drawPixmap(QPoint(pix_X1, pix_Y), *pix_gameArea1);
    }
    else
    {
        painter.drawPixmap(QPoint(pix_X,pix_Y),*pix_gameArea);
        painter1.drawPixmap(QPoint(pix_X1, pix_Y), *pix_gameArea1);
    }
    if(this->isDrawNextItem)  //是否显示下一个图形
    {
        draw_nextItem();
    }
}


void GameArea::keyPressEvent(QKeyEvent *event)  //键盘处理
{
    if(is_stop==true){
    switch(event->key())
    {
    case Qt::Key_Space:
   {
       this->is_stop=!this->is_stop;
   }
    }
    }

    if(is_stop==false)//游戏运行时才响应键盘
    {
    switch(event->key())
    {

         case Qt::Key_Space:
        {
            this->is_stop=!this->is_stop;
            break;
        }

        case Qt::Key_Left :   //向左的按键
        {
            startX=startX - step;
			startX1 = startX1 - step;
			if (isMoveLeft()) { startX = startX + step; startX1 = startX1 + step;
			}
            else
            {
                currentItem_to_currentMap();
                this->draw_gameArea();
                if(isPlaySound_moveLeft)
                {
                    playSound(sound_moveLeft);
                }
            }
            break;
        }
        case Qt::Key_Right :    //向右的按键
        {
            startX=startX + step;
			startX1 = startX1 + step;
			if (isMoveRight()) { startX = startX - step; startX1 = startX1 - step;
			}
            else
            {
                currentItem_to_currentMap();
                this->draw_gameArea();

                if(isPlaySound_moveRight)
                {
                    playSound(sound_moveRight);
                }
            }

            break;
        }
        case Qt::Key_Up :     //向上的按键
        {
            do_itemChange();
            currentItem_to_currentMap();
            this->draw_gameArea();
            if(isPlaySound_itemChange)
            {
                playSound(sound_itemChange);
            }
           break;
        }
        case Qt::Key_Down :    //向下的按键
        {
            if(this->isKey_Down_Move_OneStep)   //默认一次下移一步
            {  
                startY+=step;
                if(this->isMoveEnd())startY-=step; //在这里只做下移一步的操作，不做其他处理
                else
                {
                    currentItem_to_currentMap();
                    this->draw_gameArea();
                    if(isPlaySound_moveDown)
                    {
                        playSound(sound_moveDown);
                    }
                }
            }
            else            //一次下移到底
            {
                int i=0;
                while(!this->isMoveEnd())
                {
                    startY +=step;
                    i++;
                }
                startY -=step;
                if(i>0)
                {
                    currentItem_to_currentMap();
                    this->draw_gameArea();
                    if(isPlaySound_moveDown)
                    {
                        playSound(sound_moveDown);
                    }
                }
            }

            break;
        }
        default: QFrame::keyPressEvent(event);    //接收其他按键
    }
    }

}


bool GameArea::isMoveEnd()
        //判断图形是否移动到了最下面或和别的图形重合了
{
    int item_endRow = myItem->currentItem_endPos(currentItem,'d');

    int itemRow = startY/step;  //图形现在在网格的位置
    int itemCol = startX/step;

/*请注意下面的判断是因为上面的语句中已经让图形走了一步，然后经过这里的判断，而这时的图形的位置还没在窗口上显示。*/
    if(itemRow+item_endRow>=map_row)//如果图形到了网格底部
    {
        ismoveend=1;
        return true;
    }
    for(int i=item_endRow;i>=0;i--) //是否跟已有的图形重合
    {
        for(int j=3;j>=0;j--)
        {
           if(*(copyMap+(itemRow+i)*map_col+itemCol+j) && *(currentItem+i*4+j)==1)
            {

               if(startX==init_startX&&startY<=50) isGameOver = true;
               //如果图形一出来就和别的图形重合了，那么游戏结束
               ismoveend=1;
               return true;
            }
        }
    }
    return false;
}

bool GameArea::isMoveLeft()
        //是否到最左边或和别的图形重合了
{
    int item_endLeft = myItem->currentItem_endPos(currentItem,'l');
    int item_Col = startX/step;
    if(item_Col+item_endLeft<0)
        return true;

     if(isMoveEnd())
    {
        return true;
    }
    return false;
}

bool GameArea::isMoveRight()
        //是否到最右边或和别的图形重合了
{
    int item_endRight = myItem->currentItem_endPos(currentItem,'r');
    int item_Col = startX/step;
    if(item_Col+item_endRight >= map_col)
        return true;
    if(isMoveEnd())
    {
        return true;
    }
    return false;
}

void GameArea::do_itemChange()//对改变图形后超出窗口或和别的图形重合进行处理
{
    unsigned char *tempItem;
    tempItem = currentItem; //先保存现在的图形
    currentItem = myItem->itemChange(currentItem); //进行图形变化
    if(startX<0) startX = 0; //左超界，则让其靠左
    if((startX + 4*step)> gameArea_width) startX = gameArea_width - 4*step;
    //右超界，则让其右边靠右
    if(isMoveEnd())
    //如果和别的图形重合，则不让其改变
    {
        currentItem = tempItem;
    }
}

void GameArea::clearRow() //清除已满的行
{
    int temp1 = 1;
    for(int i=map_row-1;i>0;i--) //从下向上扫描整张网格
    {
        for(int j=0;j<map_col;j++)
        {
            temp1 = *(copyMap+i*map_col+j) && temp1;
        }
        if(temp1) //如果这一行全为1，说明已满，则清除
        {
            if(isPlaySound_clear) playSound(sound_clear);
            fullRowNum++;
            for(int row = i;row>0;row--)   //让已满的行及其上面的各行均等于其上一行
            for(int col = 0;col<map_col;col++)
            {
                *(copyMap+row*map_col+col)=*(copyMap+(row-1)*map_col+col);
            }
            i=i+1; //重新开始扫描整张图
        }
        temp1 =1;
    }
}

void GameArea::playSound(QString fileName) //实现声音的播放
{
    QSound *sound=new QSound(fileName);
    sound->play();
}

void GameArea::moveTimer_upDate() //定时器溢出函数
{
    this->moveOneStep();
    if(this->isMoveEnd())
    {
        if(this->isGameOver)
        {
            this->moveTimer->stop();
            QMessageBox::warning(this,tr("warning"),tr("Game Over!"),QMessageBox::Yes);
            this->init_Game();
            this->gameStart();
            this->moveTimer->start(moveSpeed);
        }
        else
        {
            this->nextItem();
            this->gameStart();
        }
    }
    else
    {
        this->do_MoveNext();
    }
}

