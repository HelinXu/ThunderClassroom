/*************************************************************************
【文件名】adminwindow.cpp
【功能模块和目的】AdminWindow类，管理员第一界面类，此界面上提供三种操作的选择，但不实现具体操作
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "adminwindow.h"
#include "ui_adminwindow.h"

/*************************************************************************
【函数名称】构造函数AdminWindow::AdminWindow(QWidget *parent)
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

/*************************************************************************
【函数名称】析构函数AdminWindow::~AdminWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
AdminWindow::~AdminWindow()
{
    delete ui;
}


/*************************************************************************
【函数名称】AdminWindow::on_btnAdd_clicked()
【函数功能】打开添加用户界面
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
void AdminWindow::on_btnAdd_clicked()
{
    this->setWindowOpacity(0.0);
    m_pAddWindow = new AdminAddWindow(this);
    m_pAddWindow->exec();
    this->setWindowOpacity(1.0);
    delete m_pAddWindow;
    m_pAddWindow = nullptr;
}

/*************************************************************************
【函数名称】AdminWindow::on_btnDel_clicked()
【函数功能】打开删除用户界面
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
void AdminWindow::on_btnDel_clicked()
{
    this->setWindowOpacity(0.0);
    m_pDelWindow = new AdminDelWindow(this);
    m_pDelWindow->exec();
    this->setWindowOpacity(1.0);
    delete m_pDelWindow;
    m_pDelWindow = nullptr;
}

/*************************************************************************
【函数名称】AdminWindow::on_btnRes_clicked()
【函数功能】打开重设密码界面
【参数】
【返回值】
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
void AdminWindow::on_btnRes_clicked()
{
    this->setWindowOpacity(0.0);
    m_pResWindow = new AdminResWindow(this);
    m_pResWindow->exec();
    this->setWindowOpacity(1.0);
    delete m_pResWindow;
    m_pResWindow = nullptr;
}
