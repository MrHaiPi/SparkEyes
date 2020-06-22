#include "widget.h"
#include "ui_widget.h"
#include<QMessageBox>
#include <QColorDialog>
#include <QFile>
#include <QTextStream>
#include <QSound>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    gamewid=new gamewidget;
    gamewid->setAttribute(Qt::WA_DeleteOnClose); //设置窗口关闭时自动删除
	gamewid->showMaximized();//最大化显示

    this->gameArea=new GameArea(gamewid);
    this->timer=new QTimer(gamewid);
    connect(this->timer,SIGNAL(timeout()),this,SLOT(timer_upDate()));
    this->score=0;
    this->doHightestScore();//显示最高分
    this->gameArea->show();
    this->gameArea->init_Game();//进入游戏初始化
    this->gameArea->gameStart();

    on_comboBox_activated(0);//颜色常规模式初始化
    this->ui->horizontalSlider->setValue(100);//弱视程度初始化
    on_horizontalSlider_actionTriggered(100);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timer_upDate(){//定时器溢出处理
    if(this->gameArea->is_stop)this->ui->pushButton_2->click();

    this->gameArea->moveOneStep();
    if(this->gameArea->isMoveEnd()){

        if(this->gameArea->isGame_Over()){
            this->timer->stop();
            QMessageBox::warning(this,tr("warning"),tr("Game Over!"),QMessageBox::Yes);

            this->doHightestScore();//保存显示最高分

            this->score=0;
            this->gameArea->init_Game();
            this->gameArea->gameStart();
            int num=0;//清空分数
            this->doScore(num);
            gamewid->score_change();
        }
        else{
            this->gameArea->nextItem();
            int num=this->gameArea->getFullRowNum();
            this->doScore(num);
            gamewid->score_change();
            this->gameArea->gameStart();

        }

    }
    else{
        this->gameArea->do_MoveNext();
    }  

}

void Widget::doScore(int num){//显示分数
    score +=num*100*800/(this->speed);
    gamewid->a=score;
}

void Widget::doHightestScore(){//保存显示最高分数
    QFile file("hightest_score.txt");   
    file.open(QIODevice::ReadOnly);
    QByteArray t = file.readAll();
    file.close();
    int hightest_score=t.toInt();
    QString strText;
    strText = tr("%1").arg(hightest_score);
    if (hightest_score<score){
        hightest_score=score;
        strText = tr("%1").arg(score);//显示最高分数
        file.open(QIODevice::WriteOnly);
        file.write(strText.toUtf8());
    }
    ui->label_2->setText(strText.split("", QString::SkipEmptyParts).join("\n"));//竖排显示分数
    ui->label_2->setAlignment(Qt::AlignCenter);
    file.close();
}

void Widget::on_pushButton_clicked()//开始游戏按钮
{
    this->gameArea->is_stop=false;//改变游戏暂停指示变量
    this->timer->start(this->speed);//开启定时器
    this->gameArea->setFocus();//让游戏区获得焦点，才能响应键盘
}

void Widget::on_pushButton_2_clicked()//暂停按钮
{
    if(this->ui->pushButton_2->isChecked()){
        this->timer->stop();
        this->gameArea->is_stop=true;//改变游戏暂停指示变量
        this->ui->pushButton_2->setText(tr("取消暂停"));
    }
    else{
        this->timer->start(this->speed);
        this->gameArea->is_stop=false;
        this->ui->pushButton_2->setText(tr("暂停游戏"));
    }
}

void Widget::on_pushButton_3_clicked()//重新开始
{
   this->gameArea->is_stop=true;
   this->timer->stop();
   if(gamewid->b){
   gamewid=new gamewidget;
   gamewid->setAttribute(Qt::WA_DeleteOnClose);
   gamewid->show();
   this->gameArea=new GameArea(gamewid);
   this->timer=new QTimer(gamewid);
   connect(this->timer,SIGNAL(timeout()),this,SLOT(timer_upDate()));
   }

   this->score=0;
   this->gameArea->show();
   this->gameArea->init_Game();//进入游戏初始化
   this->gameArea->gameStart();
   int num=0;//清空分数
   this->doScore(num);
   gamewid->score_change();

   on_comboBox_activated(0);//颜色常规模式初始化
}

