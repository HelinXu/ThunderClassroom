/*************************************************************************
【文件名】adminaddwindow.cpp
【功能模块和目的】AdminAddWindow类，管理员增加账户界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "adminaddwindow.h"
#include "ui_adminaddwindow.h"
#include <QMessageBox>

/*************************************************************************
【函数名称】构造函数
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
AdminAddWindow::AdminAddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminAddWindow)
{
    ui->setupUi(this);
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】析构函数
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
AdminAddWindow::~AdminAddWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】AdminAddWindow::on_btnCreateStu_clicked()
【函数功能】增加一个学生账号
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminAddWindow::on_btnCreateStu_clicked()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty() || ui->edtPassword->text().isEmpty()) {
        msgBox.setText("Empty username / password!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    AdminResult res = Proc.Add(ui->edtName->text(), ui->edtPassword->text(), QString::fromStdString("Student"));
    if (res == AR_SUCCEED) {
        msgBox.setText("Successfully created a student account.");
        msgBox.setWindowTitle("Success");
        msgBox.exec();
    }
    else if (res == AR_ALREADYEXIST){
        msgBox.setText("This username already exists.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    ui->edtName->clear();
    ui->edtPassword->clear();
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】AdminAddWindow::on_rbtnShowPassword_clicked(bool checked)
【函数功能】密码的显示与隐藏
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminAddWindow::on_rbtnShowPassword_clicked(bool checked)
{
    if(checked){
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
    }
    else {
        ui->edtPassword->setEchoMode(QLineEdit::Password);
    }
}

/*************************************************************************
【函数名称】AdminAddWindow::on_btnCreateTea_clicked()
【函数功能】创建教师账户
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminAddWindow::on_btnCreateTea_clicked()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty() || ui->edtPassword->text().isEmpty()) {
        msgBox.setText("Empty username / password!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    AdminResult res = Proc.Add(ui->edtName->text(), ui->edtPassword->text(), QString::fromStdString("Teacher"));
    if (res == AR_SUCCEED) {
        msgBox.setText("Successfully created a teacher account.");
        msgBox.setWindowTitle("Success");
        msgBox.exec();
    }
    else if (res == AR_ALREADYEXIST){
        msgBox.setText("This username already exists.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    ui->edtName->clear();
    ui->edtPassword->clear();
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】AdminAddWindow::on_edtName_returnPressed()
【函数功能】输入姓名后跳转到密码
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminAddWindow::on_edtName_returnPressed()
{
    ui->edtPassword->setFocus();
}

/*************************************************************************
【函数名称】AdminAddWindow::on_edtPassword_returnPressed()
【函数功能】更改密码
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-27
【更改记录】
*************************************************************************/
void AdminAddWindow::on_edtPassword_returnPressed()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty() || ui->edtPassword->text().isEmpty()) {
        msgBox.setText("Empty username / password!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    ui->btnCreateStu->setFocus();
}
