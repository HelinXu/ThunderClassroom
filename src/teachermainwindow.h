/*************************************************************************
【文件名】teachermainwindow
【功能模块和目的】教师主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
#ifndef TEACHERMAINWINDOW_H
#define TEACHERMAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QShowEvent>
#include <QTimer>
#include <QTime>
#include <QMessageBox>
#include "teacherprocess.h"
#include "newmultiplechoicewindow.h"
#include "chattingwindow.h"
#include "ansdatawindow.h"
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QApplication>
#include <QScreen>

enum HIDEPOSATION//隐藏位置
{
    HP_None = 0,
    HP_Top = 1,
    HP_Left = 2,
    HP_Right = 3
};
namespace Ui {
class TeacherMainWindow;
}

/*************************************************************************
【类名】TeacherMainWindow
【接口说明】见注释，槽函数
【功能模块和目的】教师主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
class TeacherMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //构造函数
    explicit TeacherMainWindow(QMainWindow* m_pLogin, QWidget *parent = nullptr);

    //析构函数
    ~TeacherMainWindow();

//以下部分是用来给教师窗口添加贴边自动隐藏功能的
public:
    bool isWindowInScreen(QPoint pos);
    void hideWindow();
    void showWindow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
private:
    int m_screenWidth;
    bool m_isLMousePress;
    QPoint m_relativePos;
    HIDEPOSATION m_hp;
//以上部分是用来给教师窗口添加贴边自动隐藏功能的

private slots:
    //教师在上课禁止推出
    void closeEvent (QCloseEvent* e) override;

    //教师界面出现在桌面上边
    void showEvent(QShowEvent* e) override;

    //开始上课
    void on_btnBeginClass_clicked();

    //控制屏幕分享
    void on_ckbScreenShare_clicked();

    //控制语音分享
    void on_ckbVoiceShare_clicked();

    //下课
    void on_btnEndClass_clicked();

    //上课了，打开一些按钮
    void ClassBegined();

    //下课了，关闭一些按钮
    void ClassEnded();

    //收到学生登陆，更新签到信息
    void RecvStudentLogin(QString Name);

    //收到学生推出，更新签到信息
    void RecvStudentLogout(QString Name, unsigned int Attention);

    //收到聊天，按钮变黄
    void RecvChat(QString Msg);

    //新建题目
    void on_btnNewProblem_clicked();

    //打开聊天界面
    void on_btnChat_clicked();

    //统计作答情况的界面
    void on_pushButton_clicked();

    //推出课堂
    void on_btnExit_clicked();

private:
    Ui::TeacherMainWindow *ui;

    //教师过程指针
    TeacherProcess* m_pProc;

    //计时器
    QTimer* m_pTimer;

    //教师聊天界面指针
    ChattingWindow* m_pChatWin;

    //作答情况窗口指针
    AnsDataWindow* m_pAnsDataWin;

    //登陆界面指针
    QMainWindow* m_pLogin;

    //更新界面按钮的可用性
    void UpdateControlEnabled(bool IsInClass);
};

#endif // TEACHERMAINWINDOW_H
