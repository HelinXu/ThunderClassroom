/*************************************************************************
【文件名】adminreswindow.h
【功能模块和目的】AdminResWindow类，管理员更改账户密码界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMINRESWINDOW_H
#define ADMINRESWINDOW_H

#include <QDialog>
#include "adminprocess.h"

namespace Ui {
class AdminResWindow;
}

/*************************************************************************
【类名】AdminResWindow
【功能】管理员重设密码界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class AdminResWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AdminResWindow(QWidget *parent = nullptr);

    //析构函数
    ~AdminResWindow();

private slots:
    //按钮重设密码
    void on_btnReset_clicked();

    //用户名回车，光标跳转密码框
    void on_edtName_returnPressed();

    //密码框回车，相当于点击重设密码
    void on_edtPassword_returnPressed();

private:
    Ui::AdminResWindow *ui;

    //管理员过程类对象
    AdminProcess m_Proc;
};

#endif // ADMINRESWINDOW_H
