/**********************��Ȩ����****************************

����Դ������www.yafeilinux.comԭ����������ѭQt��Դ���������������Э�顣

����Ȩʹ�ã������͸������ǵĴ��룬���뱣֤����Ŀ�Դ��

����Դ�����Ȩ��www.yafeilinux.com���У��벻Ҫ������ҵ��;��


**********************************************************/

//�������ʵ������Ϸ�����й���
#include "gamearea.h"
#include <QKeyEvent>
#include <QMessageBox>
#include <QSound>
#include <QDesktopWidget>
#include <QApplication>
/****************************�����ǹ��캯������������*********************************************************/


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
/****************************��������Ҫ���ܺ���*********************************************************/

//��������һ��
void GameArea::moveOneStep()
{
     startY += step;
}

//��ʾ����һ����Ľ���
void GameArea::do_MoveNext()
{
    this->currentItem_to_currentMap();
    this->draw_gameArea();
}

//�Ƚ����ڵ���Ϸ���򱸷�������
void GameArea::nextItem()
{
    copy_Map(currentMap,copyMap,map_row,map_col);
    this->clearRow();
}

//��Ϸ�Ƿ��Ѿ�����
bool GameArea::isGame_Over()
{
    if(this->isGameOver) return true;
    else return false;
}

//��ȡ����������
int GameArea::getFullRowNum()
{
    return fullRowNum;
}

//���÷�����ɫ����ͼ(left)
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

//���÷�����ɫ����ͼ(right)
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

//���÷�����ɫ����ͼ
void GameArea::set_draw_box_picture(bool Bool)
{
    this->is_draw_box_picture = Bool;
}

void GameArea::setBoxPicture(QString fileName)
{
    this->boxPicture = fileName;
}


//�Ƿ�����һ��,���������һ�����Ƶ���
void GameArea::setKey_Down_Move_oneStep(bool Bool)
{
    this->isKey_Down_Move_OneStep = Bool;
}



//�Ƿ���ʾ����
void GameArea::setDrawGrid(bool Bool)
{
    isDrawGrid = Bool;
}

//�Ƿ���ʾ��һ��Ҫ���ֵ�ͼ��
void GameArea::setDrawNextItem(bool Bool)
{
    isDrawNextItem = Bool;
}

//�Լ�����Ϸ����ӷ���
void GameArea::setbox(int row,int col)
{
    *(copyMap+row*map_col+col) = 1;
}


//�Ƿ񲥷�����
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
//�Ƿ񲥷�����



/***������Ϸ������ת****/

void GameArea::setRotate(bool Bool) //������ת
{
    this->isRotate = Bool;
}

void GameArea::setRotateAngle(int angle) //˳ʱ����ת�Ƕ�
{
    this->theAngle = angle;
}

void GameArea::setGameAreaPixOrigin(int x,int y) //�µ�����ԭ��
{
    this->gameArea_X = x;
    this->gameArea_X1 = x;
    this->gameArea_Y = y;
}

void GameArea::setGameAreaPix(int x,int y) //��Ϸ�����λ��
{
    this->pix_X = x;
    this->pix_X1 = x;
    this->pix_Y = y;
}

/*****������ת******/


/****************************��������Ҫ���ܺ���*********************************************************/



/****************************�����Ǻ��Ĺ��ܺ���*********************************************************/


void GameArea::init_gameArea(int X,int Y,int frame_width,int frame_height,int width,int height,int boxStep,int start_x,int start_y)
        //��ʼ����Ϸ����,��ʼλ�ã����ߣ�С����߳�,ͼ�γ���λ��
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
    //����Ϸ��������Ϊ�ϴ��������
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

    //Ĭ��״̬����
    this->isDrawGrid = true;
    this->isDrawNextItem=true;
    this->isPlaySound_moveLeft = false;
    this->isPlaySound_moveRight = false;
    this->isPlaySound_moveDown = false;
    this->isPlaySound_itemChange =false;
    this->is_draw_box_picture = false;

    //Ĭ����ɫ����(left_area)
    this->gameAreaColor = Qt::black;
    this->boxBrushColor = Qt::green;
    this->boxPenColor = Qt::black;
    //Ĭ����ɫ����(right_area)
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

void GameArea::init_Game() //��һ�ν�����Ϸʱ��һЩ�������г�ʼ��
{
    this->init_Map(currentMap,map_row,map_col);
    this->init_Map(copyMap,map_row,map_col);

    this->currentItem = this->currentMap;   //������ָ����г�ʼ��
    this->theNextItem = this->currentMap;   //������ָ���ָ����յ�����

    isFirstItem = true;
    isGameOver = false;
    fullRowNum = 0;

    this->draw_gameArea();
}

