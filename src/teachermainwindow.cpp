/*************************************************************************
【文件名】teachermainwindow
【功能模块和目的】教师主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
#include "teachermainwindow.h"
#include "ui_teachermainwindow.h"
#include <QGuiApplication>
#include <QScreen>
#include <QSize>

/*************************************************************************
【函数名称】TeacherMainWindow::TeacherMainWindow(QMainWindow* pLogin, QWidget *parent)
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
TeacherMainWindow::TeacherMainWindow(QMainWindow* pLogin, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TeacherMainWindow)
{
    ui->setupUi(this);
    //一些手动的初始化
    ui->btnChat->setEnabled(0);
    ui->btnEndClass->setEnabled(0);
    ui->btnNewProblem->setEnabled(0);
    ui->pushButton->setEnabled(0);
    ui->ckbVoiceShare->setEnabled(0);
    ui->ckbScreenShare->setEnabled(0);
    //与窗口贴边自动隐藏有关的变量初始化
    m_hp = HP_None;
    m_isLMousePress = false;
    QRect rect = QGuiApplication::primaryScreen()->geometry();
    m_screenWidth = rect.width();
    setWindowFlags(  Qt::FramelessWindowHint
                   | Qt::WindowStaysOnTopHint
                   | Qt::WindowCloseButtonHint);
    m_pProc = new TeacherProcess(this);
    this->m_pLogin = pLogin;
    //建立信号和槽的连接关系
    //一定要在m_pProc构造后才能建立
    //connect是建立联系，而非调用槽函数
    connect(m_pProc, SIGNAL(ClassBegined()), this, SLOT(ClassBegined()));
    connect(m_pProc, SIGNAL(ClassEnded()), this, SLOT(ClassEnded()));
    connect(m_pProc, SIGNAL(RecvStudentLogin(QString)), this, SLOT(RecvStudentLogin(QString)));
    connect(m_pProc, SIGNAL(RecvStudentLogout(QString, unsigned int)),
            this, SLOT(RecvStudentLogout(QString, unsigned int)));
    connect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    m_pChatWin = new ChattingWindow(m_pProc);
    m_pAnsDataWin = new AnsDataWindow(m_pProc);
}

/*************************************************************************
【函数名称】TeacherMainWindow::~TeacherMainWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
TeacherMainWindow::~TeacherMainWindow()
{
    //先disconnected，再释放业务流程类
    disconnect(m_pProc, SIGNAL(ClassBegined()), this, SLOT(ClassBegined()));
    disconnect(m_pProc, SIGNAL(ClassEnded()), this, SLOT(ClassEnded()));
    disconnect(m_pProc, SIGNAL(RecvStudentLogin(QString)), this, SLOT(RecvStudentLogin(QString)));
    disconnect(m_pProc, SIGNAL(RecvStudentLogout(QString, unsigned int)),
               this, SLOT(RecvStudentLogout(QString, unsigned int)));
    disconnect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    delete m_pChatWin;
    m_pChatWin = nullptr;
    delete m_pAnsDataWin;
    m_pAnsDataWin = nullptr;
    delete ui;
}

/*************************************************************************
【函数名称】TeacherMainWindow::closeEvent (QCloseEvent* e)
【函数功能】在课堂中的时候不能推出课堂
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::closeEvent (QCloseEvent* e) {
    if (m_pProc->IsInClass) {
        e->ignore();
        return;
    }
    m_pLogin->setWindowOpacity(1.0);
}

/*************************************************************************
【函数名称】TeacherMainWindow::showEvent(QShowEvent* e)
【函数功能】让教师界面在出现时出现在页面最上端
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::showEvent(QShowEvent* e) {
    int iWidth = QGuiApplication::screens()[0]->size().width();
    this->move((iWidth - this->width()) / 2, 0);
    e->accept();
}

/*************************************************************************
【函数名称】TeacherMainWindow::UpdateControlEnabled(bool IsInClass)
【函数功能】设置按钮的可点击性，根据是否在课堂改变状态
【参数】是否在课堂中
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::UpdateControlEnabled(bool IsInClass) {
    if (!IsInClass) {
        ui->cmbStudent->clear();
        ui->ckbScreenShare->setChecked(false);
        ui->ckbVoiceShare->setChecked(false);
    }
    ui->btnBeginClass->setEnabled(!IsInClass);
    ui->btnEndClass->setEnabled(IsInClass);
    ui->ckbVoiceShare->setEnabled(IsInClass);
    ui->ckbScreenShare->setEnabled(IsInClass);
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_btnBeginClass_clicked()
【函数功能】开始上课，设置按钮的可用性
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_btnBeginClass_clicked() {
    if (m_pProc->BeginClass()) {
        ui->cmbStudent->clear();
    }
    ui->btnChat->setEnabled(1);
    ui->btnEndClass->setEnabled(1);
    ui->btnNewProblem->setEnabled(1);
    ui->pushButton->setEnabled(1);
    ui->ckbVoiceShare->setEnabled(1);
    ui->ckbScreenShare->setEnabled(1);
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_ckbScreenShare_clicked()
【函数功能】是否分享屏幕
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_ckbScreenShare_clicked()
{
    if (ui->ckbScreenShare->isChecked()) {
        ui->ckbScreenShare->setChecked(m_pProc->StartScreenShare());
    }
    else{
        ui->ckbScreenShare->setChecked(m_pProc->StopScreenShare());
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_ckbVoiceShare_clicked()
【函数功能】是否发送语音
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_ckbVoiceShare_clicked()
{
    if (ui->ckbVoiceShare->isChecked()) {
        ui->ckbVoiceShare->setChecked(m_pProc->StartVoiceShare());
    }
    else{
        ui->ckbVoiceShare->setChecked(m_pProc->StopVoiceShare());
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_btnEndClass_clicked()
【函数功能】结束课堂，发送给学生推出课堂的信息，并回收注意力
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_btnEndClass_clicked() {
    m_pProc->SendEndingSignal();
    ui->btnChat->setEnabled(0);
    ui->btnEndClass->setEnabled(0);
    ui->btnNewProblem->setEnabled(0);
    ui->pushButton->setEnabled(0);
    ui->ckbVoiceShare->setEnabled(0);
    ui->ckbScreenShare->setEnabled(0);
    ui->btnEndClass->setText("Please wait");
    //等待3秒再推出
    QTime dieTime = QTime::currentTime().addMSecs(3000);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    ui->btnEndClass->setText("下课");
    m_pProc->EndClass();
}

/*************************************************************************
【函数名称】TeacherMainWindow::ClassBegined()
【函数功能】开始上课的按钮可用性
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::ClassBegined() {
    UpdateControlEnabled(true);
}

/*************************************************************************
【函数名称】TeacherMainWindow::ClassEnded()
【函数功能】设置结束上课的按钮可用性
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::ClassEnded() {
    UpdateControlEnabled(false);
}

/*************************************************************************
【函数名称】TeacherMainWindow::RecvStudentLogin(QString Name)
【函数功能】接受学生上课的信号
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-19 徐赫临增加了课堂签到和推出的记录
*************************************************************************/
void TeacherMainWindow::RecvStudentLogin(QString Name){
    int idx = ui->cmbStudent->findText(Name);
    if (idx == -1) {
        ui->cmbStudent->insertItem(0, Name);
        idx  = 0;
    }
    ui->cmbStudent->setCurrentIndex(idx);
    QTime current_time = QTime::currentTime();
    QString Time_qstring = current_time.toString ("hh:mm:ss");
    ui->cmbAttandance->insertItem(0, Time_qstring + " " + Name + " Login");
    ui->cmbAttandance->setCurrentIndex(0);
}

