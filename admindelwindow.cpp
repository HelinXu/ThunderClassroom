/*************************************************************************
【文件名】admindelwindow.cpp
【功能模块和目的】AdminDelWindow类，管理员删除账户界面类
【开发者及日期】徐赫临 2020-5-27
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "admindelwindow.h"
#include "ui_admindelwindow.h"
#include <QMessageBox>

/*************************************************************************
【函数名称】构造函数
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
AdminDelWindow::AdminDelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminDelWindow)
{
    ui->setupUi(this);
}

/*************************************************************************
【函数名称】析构函数
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
AdminDelWindow::~AdminDelWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】AdminDelWindow::on_btnDelete_clicked()
【函数功能】删除账户
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
void AdminDelWindow::on_btnDelete_clicked()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty()) {
        msgBox.setText("Empty username!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
    else if (ui->edtName->text() == "Admin") {
        msgBox.setText("Cannot delete administrator account!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->clear();
        ui->edtName->setFocus();
        return;
    }
    AdminResult res = Proc.Del(ui->edtName->text());
    if (res == AR_SUCCEED) {
        msgBox.setText("Successfully deleted this account.");
        msgBox.setWindowTitle("Success");
        msgBox.exec();
    }
    else {
        msgBox.setText("This username does not exist.");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
    }
    ui->edtName->clear();
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】AdminDelWindow::on_edtName_returnPressed()
【函数功能】检查是否输入了空用户名
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
void AdminDelWindow::on_edtName_returnPressed()
{
    QMessageBox msgBox;
    if (ui->edtName->text().isEmpty()) {
        msgBox.setText("Empty username!");
        msgBox.setWindowTitle("Error");
        msgBox.exec();
        ui->edtName->setFocus();
        return;
    }
}
