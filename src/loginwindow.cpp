/*************************************************************************
【文件名】loginwindow.cpp
【功能模块和目的】LoginWindow类，登录界面类
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
#include <QImage>

/*************************************************************************
【函数名称】构造函数LoginWindow::LoginWindow(QWidget *parent)
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-26
【更改记录】
*************************************************************************/
LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    m_uTryTimesLeft = 3;
    ui->setupUi(this);
    //刚启动时，默认光标在用户名
    ui->edtName->setFocus();
}

/*************************************************************************
【函数名称】LoginWindow::~LoginWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-05-26
【更改记录】
*************************************************************************/
LoginWindow::~LoginWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】LoginWindow::on_rbtnShowPassword_clicked
【函数功能】切换密码框的显示和隐藏
【参数】bool checked
【返回值】void
【开发者及日期】徐赫临 2020-5-26
【更改记录】null
*************************************************************************/
void LoginWindow::on_rbtnShowPassword_clicked(bool checked)
{
    if(checked){
        ui->edtPassword->setEchoMode(QLineEdit::Normal);
    }
    else {
        ui->edtPassword->setEchoMode(QLineEdit::Password);
    }
}

/*************************************************************************
【函数名称】LoginWindow::on_btnLogin_clicked()
【函数功能】根据登录结果，分无用户等几种情况处理界面
【参数】无
【返回值】void
【开发者及日期】徐赫临 2020-5-26
【更改记录】
2020-5-27 徐赫临优化了界面默认光标的位置/自动清空密码等
*************************************************************************/
void LoginWindow::on_btnLogin_clicked()
{
    QMessageBox msgBox;
    TeacherMainWindow* pTeacherWindow;
    StudentMainWindow* pStudentWindow;
    AdminWindow* pAdminWindow;
    LoginResult res = m_Proc.Login(ui->edtName->text(), ui->edtPassword->text());
    QString str = QString::number(3);
    switch (res) {
    case LR_NOUSER :
        m_uTryTimesLeft--;
        str = QString::number(3 - m_uTryTimesLeft) + " failed log-in.";
        ui->lblDisplay->setText(str);
        msgBox.setText("Wrong username or password.\nNote that you only have 3 tries in all.");
        msgBox.setWindowTitle("Login failure");
        msgBox.exec();
        break;
    case LR_ADMIN :
        this->setWindowOpacity(0.0);
        pAdminWindow = new AdminWindow(this);
        pAdminWindow->exec();
        this->setWindowOpacity(1.0);
        delete pAdminWindow;
        pAdminWindow = nullptr;
        m_uTryTimesLeft = 3;
        break;
    case LR_TEACHER :
        this->setWindowOpacity(0.0);
        pTeacherWindow = new TeacherMainWindow(this);
        pTeacherWindow->setWindowTitle("Teacher " + QString(User::GetLoginedUser()->GetName().c_str()));
        pTeacherWindow->show();
        m_uTryTimesLeft = 3;
        break;
    default:
        this->setWindowOpacity(0.0);
        pStudentWindow = new StudentMainWindow(this);
        pStudentWindow->show();
        m_uTryTimesLeft = 3;
    }
    str = QString::number(3 - m_uTryTimesLeft) + " failed log-in.";
    ui->lblDisplay->setText(str);

    //输入错误之后，清空密码，并让光标出现在密码框
    ui->edtPassword->clear();
    ui->edtPassword->setFocus();
    if(m_uTryTimesLeft == 0){
        this->close();
    }
}

/*************************************************************************
【函数名称】void LoginWindow::on_btnClear_clicked()
【函数功能】清除内容
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void LoginWindow::on_btnClear_clicked()
{
    ui->edtName->clear();
    ui->edtPassword->clear();
    ui->edtPassword->setFocus();
}

/*************************************************************************
【函数名称】void LoginWindow::on_btnForget_clicked()
【函数功能】显示忘记密码对话框
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void LoginWindow::on_btnForget_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Forget Password");
    msgBox.setText("If you forget your password, please contact the administrator @Admin.");
    msgBox.exec();
}

/*************************************************************************
【函数名称】void LoginWindow::on_edtName_returnPressed()
【函数功能】输完用户名之后，跳转到密码
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void LoginWindow::on_edtName_returnPressed()
{
    ui->edtPassword->setFocus();
}

/*************************************************************************
【函数名称】void LoginWindow::on_edtPassword_returnPressed()
【函数功能】输完密码之后，焦点到login按钮，并设置回车为点击按钮。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void LoginWindow::on_edtPassword_returnPressed()
{
    ui->btnLogin->setFocus();
    ui->btnLogin->setDefault(Qt::Key_Enter);
    on_btnLogin_clicked();
}