void Widget::on_pushButton_4_clicked()//设置背景颜色
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Color dialog");

    if(this->leftright==0)this->gameArea->setGameAreaColor(color);
    else if (this->leftright==1)this->gameArea->setGameAreaColor1(color);

    this->gameArea->draw_gameArea();
    this->gameArea->setFocus();
}

void Widget::on_pushButton_5_clicked()//设置方块颜色
{
    QColor color = QColorDialog::getColor(Qt::green, this, "Color dialog");

    if(this->leftright==0)
    {
        this->gameArea->setBoxBrushColor(color);
        gamewid->boxBrushColor=color;
    }
    else if (this->leftright==1)
    {
        this->gameArea->setBoxBrushColor1(color);
        gamewid->boxBrushColor1=color;
    }

    this->gameArea->draw_gameArea();
    this->gameArea->setFocus();
    gamewid->score_change();
}

void Widget::on_pushButton_6_clicked()//设置方块边框颜色
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Color dialog");
    if(this->leftright==0)this->gameArea->setBoxPenColor(color);
    else if (this->leftright==1)this->gameArea->setBoxPenColor1(color);
    this->gameArea->draw_gameArea();
    this->gameArea->setFocus();
}

void Widget::on_pushButton_7_clicked()//锁定颜色设置按钮
{
    if(this->ui->pushButton_7->isChecked())
    {
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->comboBox->setEnabled(false);
        ui->comboBox_2->setEnabled(false);
        ui->comboBox_3->setEnabled(false);
        ui->horizontalSlider->setEnabled(false);
        this->ui->pushButton_7->setText(tr("取消锁定"));
    }
    else{
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->comboBox->setEnabled(true);
        ui->comboBox_2->setEnabled(true);
        ui->comboBox_3->setEnabled(true);
        ui->horizontalSlider->setEnabled(true);
        this->ui->pushButton_7->setText(tr("锁定按钮"));
    }
}

void Widget::on_pushButton_8_clicked()//方块提示按钮
{
    if(this->ui->pushButton_8->isChecked())
      {
          this->gameArea->setDrawNextItem(false);
      }
      else
      {
          this->gameArea->setDrawNextItem(true);
      }
  this->gameArea->draw_gameArea();
  this->gameArea->setFocus();
}

QSound *sound=new QSound("./voice/background.wav");
void Widget::on_pushButton_9_clicked()//声音开关按钮
{
    if(this->ui->pushButton_9->isChecked())
       {
           this->gameArea->setPlaySound_itemChange("./voice/changeItem.wav",true);
           this->gameArea->setPlaySound_moveDown("./voice/moveDown.wav",true);
           this->gameArea->setPlaySound_moveLeft("./voice/moveLeft.wav",true);
           this->gameArea->setPlaySound_moveRight("./voice/moveLeft.wav",true);
           this->gameArea->setPlaySound_clear("./voice/clear.wav",true);
           sound->play();
           sound->setLoops(1000);
           this->ui->pushButton_9->setText(tr("关闭声音"));
       }
       else
       {
           sound->stop();
           this->gameArea->setPlaySound(false); //关闭音乐
           this->ui->pushButton_9->setText(tr("打开声音"));
       }
}

void Widget::on_pushButton_10_clicked()//是否坠落按钮
{
    if(this->ui->pushButton_10->isChecked())
       {
           this->gameArea->setKey_Down_Move_oneStep(true);         //按一下向下方向键，下移一步
       }
       else
       {
           this->gameArea->setKey_Down_Move_oneStep(false);         //按一下向下方向键，移动到底
       }
       this->gameArea->setFocus();
}

