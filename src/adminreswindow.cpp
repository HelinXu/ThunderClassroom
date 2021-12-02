/*************************************************************************
【文件名】adminreswindow.c
【功能模块和目的】AdminResWindow类，管理员更改账户密码界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "adminreswindow.h"
#include "ui_adminreswindow.h"
#include <QMessageBox>

/*************************************************************************
【函数名称】构造函数
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
AdminResWindow::AdminResWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminResWindow)
{
    ui->setupUi(this);
}

/*************************************************************************
【函数名称】析构函数
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
AdminResWindow::~AdminResWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】AdminResWindow::on_btnReset_clicked()
【函数功能】更改给定用户的密码
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminResWindow::on_btnReset_clicked()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty() || ui->edtPassword->text().isEmpty()) {
        msgBox.setText("Empty username / password!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    else if (ui->edtName->text() == "Admin") {
        msgBox.setText("Cannot reset administrator account!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->clear();
        ui->edtPassword->clear();
        ui->edtName->setFocus();
        return;
    }
    AdminResult res = m_Proc.Res(ui->edtName->text(), ui->edtPassword->text());
    if (res == AR_SUCCEED) {
        msgBox.setText("Successfully reset the password.");
        msgBox.setWindowTitle("Success");
        msgBox.exec();
    }
    else {
        msgBox.setText("This username does not exist.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    ui->edtName->clear();
    ui->edtPassword->clear();
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】AdminResWindow::on_edtName_returnPressed()
【函数功能】回车转到密码框
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminResWindow::on_edtName_returnPressed()
{
    ui->edtPassword->setFocus();
}

/*************************************************************************
【函数名称】AdminResWindow::on_edtPassword_returnPressed()
【函数功能】功能与点击按钮一致
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】此处可以继续优化为与点击按钮公用代码
*************************************************************************/
void AdminResWindow::on_edtPassword_returnPressed()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty() || ui->edtPassword->text().isEmpty()) {
        msgBox.setText("Empty username / password!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    else if (ui->edtName->text() == "Admin") {
        msgBox.setText("Cannot reset administrator account!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->clear();
        ui->edtPassword->clear();
        ui->edtName->setFocus();
        return;
    }
    AdminResult res = m_Proc.Res(ui->edtName->text(), ui->edtPassword->text());
    if (res == AR_SUCCEED) {
        msgBox.setText("Successfully reset the password.");
        msgBox.setWindowTitle("Success");
        msgBox.exec();
    }
    else {
        msgBox.setText("This username does not exist.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    ui->edtName->clear();
    ui->edtPassword->clear();
    ui->edtName->setFocus();
}
