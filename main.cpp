/*************************************************************************
【文件名】main
【功能模块和目的】主函数
【更改记录】
2020-06-20 徐赫临增加了注释
*************************************************************************/
#include "loginwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //对高分辨率屏幕的适配
    #if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    #endif

    QApplication a(argc, argv);
    LoginWindow w;
    w.show();
    return a.exec();
}
