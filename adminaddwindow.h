/*************************************************************************
【文件名】adminaddwindow.h
【功能模块和目的】AdminAddWindow类，管理员增加账户界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMINADDWINDOW_H
#define ADMINADDWINDOW_H

#include <QDialog>
#include "adminprocess.h"

namespace Ui {
class AdminAddWindow;
}

/*************************************************************************
【类名】AdminAddWindow
【功能】管理员界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class AdminAddWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AdminAddWindow(QWidget *parent = nullptr);

    //析构函数
    ~AdminAddWindow();

private slots:
    //创建学生账号
    void on_btnCreateStu_clicked();

    //调整密码的可见性
    void on_rbtnShowPassword_clicked(bool checked);

    //创建教师账号
    void on_btnCreateTea_clicked();

    //光标跳转
    void on_edtName_returnPressed();

    //密码框回车检查是否有输入用户名密码
    void on_edtPassword_returnPressed();

private:
    Ui::AdminAddWindow *ui;

    //包含管理员过程对象
    AdminProcess Proc;
};

#endif // ADMINADDWINDOW_H
