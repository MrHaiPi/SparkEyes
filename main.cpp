#include "widget.h"
#include <QApplication>
#include <QTextCodec>
#include <QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString strPath=QApplication::applicationDirPath();
    strPath +="/img/sparkeye.png";
    a.setWindowIcon(QIcon(strPath));

    Widget w;
	w.show();

    return a.exec();
}
