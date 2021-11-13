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
#ifndef CHATTINGWINDOW_H
#define CHATTINGWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "qnchatmessage.h"
#include "teacherprocess.h"
namespace Ui {
class ChattingWindow;
}

/*************************************************************************
【类名】ChattingWindow
【功能】教师聊天界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class ChattingWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ChattingWindow(TeacherProcess* pTeacherProc, QWidget *parent = nullptr);

    //析构函数
    ~ChattingWindow();

    //处理消息内容
    void dealMessage(QNChatMessage *messageW,
                     QListWidgetItem *item,
                     QString text,
                     QString time,
                     QNChatMessage::User_Type type);

    //处理消息时间戳
    void dealMessageTime(QString curMsgTime);

protected:
    //改变页面大小
    void resizeEvent(QResizeEvent *event);

private slots:
    //收到消息刷新在页面上
    void RecvChat(QString);

    //发送消息给全体成员
    void on_btnSend_clicked();

    //随机提问
    void on_btnRandom_clicked();

private:
    Ui::ChattingWindow *ui;

    //教师流程
    TeacherProcess* m_pTeacherProc;
};

#endif // CHATTINGWINDOW_H

