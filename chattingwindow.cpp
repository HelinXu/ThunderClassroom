/*************************************************************************
【文件名】chattingwindow
【功能模块和目的】教师聊天页面
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
#include "chattingwindow.h"
#include "ui_chattingwindow.h"
#include <QDateTime>
#include <QDebug>

/*************************************************************************
【函数名称】ChattingWindow::ChattingWindow(TeacherProcess* pTeacherProc, QWidget *parent)教师聊天窗口构造函数
【函数功能】构造函数
【参数】传入process指针（收到聊天的信号）。
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
ChattingWindow::ChattingWindow(TeacherProcess* pTeacherProc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ChattingWindow)
{
    ui->setupUi(this);
    m_pTeacherProc = pTeacherProc;
    connect(m_pTeacherProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
}

/*************************************************************************
【函数名称】ChattingWindow::~ChattingWindow()析构函数
【函数功能】析构函数
【参数】不能把process指针delete！
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】
*************************************************************************/
ChattingWindow::~ChattingWindow()
{
    disconnect(m_pTeacherProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    delete ui;
}

/*************************************************************************
【函数名称】ChattingWindow::RecvChat(QString msg)收到信息槽函数
【函数功能】根据收到的信息更新界面
【参数】收到的信息msg
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18 更改了接收消息的逻辑
*************************************************************************/
void ChattingWindow::RecvChat(QString msg) {
    QString time = QString::number(
                QDateTime::currentDateTime().toTime_t());                  //时间戳
    qDebug()<<"addMessage" << msg << time << ui->listWidget->count();
    if(msg != "") {                                                        //将当前对话插入气泡列表
        dealMessageTime(time);
        QNChatMessage* messageW = new QNChatMessage(ui->listWidget->parentWidget());
        QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
        dealMessage(messageW, item, msg, time, QNChatMessage::User_She);
    }
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);             //将当前对话框移到界面最下端
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
void ChattingWindow::dealMessage(QNChatMessage *messageW,
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
void ChattingWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;
    if(ui->listWidget->count() > 0) {
        QListWidgetItem* lastItem = ui->listWidget->item(ui->listWidget->count() - 1);
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(lastItem);
        int lastTime = messageW->time().toInt();
        int curTime = curMsgTime.toInt();
        qDebug() << "curTime lastTime:" << curTime - lastTime;
        isShowTime = ((curTime - lastTime) > 60);                         // 两个消息相差一分钟
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
/*************************************************************************
【函数名称】ChattingWindow::resizeEvent(QResizeEvent *event)
【函数功能】改变窗口大小时调整各控件大小
【参数】event
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18 添加了按钮的位置适配
*************************************************************************/
void ChattingWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    ui->listWidget->resize(this->frameSize().width() + 50,
                           this->frameSize().height() - 200);
    ui->widget->resize(this->frameSize().width(), 200);
    ui->widget->move(0, this->frameSize().height() - 200);
    ui->textEdit->resize(this->width() - 20, 125);
    ui->textEdit->move(10, 10);
    ui->btnSend->move(ui->textEdit->width()+ui->textEdit->x()
                      - ui->btnSend->width() - 10,
                        ui->textEdit->height()+ui->textEdit->y()
                      - ui->btnSend->height() - 10);                          //发送按钮的位置调整
    ui->btnRandom->move(ui->textEdit->width()+ui->textEdit->x()
                        - ui->btnRandom->width() - 10,
                         ui->textEdit->height()+ui->textEdit->y()
                        - ui->btnRandom->height() - 40);                      //随机提问的按钮位置调整
    for(int i = 0; i < ui->listWidget->count(); i++) {                        //聊天气泡的大小调整
        QNChatMessage* messageW = (QNChatMessage*)ui->listWidget->itemWidget(ui->listWidget->item(i));
        QListWidgetItem* item = ui->listWidget->item(i);
        dealMessage(messageW, item, messageW->text(), messageW->time(), messageW->userType());
    }
}

/*************************************************************************
【函数名称】ChattingWindow::on_btnSend_clicked()
【函数功能】把信息发送给全体
【参数】无
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18 更改了发送消息的逻辑
*************************************************************************/
void ChattingWindow::on_btnSend_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    if (msg == "") {
        return;                                                              //空消息不发送
    }
    if (m_pTeacherProc->SendStrChat(msg)) {
        ui->textEdit->setText("");                                           //发送结束则清空聊天输入框
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
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);              //在界面最下一行显示发送的消息
}

/*************************************************************************
【函数名称】ChattingWindow::on_btnRandom_clicked()
【函数功能】根据发送的信息更新界面
【参数】无
【返回值】
【开发者及日期】徐赫临 2020-06-19
【更改记录】2020-06-19 此功能可能仍有问题
          2020-06-20 徐赫临修复了多人进入推出之后可能引起的错误
*************************************************************************/
void ChattingWindow::on_btnRandom_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    if (msg == "") {
        return;                                                              //空消息不发送
    }
    unsigned int idx = m_pTeacherProc->GetRdmConnectionIdx();                //返回vector中随机的idx
    if (idx >= m_pTeacherProc->GetStudentCount()) {
        return;
    }
    msg = "Random Question to ["
            + QString::fromStdString(m_pTeacherProc->GetStudentName(idx))
            + "] :\n" + msg;                                                 //显示消息被发给了谁
    if (m_pTeacherProc->SendStrChatTo(m_pTeacherProc->GetConnectionIdx(idx), msg)) {
        ui->textEdit->setText("");                                           //发送结束则清空聊天输入框
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
    ui->listWidget->setCurrentRow(ui->listWidget->count() - 1);              //在界面最下一行显示发送的消息
}
