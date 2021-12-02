/*************************************************************************
【文件名】adminwindow.h
【功能模块和目的】AdminWindow类，管理员第一界面类，此界面上提供三种操作的选择，但不实现具体操作
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QDialog>
#include "adminaddwindow.h"
#include "admindelwindow.h"
#include "adminreswindow.h"

namespace Ui {
class AdminWindow;
}

/*************************************************************************
【类名】AdminWindow
【功能】管理员第一界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AdminWindow(QWidget *parent = nullptr);

    //析构函数
    ~AdminWindow();

private slots:
    //进入增加用户界面
    void on_btnAdd_clicked();

    //进入删除用户界面
    void on_btnDel_clicked();

    //进入重设密码界面
    void on_btnRes_clicked();

private:
    Ui::AdminWindow *ui;

    //增加用户界面指针
    AdminAddWindow* m_pAddWindow;

    //删除用户界面指针
    AdminDelWindow* m_pDelWindow;

    //重设密码界面指针
    AdminResWindow* m_pResWindow;
};

#endif // ADMINWINDOW_H
