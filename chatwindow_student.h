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
#ifndef CHATWINDOW_STUDENT_H
#define CHATWINDOW_STUDENT_H

#include <QMainWindow>
#include <QListWidgetItem>
#include "qnchatmessage.h"
#include "studentprocess.h"

namespace Ui {
class ChatWindow_Student;
}

/*************************************************************************
【类名】ChatWindow_Student
【功能】学生聊天界面类
【接口说明】槽函数
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class ChatWindow_Student : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit ChatWindow_Student(StudentProcess* m_pProc, QWidget *parent = nullptr);

    //析构函数
    ~ChatWindow_Student();

    //处理消息文本
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
    //发送给全体成员
    void on_btnSendToAll_clicked();

    //收到消息刷新在页面上
    void RecvChat(QString);

    //发送给老师
    void on_btnSendToTeacher_clicked();

private:
    Ui::ChatWindow_Student *ui;

    //学生流程类
    StudentProcess* m_pProc;
};

#endif // CHATWINDOW_STUDENT_H
