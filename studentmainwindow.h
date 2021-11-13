/*************************************************************************
【文件名】studentmainwindow
【功能模块和目的】学生主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
#ifndef STUDENTMAINWINDOW_H
#define STUDENTMAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTimer>
#include "studentprocess.h"
#include "answerwindow.h"
#include "loginwindow.h"
#include "chatwindow_student.h"

namespace Ui {
class StudentMainWindow;
}

/*************************************************************************
【类名】StudentMainWindow
【接口说明】见注释，槽函数
【功能模块和目的】学生主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
class StudentMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit StudentMainWindow(QMainWindow* m_pLogin, QWidget *parent = nullptr);

    //析构函数
    ~StudentMainWindow();

    //学生在上课禁止关闭
    void closeEvent (QCloseEvent* e) override;

    //更新界面按钮可用性
    void UpdateControlEnabled(bool IsInClass);

private slots:
    //进入课堂，尝试连接
    void on_btnEnterClass_clicked();

    //推出课堂，发送注意力数据
    void on_btnExitClass_clicked();

    //计时
    void TimerEvent();

    //进入课堂信号
    void ClassEntered();

    //退出课堂信号
    void ClassExited();

    //收到文字消息信号
    void RecvChat(QString Msg);

    //收到屏幕共享消息信号
    void RecvScreen(QImage Img);

    //收到题目
    void RecvProblem(QString MtpChoiceText,
                     unsigned int TimeLimit,
                     unsigned int ProblemNum,
                     bool IsSingleChoice);

    //打开聊天窗口
    void on_btnChat_clicked();

    //收到课程即将结束的信息，主动推出
    void ClassToEnd();

private:
    //学生过程类
    StudentProcess* m_pProc;

    //计时器
    QTimer* m_pTimer;

    //作答窗口
    AnswerWindow* m_pAnsWin;

    //本界面指针
    Ui::StudentMainWindow *ui;

    //登录窗口指针
    QMainWindow* m_pLogin;

    //聊天窗口指针
    ChatWindow_Student* m_pChatWin;

    //学生注意力
    double m_rAttention;

    //学生在课堂的计算次数
    unsigned int m_uInClassCount;

    //学生总共计算次数
    unsigned int m_uTotalCount;
};

#endif // STUDENTMAINWINDOW_H