void GameArea::gameStart() //��Ϸ��ʼ���У�����ÿ�γ����µķ��鶼����һ���������
{
    ismoveend=0;

    this->startX = this->init_startX;
	this->startX1 = this->init_startX1;
    this->startY = this->init_startY;
    fullRowNum = 0; //ÿ�γ���һ���µ�ͼ�ζ����ϴ�����������0
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
        //������һ�������е���ȫ��Ϊ0
{
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            *(initMap+i*col+j)= 0;
        }
    }
}

void GameArea::draw_gameArea()  //������Ϸ���򣬰����������Ϸ���ķ���
{
    this->pix_gameArea->fill(gameAreaColor);
    this->pix_gameArea1->fill(gameAreaColor1);

    if(this->isDrawGrid)//������
    {
        draw_Grid();
    }
    draw_currentMap();
    update();
}

void GameArea::draw_Grid()   //������Ϸ���򱳾�������
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
			painter.drawLine(QPoint(j*(step / 2), 0), QPoint(j*(step / 2), this->gameArea_height));//һ���
			painter1.drawLine(QPoint(j*(step / 2), 0), QPoint(j*(step / 2), this->gameArea_height));//һ���
		}
		if (mode == 0) {
			painter.drawLine(QPoint(j*step , 0), QPoint(j*step , this->gameArea_height));
			painter1.drawLine(QPoint(j*step, 0), QPoint(j*step , this->gameArea_height));
		}
    }
}

