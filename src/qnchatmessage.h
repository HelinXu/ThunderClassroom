/*************************************************************************
【文件名】qnchatmessage
【功能模块和目的】聊天气泡核心类
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临，参考了网络代码
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
#ifndef QNCHATMESSAGE_H
#define QNCHATMESSAGE_H

#include <QWidget>

class QPaintEvent;
class QPainter;
class QLabel;
class QMovie;

/*************************************************************************
【类名】QNChatMessage
【接口说明】见注释，槽函数
【功能模块和目的】聊天气泡核心类
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临，参考了网络代码
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class QNChatMessage : public QWidget
{
    Q_OBJECT
public:
    //构造函数
    explicit QNChatMessage(QWidget *parent = nullptr);

    //用户类型
    enum User_Type{
        User_System,//系统
        User_Me,    //自己
        User_She,   //用户
        User_Time,  //时间
    };

    //设置text序列
    void setTextSuccess();

    //设置text
    void setText(QString text, QString time, QSize allSize, User_Type userType);

    //消息
    QSize getRealString(QString src);

    //方块
    QSize fontRect(QString str);

    //返回消息
    inline QString text() {return m_msg;}

    //返回时间
    inline QString time() {return m_time;}

    //用户类型
    inline User_Type userType() {return m_userType;}

protected:
    //绘制界面
    void paintEvent(QPaintEvent *event);

private:
    //消息
    QString m_msg;

    //时间
    QString m_time;

    //当前时间
    QString m_curTime;

    //大小
    QSize m_allSize;

    //用户类型
    User_Type m_userType = User_System;

    //文本框等部件的大小
    int m_kuangWidth;
    int m_textWidth;
    int m_spaceWid;
    int m_lineHeight;

    //各部件的大小和性质
    QRect m_iconLeftRect;
    QRect m_iconRightRect;
    QRect m_sanjiaoLeftRect;
    QRect m_sanjiaoRightRect;
    QRect m_kuangLeftRect;
    QRect m_kuangRightRect;
    QRect m_textLeftRect;
    QRect m_textRightRect;
    QPixmap m_leftPixmap;
    QPixmap m_rightPixmap;
    QLabel* m_loading = Q_NULLPTR;
    QMovie* m_loadingMovie = Q_NULLPTR;
    bool m_isSending = false;
};

#endif // QNCHATMESSAGE_H
