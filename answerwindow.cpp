/*************************************************************************
【文件名】answerwindow
【功能模块和目的】学生答题页面
【开发者及日期】徐赫临 2020-06-14
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
#include "answerwindow.h"
#include "ui_answerwindow.h"

/*************************************************************************
【函数名称】构造函数AnswerWindow::AnswerWindow(unsigned int ProblemNumber,
                           StudentProcess* pProc,
                           QString MtpChoiceText,
                           unsigned int TimeLimit,
                           bool IsSingleChoice,
                           QWidget *parent)
【函数功能】需要知道：该问题的编号，问题的文本，学生process指针（停止答题的信号）。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-16 徐赫临增加了传入问题编号的参数，增加了Timer
*************************************************************************/
AnswerWindow::AnswerWindow(unsigned int ProblemNumber,
                           StudentProcess* pProc,
                           QString MtpChoiceText,
                           unsigned int TimeLimit,
                           bool IsSingleChoice,
                           QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnswerWindow)
{
    ui->setupUi(this);

    //初始化数据成员
    this->m_uProblemNumber = ProblemNumber;
    this->m_pProc = pProc;
    m_pTimer = new QTimer();
    m_pTimer->setInterval(1000);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    m_pTimer->start();
    connect(pProc, SIGNAL(StopAnswering()), this, SLOT(StopAnswering()));
    m_uTimeCost = 0;
    m_bIsSingleChoice = IsSingleChoice;
    m_uTimeLimit = TimeLimit;

    //初始化显示的题干内容
    QString Display = "Question " + QString::fromStdString(to_string(m_uProblemNumber));
    if (m_bIsSingleChoice) {
        Display += " -Single choice";
    }
    else {
        Display += " -Multiple choice";
    }
    if (m_uTimeLimit) {
        Display += "\nwith time limit of " + QString::fromStdString(to_string(m_uTimeLimit)) + " seconds.\n\n\n";
    }
    else {
        Display += "\nwith no time limit.\n\n\n";
    }
    Display += MtpChoiceText;
    ui->textBrowser->setText(Display);
}

/*************************************************************************
【函数名称】析构函数AnswerWindow::~AnswerWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-6-16 徐赫临更改了错误：此处不能把学生process的指针delete
*************************************************************************/
AnswerWindow::~AnswerWindow()
{
    m_pTimer->stop();
    disconnect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    disconnect(m_pProc, SIGNAL(StopAnswering()), this, SLOT(StopAnswering()));
    delete m_pTimer;
    m_pTimer = nullptr;
    delete ui;
}

/*************************************************************************
【函数名称】AnswerWindow::on_btnHandIn_clicked()
【函数功能】上交答案
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-16 增加了反馈题目编号和答题用时的内容
*************************************************************************/
void AnswerWindow::on_btnHandIn_clicked()
{
    bool C1 = ui->ckbA->isChecked();
    bool C2 = ui->ckbB->isChecked();
    bool C3 = ui->ckbC->isChecked();
    bool C4 = ui->ckbD->isChecked();

    //提交答案
    m_pProc->HandInMtpChoice(m_uProblemNumber, m_uTimeCost, C1, C2, C3, C4);

    //提交答案后不能修改
    m_pTimer->stop();
    ui->btnHandIn->setEnabled(0);
    ui->ckbA->setEnabled(0);
    ui->ckbB->setEnabled(0);
    ui->ckbC->setEnabled(0);
    ui->ckbD->setEnabled(0);
}

/*************************************************************************
【函数名称】AnswerWindow::StopAnswering()
【函数功能】收到教师停止答题的信号，强行点击上交按钮，并显示时间结束的messagebox
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void AnswerWindow::StopAnswering() {
    if(!(ui->btnHandIn->isEnabled())) {
        return;
    }
    bool C1 = ui->ckbA->isChecked();
    bool C2 = ui->ckbB->isChecked();
    bool C3 = ui->ckbC->isChecked();
    bool C4 = ui->ckbD->isChecked();

    //强制交卷
    m_pProc->HandInMtpChoice(m_uProblemNumber, m_uTimeCost, C1, C2, C3, C4);
    m_pTimer->stop();
    QMessageBox box;
    box.setText("Time is up!");
    box.exec();

    //提交后不能更改
    ui->btnHandIn->setEnabled(0);
    ui->ckbA->setEnabled(0);
    ui->ckbB->setEnabled(0);
    ui->ckbC->setEnabled(0);
    ui->ckbD->setEnabled(0);
}

/*************************************************************************
【函数名称】AnswerWindow::TimerEvent()
【函数功能】更新timecost，并更新界面显示时间。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void AnswerWindow::TimerEvent(){
    m_uTimeCost++;

    //倒计时
    if (m_uTimeLimit) {
        ui->lblTimer->setText("Time left: " + QString::fromStdString(to_string(m_uTimeLimit - m_uTimeCost)) + " seconds.");
        if (m_uTimeLimit - m_uTimeCost == 0) {
            on_btnHandIn_clicked();
        }
    }
    //正计时（如果没有时间限制）
    else {
        ui->lblTimer->setText("Time cost: " + QString::fromStdString(to_string(m_uTimeCost)) + " seconds.");
    }
}

/*************************************************************************
【函数名称】AnswerWindow::closeEvent (QCloseEvent* e)
【函数功能】还未提交禁止关闭窗口
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-17
【更改记录】
*************************************************************************/
void AnswerWindow::closeEvent (QCloseEvent* e) {
    //还未提交禁止关闭窗口
    if (ui->btnHandIn->isEnabled()) {
        e->ignore();
    }
}

/*************************************************************************
【函数名称】AnswerWindow::on_ckbA_stateChanged(int arg1)
【函数功能】如果是单选题，则强制只选一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-19
【更改记录】
*************************************************************************/
void AnswerWindow::on_ckbA_stateChanged(int arg1)
{
    if (m_bIsSingleChoice) {
        if (ui->ckbA->isChecked()) {
            ui->ckbB->setChecked(0);
            ui->ckbC->setChecked(0);
            ui->ckbD->setChecked(0);
        }
    }
}

/*************************************************************************
【函数名称】AnswerWindow::on_ckbB_stateChanged(int arg1)
【函数功能】如果是单选题，则强制只选一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-19
【更改记录】
*************************************************************************/
void AnswerWindow::on_ckbB_stateChanged(int arg1)
{
    if (m_bIsSingleChoice) {
        if (ui->ckbB->isChecked()) {
            ui->ckbA->setChecked(0);
            ui->ckbC->setChecked(0);
            ui->ckbD->setChecked(0);
        }
    }
}

/*************************************************************************
【函数名称】AnswerWindow::on_ckbC_stateChanged(int arg1)
【函数功能】如果是单选题，则强制只选一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-19
【更改记录】
*************************************************************************/
void AnswerWindow::on_ckbC_stateChanged(int arg1)
{
    if (m_bIsSingleChoice) {
        if (ui->ckbC->isChecked()) {
            ui->ckbB->setChecked(0);
            ui->ckbA->setChecked(0);
            ui->ckbD->setChecked(0);
        }
    }
}

/*************************************************************************
【函数名称】AnswerWindow::on_ckbD_stateChanged(int arg1)
【函数功能】如果是单选题，则强制只选一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-19
【更改记录】
*************************************************************************/
void AnswerWindow::on_ckbD_stateChanged(int arg1)
{
    if (m_bIsSingleChoice) {
        if (ui->ckbD->isChecked()) {
            ui->ckbB->setChecked(0);
            ui->ckbC->setChecked(0);
            ui->ckbA->setChecked(0);
        }
    }
}