void GameArea::draw_currentMap()
        //������Ϸ�����������еķ���
{
    QPainter painter(this->pix_gameArea);
    painter.setPen(this->boxPenColor);
    painter.setBrush(this->boxBrushColor);

    QPainter painter1(this->pix_gameArea1);
    painter1.setPen(this->boxPenColor1);
    painter1.setBrush(this->boxBrushColor1);

    for(int i=0;i<map_row;i++)    //�������ϵ�ͼ����ʾ��������
    {
        for(int j=0;j<map_col;j++)
       {

             if(*(currentMap+i*map_col+j)-*(copyMap+i*map_col+j)==1)//�������з���
             {
                 if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
                    if (mode == 1) {
                        painter.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//һ���
                        painter1.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//һ���
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
                     painter.drawRect(j*(step / 2), i*step, step / 2, step);//һ���
                     painter1.drawRect(j*(step / 2), i*step, step / 2, step);//һ���
                 }
                 if (mode == 0) {
                     painter.drawRect(j*step, i*step, step, step);
                     painter1.drawRect(j*step, i*step, step , step);
                 }

             }

             if(*(copyMap+i*map_col+j)==1)//�����Ѿ����µķ���
             {
                 if(this->is_draw_box_picture)
                 {
                    QPixmap pix;
                    pix.load(this->boxPicture);
                    if (mode == 1) {
                        painter.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//һ���
                        painter1.drawPixmap(j*(step / 2), i*step, step / 2, step, pix);//һ���
                    }
                    if (mode == 0) {
                        painter.drawPixmap(j*step, i*step, step , step, pix);//һ���
                        painter1.drawPixmap(j*step, i*step, step , step, pix);//һ���
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
        //����ǰͼ�μ��뵽��Ϸ����������
{
    copy_Map(copyMap,currentMap,map_row,map_col);//ʹ�ñ��ݵ��������飬��Ϊ��ǰ���飬�����ͱ�������ʾ��ͼ����ǰ��λ��
    int m_row = startY/step;
    int m_col = startX/step;
    for(int i=m_row;i<m_row+4;i++)
    {
        for(int j=m_col;j<m_col+4;j++)
        {
            *(currentMap+i*map_col+j)|=*(currentItem+(i-m_row)*4+(j-m_col));//����ת��
        }
    }
}

void GameArea::copy_Map(unsigned char *theMap,unsigned char *toMap,int row,int col)
        //��Ϸ���򱸷�
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
    QPainter painter(this);//��ʾ��һ��Ҫ���ֵ�ͼ��(left)
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
                painter.drawRect(gameArea_width+20+j*(step/2),10+i*step,step/2,step);//��ʾͼ��һ���
				if (mode == 0)
					painter.drawRect(gameArea_width + 20 + j * step , 10 + i * step, step , step);
            }
        }

    QPainter painter1(this);//��ʾ��һ��Ҫ���ֵ�ͼ��(right)
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
                painter1.drawRect(gameArea_width+20+ j * (step / 2) +QApplication::desktop()->width()/2,10+i*step,step/2,step);//��ʾͼ��һ���
				if (mode == 0)
					painter1.drawRect(gameArea_width + 20 + j * step  + QApplication::desktop()->width() / 2, 10 + i * step, step , step);//��ʾͼ��һ���
            }
        }

}

void GameArea::paintEvent(QPaintEvent *e)  //�ػ��¼�
{
    QPainter painter(this);
    QPainter painter1(this);
    painter.setRenderHint(QPainter::Antialiasing,true);//�������Է����
    painter1.setRenderHint(QPainter::Antialiasing,true);
    if(this->isRotate)  //�����ת��Ϸ����
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
    if(this->isDrawNextItem)  //�Ƿ���ʾ��һ��ͼ��
    {
        draw_nextItem();
    }
}


void GameArea::keyPressEvent(QKeyEvent *event)  //���̴���
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

    if(is_stop==false)//��Ϸ����ʱ����Ӧ����
    {
    switch(event->key())
    {

         case Qt::Key_Space:
        {
            this->is_stop=!this->is_stop;
            break;
        }

        case Qt::Key_Left :   //����İ���
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
        case Qt::Key_Right :    //���ҵİ���
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
        case Qt::Key_Up :     //���ϵİ���
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
        case Qt::Key_Down :    //���µİ���
        {
            if(this->isKey_Down_Move_OneStep)   //Ĭ��һ������һ��
            {  
                startY+=step;
                if(this->isMoveEnd())startY-=step; //������ֻ������һ���Ĳ�����������������
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
            else            //һ�����Ƶ���
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
        default: QFrame::keyPressEvent(event);    //������������
    }
    }

}


bool GameArea::isMoveEnd()
        //�ж�ͼ���Ƿ��ƶ������������ͱ��ͼ���غ���
{
    int item_endRow = myItem->currentItem_endPos(currentItem,'d');

    int itemRow = startY/step;  //ͼ�������������λ��
    int itemCol = startX/step;

/*��ע��������ж�����Ϊ�����������Ѿ���ͼ������һ����Ȼ�󾭹�������жϣ�����ʱ��ͼ�ε�λ�û�û�ڴ�������ʾ��*/
    if(itemRow+item_endRow>=map_row)//���ͼ�ε�������ײ�
    {
        ismoveend=1;
        return true;
    }
    for(int i=item_endRow;i>=0;i--) //�Ƿ�����е�ͼ���غ�
    {
        for(int j=3;j>=0;j--)
        {
           if(*(copyMap+(itemRow+i)*map_col+itemCol+j) && *(currentItem+i*4+j)==1)
            {

               if(startX==init_startX&&startY<=50) isGameOver = true;
               //���ͼ��һ�����ͺͱ��ͼ���غ��ˣ���ô��Ϸ����
               ismoveend=1;
               return true;
            }
        }
    }
    return false;
}

bool GameArea::isMoveLeft()
        //�Ƿ�����߻�ͱ��ͼ���غ���
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
        //�Ƿ����ұ߻�ͱ��ͼ���غ���
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

void GameArea::do_itemChange()//�Ըı�ͼ�κ󳬳����ڻ�ͱ��ͼ���غϽ��д���
{
    unsigned char *tempItem;
    tempItem = currentItem; //�ȱ������ڵ�ͼ��
    currentItem = myItem->itemChange(currentItem); //����ͼ�α仯
    if(startX<0) startX = 0; //�󳬽磬�����俿��
    if((startX + 4*step)> gameArea_width) startX = gameArea_width - 4*step;
    //�ҳ��磬�������ұ߿���
    if(isMoveEnd())
    //����ͱ��ͼ���غϣ�������ı�
    {
        currentItem = tempItem;
    }
}

void GameArea::clearRow() //�����������
{
    int temp1 = 1;
    for(int i=map_row-1;i>0;i--) //��������ɨ����������
    {
        for(int j=0;j<map_col;j++)
        {
            temp1 = *(copyMap+i*map_col+j) && temp1;
        }
        if(temp1) //�����һ��ȫΪ1��˵�������������
        {
            if(isPlaySound_clear) playSound(sound_clear);
            fullRowNum++;
            for(int row = i;row>0;row--)   //���������м�������ĸ��о���������һ��
            for(int col = 0;col<map_col;col++)
            {
                *(copyMap+row*map_col+col)=*(copyMap+(row-1)*map_col+col);
            }
            i=i+1; //���¿�ʼɨ������ͼ
        }
        temp1 =1;
    }
}

void GameArea::playSound(QString fileName) //ʵ�������Ĳ���
{
    QSound *sound=new QSound(fileName);
    sound->play();
}

void GameArea::moveTimer_upDate() //��ʱ���������
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

