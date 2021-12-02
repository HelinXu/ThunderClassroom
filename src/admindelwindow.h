/*************************************************************************
【文件名】admindelwindow.h
【功能模块和目的】AdminDelWindow类，管理员删除账户界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMINDELWINDOW_H
#define ADMINDELWINDOW_H

#include <QDialog>
#include "adminprocess.h"

namespace Ui {
class AdminDelWindow;
}

/*************************************************************************
【类名】AdminDelWindow
【功能】管理员删除账户界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class AdminDelWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AdminDelWindow(QWidget *parent = nullptr);

    //析构函数
    ~AdminDelWindow();

private slots:
    //删除用户
    void on_btnDelete_clicked();

    //回车检查是否已经输入。
    void on_edtName_returnPressed();

private:
    Ui::AdminDelWindow *ui;

    //包含管理员过程对象
    AdminProcess Proc;
};

#endif // ADMINDELWINDOW_H
