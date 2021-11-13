/*************************************************************************
【文件名】chatwindow_student
【功能模块和目的】学生聊天页面
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临，参考了网络代码，信息见下
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2018-07-23
# UpdateTime: 2019-12-27
# Info: Qt5气泡式聊天框——QListWidget+QPainter实现
# Url:https://shazhenyu.blog.csdn.net/article/details/81505832
# Github:https://github.com/ShaShiDiZhuanLan/Demo_MessageChat_Qt
#
#-------------------------------------------------*/
#include "chatwindow_student.h"
#include "ui_chatwindow_student.h"
#include <QDateTime>
#include <QDebug>

/*************************************************************************
【函数名称】ChatWindow_Student::ChatWindow_Student(StudentProcess* m_pProc, QWidget *parent)学生界面构造函数
【函数功能】学生界面构造函数
【参数】process的指针
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
ChatWindow_Student::ChatWindow_Student(StudentProcess* m_pProc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChatWindow_Student)
{
    ui->setupUi(this);
    this->m_pProc = m_pProc;
    connect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
}

/*************************************************************************
【函数名称】ChatWindow_Student::~ChatWindow_Student()学生界面析构函数
【函数功能】学生界面析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
ChatWindow_Student::~ChatWindow_Student()
{
    disconnect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    delete ui;

}

/*************************************************************************
【函数名称】ChatWindow_Student::on_btnSendToAll_clicked()发送给全体更新界面
【函数功能】学生界面构造函数
【参数】process的指针
【返回值】
【开发者及日期】徐赫临更改自原帖 2020-06-18
【更改记录】
*************************************************************************/
void ChatWindow_Student::on_btnSendToAll_clicked()
{
    QString msg = ui->textEdit->toPlainText();                               //发送结束则清空聊天输入框
    if (msg == "") {
        return;
    }
    if (m_pProc->Send(msg, 1)) {                                             //1表示发给所有人。
        ui->textEdit->setText("");
    }
    else {
        return;                                                              //如果没有成功发送，则保持原样。
    }
    msg = "I said to all:\n" + msg;                                          //添加发送给全体的提示字符
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    dealMessageTime(time);
    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    messageW->setTextSuccess();
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

/*************************************************************************
【函数名称】收到消息更新界面
【函数功能】收到信息更新界面
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
void ChatWindow_Student::RecvChat(QString msg) {
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    qDebug() << "addMessage" << msg << time << ui->listWidget->count();
    if (msg != "") {
        dealMessageTime(time);
        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);
}

/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2018-07-23
# UpdateTime: 2019-12-27
# Info: Qt5气泡式聊天框——QListWidget+QPainter实现
# Url:https://shazhenyu.blog.csdn.net/article/details/81505832
# Github:https://github.com/ShaShiDiZhuanLan/Demo_MessageChat_Qt
#
#-------------------------------------------------*/
void ChatWindow_Student::dealMessage(QNChatMessage *messageW,
                                     QListWidgetItem *item,
                                     QString text,
                                     QString time,
                                     QNChatMessage::User_Type type)
{
    messageW->setFixedWidth(this->width());
    QSize size = messageW->fontRect(text);
    item->setSizeHint(size);
    messageW->setText(text, time, size, type);
    ui->listWidget->setItemWidget(item, messageW);
}

/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2018-07-23
# UpdateTime: 2019-12-27
# Info: Qt5气泡式聊天框——QListWidget+QPainter实现
# Url:https://shazhenyu.blog.csdn.net/article/details/81505832
# Github:https://github.com/ShaShiDiZhuanLan/Demo_MessageChat_Qt
#
#-------------------------------------------------*/
void ChatWindow_Student::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60);                       // 两个消息相差一分钟
    } else {
        isShowTime = true;
    }
    if(isShowTime) {
        QNChatMessage* messageTime = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->listWidget);
        QSize size = QSize(this->width(), 40);
        messageTime->resize(size);
        itemTime->setSizeHint(size);
        messageTime->setText(curMsgTime, curMsgTime, size, QNChatMessage::User_Time);
        ui->listWidget->setItemWidget(itemTime, messageTime);
    }
}

/*-------------------------------------------------
#
# Project created by QtCreator
# Author: 沙振宇
# CreateTime: 2018-07-23
# UpdateTime: 2019-12-27
# Info: Qt5气泡式聊天框——QListWidget+QPainter实现
# Url:https://shazhenyu.blog.csdn.net/article/details/81505832
# Github:https://github.com/ShaShiDiZhuanLan/Demo_MessageChat_Qt
#
#-------------------------------------------------*/
void ChatWindow_Student::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    ui->listWidget->resize(this->frameSize().width() + 50,
                           this->frameSize().height() - 200);
    ui->widget->resize(this->frameSize().width(), 200);
    ui->widget->move(0, this->frameSize().height() - 200);
    ui->textEdit->resize(this->width() - 20, 125);
    ui->textEdit->move(10, 10);
    ui->btnSendToAll->move(ui->textEdit->width()+ui->textEdit->x()
                           - ui->btnSendToAll->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y()
                           - ui->btnSendToAll->height() - 10);                     //移动发送全体按钮
    ui->btnSendToTeacher->move(ui->textEdit->width()+ui->textEdit->x()
                               - ui->btnSendToTeacher->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y()
                               - ui->btnSendToTeacher->height() - 40);             //移动发给老师按钮
    for(int i = 0; i < ui->listWidget->count(); i++) {
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);
        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

/*************************************************************************
【函数名称】发送给老师
【函数功能】发送给老师
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
void ChatWindow_Student::on_btnSendToTeacher_clicked()
{
    QString msg = ui->textEdit->toPlainText();                               //发送结束则清空聊天输入框
    if (msg == "") {
        return;
    }
    if (m_pProc->Send(msg, 0)) {                                             //1表示发给所有人。0表示发给老师
        ui->textEdit->setText("");
    }
    else {
        return;                                                              //如果没有成功发送，则保持原样。
    }
    QString time = QString::number(QDateTime::currentDateTime().toTime_t()); //时间戳
    dealMessageTime(time);
    QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    dealMessage(messageW, item, msg, time, QNChatMessage::User_Me);
    messageW->setTextSuccess();
    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}
