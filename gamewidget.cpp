#include "gamewidget.h"
#include "ui_gamewidget.h"
#include<QMessageBox>
#include <QColorDialog>
#include <QColor>
#include <QApplication>

gamewidget::gamewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewidget)
{
    ui->setupUi(this);
    b=0;//窗口销毁指示变量
    a=0;//分数
    score_change();
}

gamewidget::~gamewidget()
{
    delete ui;
    b=1;
}

void gamewidget::score_change()//显示子窗口的分数
{
    QString strText = tr("%1").arg(a);

    QFont font1("Snap ITC");
    font1.setStretch(30);
    font1.setPixelSize(50);

    QFont font("Snap ITC");
    font.setPixelSize(80);


    if(mode==0){
        ui->label_2->setGeometry(QApplication::desktop()->width()/2-250,QApplication::desktop()->height()/2-300,101,751);
        ui->label_2->setFont(font);
    }
    if(mode==1)
    {
        ui->label_2->setGeometry(QApplication::desktop()->width()/2-440,QApplication::desktop()->height()/2-300,101,751);
        ui->label_2->setFont(font1);
    }
    ui->label_2->setText(strText.split("", QString::SkipEmptyParts).join("\n"));//竖排显示分数
    ui->label_2->setAlignment(Qt::AlignCenter);
    QPalette pe;
    pe.setColor(QPalette::WindowText,boxBrushColor);
    ui->label_2->setPalette(pe);


    if(mode==0){
        ui->label_3->setGeometry(QApplication::desktop()->width()-250,QApplication::desktop()->height()/2-300,101,751);
        ui->label_3->setFont(font);
    }
    if(mode==1){
        ui->label_3->setGeometry(QApplication::desktop()->width()-440,QApplication::desktop()->height()/2-300,101,751);
        ui->label_3->setFont(font1);
    }
    ui->label_3->setText(strText.split("", QString::SkipEmptyParts).join("\n"));
    ui->label_3->setAlignment(Qt::AlignCenter);
    pe.setColor(QPalette::WindowText,boxBrushColor1);
    ui->label_3->setPalette(pe);
}
