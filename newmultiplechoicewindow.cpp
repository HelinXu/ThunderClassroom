/*************************************************************************
【文件名】newmultiplechoicewindow
【功能模块和目的】教师新建题目类的界面。
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-17 徐赫临增加了时间限制，单选与多选的区别
2020-06-20 徐赫临增加注释
*************************************************************************/
#include "newmultiplechoicewindow.h"
#include "ui_newmultiplechoicewindow.h"

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::NewMultipleChoiceWindow(TeacherProcess* pProc, QWidget *parent)
【函数功能】构造函数。一开始不能结束答题/发题。
【参数】pPrc流程指针
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
NewMultipleChoiceWindow::NewMultipleChoiceWindow(TeacherProcess* pProc, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMultipleChoiceWindow)
{
    ui->setupUi(this);
    ui->spinTimeLimit->setSuffix(" seconds");
    ui->spinTimeLimit->setRange(0, 600);
    m_pTimer = new QTimer();
    m_pTimer->setInterval(1000);
    m_uTimeCost = 0;
    this->m_pProc = pProc;
    m_uMtpChoiceNumber = MultipleChoice::GetTotalMtpChoiceCount() - 1;
    connect(pProc, SIGNAL(RecvAnswer(QString)), this, SLOT(RecvAnswer(QString)));
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    ui->btnSend->setEnabled(0);
    ui->btnStopAnswer->setEnabled(0);
    ui->textEdit->setFocus();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::~NewMultipleChoiceWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
NewMultipleChoiceWindow::~NewMultipleChoiceWindow()
{
    disconnect(m_pProc, SIGNAL(RecvAnswer(QString)), this, SLOT(RecvAnswer(QString)));
    disconnect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    delete ui;
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_btnSave_clicked()
【函数功能】点击动态储存编辑的题目，并检查编辑是否漏输入题目、答案，自动判断是单选还是多选。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-19 徐赫临设置时间限制。
*************************************************************************/
void NewMultipleChoiceWindow::on_btnSave_clicked()
{
    unsigned int CheckAnsCount = 0;                    //总共选择几个选项
    unsigned int TimeLim = ui->spinTimeLimit->value(); //时间限制

    //获取文本和答案
    QString Text = ui->textEdit->toPlainText();
    QString Choice1 = ui->edtChoice1->text();
    QString Choice2 = ui->edtChoice2->text();
    QString Choice3 = ui->edtChoice3->text();
    QString Choice4 = ui->edtChoice4->text();
    bool C1 = ui->checkBoxA->isChecked();
    bool C2 = ui->checkBoxB->isChecked();
    bool C3 = ui->checkBoxC->isChecked();
    bool C4 = ui->checkBoxD->isChecked();

    //判断单选还是多选，判断是否漏输入了内容
    CheckAnsCount = C1 + C2 + C3 + C4;
    if (   ui->textEdit->document()->isEmpty()
        || ui->edtChoice1->text().isEmpty()
        || ui->edtChoice2->text().isEmpty()
        || ui->edtChoice3->text().isEmpty()
        || ui->edtChoice4->text().isEmpty()) {
        QMessageBox msgBox;
        msgBox.setText("Have you forgotten to enter the text?");
        msgBox.exec();
    }
    if (CheckAnsCount == 0) {
        QMessageBox msgBox;
        msgBox.setText("Have you forgotten to set the answer?");
        msgBox.exec();
        ui->btnSend->setEnabled(0);
        return;
    }

    //制作预览信息
    string txt = "Qutetion " + to_string(MultipleChoice::GetTotalMtpChoiceCount() - 1);
    if (CheckAnsCount == 1) {
        txt += " -Single Choice";
    }
    else {
        txt += " -Multiple Choice";
    }
    if (TimeLim) {
        txt += "\nwith time limit of " + to_string(TimeLim) + " seconds.\n";
    }
    else {
        txt += "\nwith no time limit.\n";
    }
        txt = txt + m_pProc->EditMtpChoice(Text, Choice1, Choice2, Choice3, Choice4, C1, C2, C3, C4, TimeLim)
            + "\nKey:\n";
    if (C1) {
        txt += "A";
    }
    if (C2) {
        txt += "B";
    }
    if (C3) {
        txt += "C";
    }
    if (C4) {
        txt += "D";
    }
    if(!(C1 || C2 || C3 || C4)) {
        txt += "None.";
    }
    ui->textBrowser->setText(QString::fromStdString(txt));
    ui->btnSend->setEnabled(1);
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_btnSend_clicked()
【函数功能】发送题目
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-19 徐赫临修改了逻辑：当点击储存的时候应该强制保存当前的题目。
    //QMessageBox msgBox;
    //msgBox.setWindowTitle("Success");
    //msgBox.setText("Successfully sent to all students.");
    //msgBox.exec();
    徐赫临改善了用户体验，当成功发送时不需要跳出一个messagebox，直接在按钮上体现发送成功就可以了。
*************************************************************************/
void NewMultipleChoiceWindow::on_btnSend_clicked()
{
    //发送之前强制保存
    on_btnSave_clicked();
    m_pProc->SendMtpChoice();
    ui->btnSend->setText("Successfully sent to all students.");
    ui->btnSend->setEnabled(0);
    ui->btnSave->setEnabled(0);
    ui->btnStopAnswer->setEnabled(1);

    //发送之后不能继续编辑答案
    ui->checkBoxA->setEnabled(0);
    ui->checkBoxB->setEnabled(0);
    ui->checkBoxC->setEnabled(0);
    ui->checkBoxD->setEnabled(0);
    ui->spinTimeLimit->setEnabled(0);
    if (ui->spinTimeLimit->value()) {
        m_pTimer->start();
    }
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_edtText0_returnPressed()
【函数功能】编辑完上一个选项自动跳转到下一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_edtText0_returnPressed()
{
    ui->edtChoice1->setFocus();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_edtChoicex_returnPressed()
【函数功能】编辑完上一个选项自动跳转到下一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_edtChoice1_returnPressed()
{
    ui->edtChoice2->setFocus();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_edtChoicex_returnPressed()
【函数功能】编辑完上一个选项自动跳转到下一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_edtChoice2_returnPressed()
{
    ui->edtChoice3->setFocus();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_edtChoicex_returnPressed()
【函数功能】编辑完上一个选项自动跳转到下一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_edtChoice3_returnPressed()
{
    ui->edtChoice4->setFocus();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_edtChoicex_returnPressed()
【函数功能】编辑完上一个选项自动跳转到下一个选项
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_edtChoice4_returnPressed()
{
    ui->btnSave->setDefault(1);
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::on_btnStopAnswer_clicked()
【函数功能】发送停止答题的信号
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::on_btnStopAnswer_clicked()
{
    m_pProc->StopAnswering();
    ui->btnStopAnswer->setEnabled(0);
    ui->btnStopAnswer->setText("Stopped.");
    m_pTimer->stop();
}

/*************************************************************************
【函数名称】NewMultipleChoiceWindow::RecvAnswer(QString Answer)
【函数功能】收到答案时显示在combox中，同时实时在界面上显示正确率
【参数】QString Answer，显示的内容
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-17 徐赫临解决了本信号不会被触发的问题
*************************************************************************/
void NewMultipleChoiceWindow::RecvAnswer(QString Answer) {
    ui->cmbReceiveAnswer->insertItem(0, Answer);
    ui->cmbReceiveAnswer->setCurrentIndex(0);
    unsigned int CorrectRate = (unsigned int)(MultipleChoice::GetCorrectRate(m_uMtpChoiceNumber) * 100);
    unsigned int CorrectCount = MultipleChoice::GetCorrectCount(m_uMtpChoiceNumber);
    unsigned int TotalCount = MultipleChoice::GetTotalAnswerCount(m_uMtpChoiceNumber);
    ui->lblCorrectRate->setText("Q"
                                + QString::fromStdString(to_string(m_uMtpChoiceNumber)) + ": "
                                + QString::fromStdString(to_string(CorrectRate)) + "% correct with "
                                + QString::fromStdString(to_string(CorrectCount)) + " correct ans. out of "
                                + QString::fromStdString(to_string(TotalCount)) + ".");
}

/*************************************************************************
【函数名称】 NewMultipleChoiceWindow::closeEvent (QCloseEvent* e)
【函数功能】如果还没有收题，则不允许关闭本窗口
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-17
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::closeEvent (QCloseEvent* e) {
    if(ui->btnStopAnswer->isEnabled()
       || ui->btnSave->isEnabled()
       || ui->btnSend->isEnabled()) {
        e->ignore();
    }
}

/*************************************************************************
【函数名称】AnswerWindow::TimerEvent()
【函数功能】更新timecost，并更新界面显示时间。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void NewMultipleChoiceWindow::TimerEvent(){
    m_uTimeCost++;
    ui->btnStopAnswer->setText("AutoStop Answering after "
                               + QString::fromStdString(to_string(ui->spinTimeLimit->value() - m_uTimeCost))
                               + " seconds.");
    if (ui->spinTimeLimit->value() - m_uTimeCost == 0) {
        on_btnStopAnswer_clicked();
    }
}

