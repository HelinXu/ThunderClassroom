/*************************************************************************
【文件名】ansdatawindow
【功能模块和目的】学生答题情况统计页面
【开发者及日期】徐赫临 2020-06-18
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
#ifndef ANSDATAWINDOW_H
#define ANSDATAWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QStringList>
#include "multiplechoice.h"
#include "string"
#include "teacherprocess.h"
using namespace QtCharts;

namespace Ui {
class AnsDataWindow;
}

/*************************************************************************
【类名】AnsDataWindow
【功能】管理员第一界面类
【接口说明】槽函数
【功能模块和目的】学生答题情况统计页面
【开发者及日期】徐赫临 2020-06-18
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
class AnsDataWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    //收到答案槽函数：更新界面
    void RecvAnswer();

public:
    //构造函数
    explicit AnsDataWindow(TeacherProcess* m_pProc, QWidget *parent = nullptr);

    //析构函数
    ~AnsDataWindow();

private:
    Ui::AnsDataWindow *ui;

    //教师流程指针
    TeacherProcess* m_pProc;
};

#endif // ANSDATAWINDOW_H
