/*************************************************************************
【文件名】loginwindow.h
【功能模块和目的】LoginWindow类，登录界面类
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "teachermainwindow.h"
#include "studentmainwindow.h"
#include "adminwindow.h"
#include "loginprocess.h"

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

/*************************************************************************
【类名】LoginWindow
【功能】登录界面
【接口说明】槽函数
【开发者及日期】徐赫临 2020-5-26
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit LoginWindow(QWidget *parent = nullptr);

    //析构函数
    ~LoginWindow();

private slots:
    //调整密码的可见性
    void on_rbtnShowPassword_clicked(bool checked);

    //点击登录
    void on_btnLogin_clicked();

    //清除输入框
    void on_btnClear_clicked();

    //忘记密码提示语
    void on_btnForget_clicked();

    //光标跳转到密码框
    void on_edtName_returnPressed();

    //回车用户友好的行为
    void on_edtPassword_returnPressed();

private:
    Ui::LoginWindow *ui;

    //登录过程类对象
    LoginProcess m_Proc;

    //该窗口上剩余的输入次数
    unsigned int m_uTryTimesLeft;
};

#endif // LOGINWINDOW_H