void Widget::on_comboBox_activated(int index)//选定弱视眼
{
    if(ui->comboBox->currentIndex()==0) {this->leftright=0;this->gameArea->left_right=0;}//选定左眼，调节左区域
        else if(ui->comboBox->currentIndex()==1){this->leftright=1;this->gameArea->left_right=1;}//选定右眼，调节右区域

     QColor color =QColor(0,0,0,0);
    if(ui->comboBox_2->currentIndex()==0&&ui->comboBox->currentIndex()==1){
        this->gameArea->setBoxBrushColor(color);
        this->gameArea->setBoxPenColor(color);
        this->gameArea->setBoxBrushColor1(this->gameArea->green_change);
        this->gameArea->setBoxPenColor1(Qt::black);
    }
    if(ui->comboBox_2->currentIndex()==0&&ui->comboBox->currentIndex()==0){
        this->gameArea->setBoxBrushColor1(color);
        this->gameArea->setBoxPenColor1(color);
        this->gameArea->setBoxBrushColor(this->gameArea->green_change);
        this->gameArea->setBoxPenColor(Qt::black);
    }

    if(ui->comboBox_2->currentIndex()==0){
    this->gameArea->setGameAreaColor(Qt::black);
    this->gameArea->setGameAreaColor1(Qt::black);
    }

    this->gameArea->draw_gameArea();
    this->gameArea->setFocus();
}

void Widget::on_comboBox_2_activated(int index)//选定颜色模式
{
    if(ui->comboBox_2->currentIndex()==0){
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->horizontalSlider->setEnabled(true);
        this->gameArea->color_model=0;//更新颜色模式
        on_comboBox_activated(0);
        gamewid->boxBrushColor=this->gameArea->green_change;
        gamewid->boxBrushColor1=this->gameArea->green_change;
        gamewid->score_change();
    }

    if(ui->comboBox_2->currentIndex()==1){
        ui->pushButton_4->setEnabled(true);
        ui->pushButton_5->setEnabled(true);
        ui->pushButton_6->setEnabled(true);
        ui->horizontalSlider->setEnabled(false);
        this->gameArea->color_model=1;//更新颜色模式

        this->gameArea->setBoxBrushColor(this->gameArea->green_change);
        this->gameArea->setBoxBrushColor1(this->gameArea->green_change);
        this->gameArea->setBoxPenColor(Qt::black);
        this->gameArea->setBoxPenColor1(Qt::black);
        this->gameArea->draw_gameArea();
        this->gameArea->setFocus();

    }
}
void Widget::on_comboBox_3_activated(int index)//游戏模式选择
{
	if (ui->comboBox_3->currentIndex() == 0)//左右分视
	{
		this->gameArea->mode = 0;
        this->gamewid->mode = 0;
	    this->gameArea->init_gameArea(110, 20, QApplication::desktop()->width(), QApplication::desktop()->height(), QApplication::desktop()->width() / 3 - 8 - QApplication::desktop()->width() / 3 / 7, QApplication::desktop()->height() - 134, QApplication::desktop()->width() / 3 / 14, 220, 0);

	}
	if (ui->comboBox_3->currentIndex() == 1)//偏正光
	{
		this->gameArea->mode = 1;
        this->gamewid->mode = 1;
		this->gameArea->init_gameArea(240, 20, QApplication::desktop()->width(), QApplication::desktop()->height(), (QApplication::desktop()->width() / 3 - 8 - QApplication::desktop()->width() / 3 / 7) / 2, QApplication::desktop()->height() - 134, QApplication::desktop()->width() / 3 / 14, 220, 0);
	}
    on_pushButton_3_clicked();
}

void Widget::on_comboBox_4_activated(int index)//游戏难度选择
{
    if(ui->comboBox_4->currentIndex()==0)this->speed=800;//简单
    if(ui->comboBox_4->currentIndex()==1)this->speed=500;//普通
    if(ui->comboBox_4->currentIndex()==2)this->speed=300;//困难
    if(ui->comboBox_4->currentIndex()==3)this->speed=100;//地狱
    on_pushButton_clicked();
    this->timer->stop();
}

void Widget::on_horizontalSlider_actionTriggered(int action)//弱视程度
{   QString str;
    this->ui->horizontalSlider->setMaximum(100);
    str = tr("%1").arg(this->ui->horizontalSlider->value());
    this->ui->label_6->setText(str.append("%"));

    this->gameArea->transparency=255/100*this->ui->horizontalSlider->value()+50;
    this->gameArea->green_change=QColor(0,255,0,this->gameArea->transparency);

    on_comboBox_activated(ui->comboBox->currentIndex());
    this->gameArea->draw_gameArea();
}
