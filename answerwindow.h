/*************************************************************************
【文件名】answerwindow
【功能模块和目的】学生答题页面
【开发者及日期】徐赫临 2020-06-14
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
#ifndef ANSWERWINDOW_H
#define ANSWERWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <QCloseEvent>
#include "studentprocess.h"

namespace Ui {
class AnswerWindow;
}

/*************************************************************************
【类名】AnswerWindow
【功能】学生回答窗口
【接口说明】见注释
【开发者及日期】徐赫临 2020-06-14
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class AnswerWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit AnswerWindow(unsigned int ProblemNumber,
                          StudentProcess* m_pProc,
                          QString MtpChoiceText,
                          unsigned int TimeLimit,
                          bool IsSingleChoice,
                          QWidget *parent = nullptr);

    //析构函数
    ~AnswerWindow();

    //关闭时，需要确保题目已经作答
    void closeEvent (QCloseEvent* e);
private slots:
    //提交
    void on_btnHandIn_clicked();

    //停止作答
    void StopAnswering();

    //计时并更新界面
    void TimerEvent();

    //单选题防止多选
    void on_ckbA_stateChanged(int arg1);

    //单选题防止多选
    void on_ckbB_stateChanged(int arg1);

    //单选题防止多选
    void on_ckbC_stateChanged(int arg1);

    //单选题防止多选
    void on_ckbD_stateChanged(int arg1);

private:
    Ui::AnswerWindow *ui;

    //学生过程的指针，保证与StudentMainWindow是同一个Process
    StudentProcess* m_pProc;

    //计时器
    QTimer* m_pTimer;

    //是否单选题
    bool m_bIsSingleChoice;

    //时间限制
    unsigned int m_uTimeLimit;

    //花费的时间
    unsigned int m_uTimeCost;

    //题目编号
    unsigned int m_uProblemNumber;
};

#endif // ANSWERWINDOW_H