/*************************************************************************
【函数名称】TeacherMainWindow::RecvStudentLogout(QString Name)
【函数功能】接受学生推出的信号
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-19 徐赫临增加了课堂签到和推出的记录
*************************************************************************/
void TeacherMainWindow::RecvStudentLogout(QString Name, unsigned int Attention) {
    int idx = ui->cmbStudent->findText(Name);
    if (idx != -1) {
        ui->cmbStudent->removeItem(idx);
    }
    QTime current_time = QTime::currentTime();
    QString Time_qstring = current_time.toString ("hh:mm:ss");
    ui->cmbAttandance->insertItem(0, Time_qstring + " " + Name
                                  + " Logout, attention: "
                                  + QString::fromStdString(to_string(Attention))
                                  + "%");
    ui->cmbAttandance->setCurrentIndex(0);
}

/*************************************************************************
【函数名称】TeacherMainWindow::RecvChat(QString Msg)
【函数功能】收到信息，按钮变成黄色
【参数】没有用
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::RecvChat(QString Msg) {
    ui->btnChat->setStyleSheet("background: rgb(225, 158, 51);");
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_btnNewProblem_clicked()
【函数功能】新建题目
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_btnNewProblem_clicked()
{
    m_pProc->AddNewMtpChoice();
    NewMultipleChoiceWindow* pNewMtpChoiceWin = new NewMultipleChoiceWindow(m_pProc);
    pNewMtpChoiceWin->exec();
    delete pNewMtpChoiceWin;
    pNewMtpChoiceWin = nullptr;
}

/*************************************************************************
【函数名称】打开聊天窗口TeacherMainWindow::on_btnChat_clicked()
【函数功能】打开聊天窗口。其中先关闭再打开可以保证窗口出现在最顶层
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_btnChat_clicked()
{
    m_pChatWin->close();
    m_pChatWin->show();
    ui->btnChat->setStyleSheet("");
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_pushButton_clicked()
【函数功能】//这是显示答题情况统计的按钮，显示答题情况
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_pushButton_clicked()
{
    m_pAnsDataWin->close();
    m_pAnsDataWin->show();
}

/*************************************************************************
【函数名称】TeacherMainWindow::isWindowInScreen(QPoint pos)
【函数功能】判断教师窗口是否在屏幕里。用在教师窗口的贴边自动隐藏
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
//判断当前鼠标位置，并根据位置确定信息
bool TeacherMainWindow::isWindowInScreen(QPoint pos)
{
    if(pos.x() < 1){
        m_hp = HP_Left;
        return false;
    }
    else if(pos.x() > m_screenWidth - 1){
        m_hp = HP_Right;
        return false;
    }
    else if(pos.y() < 1){
        m_hp = HP_Top;
        return false;
    }
    else{
        m_hp = HP_None;
        return true;
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::hideWindow()
【函数功能】//隐藏窗口的动画
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::hideWindow()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(QRect(x(), y(), width(), height()));
    if(m_hp == HP_Top)
        animation->setEndValue(QRect(x(), 5 - height(), width(), height()));
    else if(m_hp == HP_Left)
        animation->setEndValue(QRect(2 - width(), y(), width(), height()));
    else if(m_hp == HP_Right)
        animation->setEndValue(QRect(m_screenWidth - 2, y(), width(), height()));
    animation->setDuration(250);
    animation->start();
}

/*************************************************************************
【函数名称】TeacherMainWindow::showWindow()
【函数功能】//显示窗口的动画
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::showWindow()
{
    QPropertyAnimation * animation = new QPropertyAnimation(this, "geometry");
    animation->setStartValue(QRect(x(), y(), width(), height()));
    if(m_hp == HP_Top) {
        animation->setEndValue(QRect(x(), -1 , width(), height()));
    }
    else if(m_hp == HP_Left) {
        animation->setEndValue(QRect(-1, y(), width(), height()));
    }
    else if(m_hp == HP_Right) {
        animation->setEndValue(QRect(m_screenWidth - width() - 1, y(), width(), height()));
    }
    animation->setDuration(250);
    animation->start();
}

/*************************************************************************
【函数名称】TeacherMainWindow::mousePressEvent(QMouseEvent *event)
【函数功能】触发检验教师窗口位置的行为
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_isLMousePress = true;
        m_relativePos = event->globalPos() - pos();         //记录相对位置
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::mouseReleaseEvent(QMouseEvent *event)
【函数功能】放开鼠标的行为
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_isLMousePress = false;
}

/*************************************************************************
【函数名称】TeacherMainWindow::mouseMoveEvent(QMouseEvent *event)
【函数功能】与鼠标移动有关的动画
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(m_isLMousePress && isWindowInScreen(event->globalPos())) {
        move(event->globalPos() - m_relativePos);//实现无边框移动
    }
    else if(m_isLMousePress && !isWindowInScreen(event->globalPos()))
    {
                                                 //特殊位置，移动规则不同
        int x = event->globalPos().x();
        int y = event->globalPos().y();
        if(m_hp == HP_Top) {                     //比如当前鼠标位置为屏幕最上面时，将纵坐标拉至鼠标处，此后只改变横坐标
            move(x-m_relativePos.x(),y);
        }
        else if(m_hp == HP_Left) {
            move(x,y - m_relativePos.y());
        }
        else if(m_hp == HP_Right) {
            move(x-width(),y - m_relativePos.y());
        }
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::enterEvent(QEvent *event)
【函数功能】用于窗口贴边自动隐藏
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None) {
        showWindow();
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::leaveEvent(QEvent *event)
【函数功能】用于窗口贴边自动隐藏
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    if(m_hp != HP_None) {
        hideWindow();
    }
}

/*************************************************************************
【函数名称】TeacherMainWindow::on_btnExit_clicked()
【函数功能】自定义的关闭窗口按钮功能
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void TeacherMainWindow::on_btnExit_clicked()
{
    if (m_pProc->IsInClass) {
        return;
    }
    this->close();
}

