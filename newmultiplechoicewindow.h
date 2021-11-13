/*************************************************************************
【文件名】newmultiplechoicewindow
【功能模块和目的】教师新建题目类的界面。
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-17 徐赫临增加了时间限制，单选与多选的区别
2020-06-20 徐赫临增加注释
*************************************************************************/
#ifndef NEWMULTIPLECHOICEWINDOW_H
#define NEWMULTIPLECHOICEWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <QCloseEvent>
#include <QTimer>
#include "teacherprocess.h"

namespace Ui {
class NewMultipleChoiceWindow;
}

/*************************************************************************
【类名】NewMultipleChoiceWindow
【功能】新建题目窗口类
【接口说明】见注释，槽函数
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class NewMultipleChoiceWindow : public QDialog
{
    Q_OBJECT

public:
    //构造函数
    explicit NewMultipleChoiceWindow(TeacherProcess* m_pProc = nullptr, QWidget *parent = nullptr);

    //析构函数
    ~NewMultipleChoiceWindow();

    //关闭界面判断是否可以关闭
    void closeEvent (QCloseEvent* e) override;

private slots:
    //储存编辑题目
    void on_btnSave_clicked();

    //发送题目（首先强制储存）
    void on_btnSend_clicked();

    //回车跳转光标
    void on_edtText0_returnPressed();

    //回车跳转光标
    void on_edtChoice1_returnPressed();

    //回车跳转光标
    void on_edtChoice2_returnPressed();

    //回车跳转光标
    void on_edtChoice3_returnPressed();

    //回车跳转光标
    void on_edtChoice4_returnPressed();

    //停止学生答题
    void on_btnStopAnswer_clicked();

    //收到答案，更新界面，实时显示作答情况
    void RecvAnswer(QString);

    void TimerEvent();
private:
    Ui::NewMultipleChoiceWindow *ui;

    //教师流程指针
    TeacherProcess* m_pProc;

    //计时器指针
    QTimer* m_pTimer;

    //题号
    unsigned int m_uMtpChoiceNumber;

    //作答用时
    unsigned int m_uTimeCost;
};

#endif // NEWMULTIPLECHOICEWINDOW_H
