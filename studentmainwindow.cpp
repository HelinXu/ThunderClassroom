/*************************************************************************
【文件名】studentmainwindow
【功能模块和目的】学生主窗口
【开发者及日期】徐赫临 2020-06-16
【版权信息】徐赫临，参考了网络代码
【更改记录】
2020-06-16 徐赫临将qdialog的窗口移植到了mainwindow上
*************************************************************************/
#include "studentmainwindow.h"
#include "ui_studentmainwindow.h"
#include <QImage>
#include <QPixmap>

/*************************************************************************
【函数名称】StudentMainWindow::StudentMainWindow(QMainWindow* pLogin, QWidget *parent)
【函数功能】构造函数
【参数】传入流程类指针
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-20 徐赫临做了代码规范调整
*************************************************************************/
StudentMainWindow::StudentMainWindow(QMainWindow* pLogin, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StudentMainWindow)
{
    ui->setupUi(this);
    m_pProc = new StudentProcess(this);
    m_pAnsWin = nullptr; //@TODO
    this->m_pLogin = pLogin;
    m_pChatWin = new ChatWindow_Student(m_pProc);
    //建立信号和槽的连接关系
    //一定要在m_pProc构造后才能建立
    //connect是建立联系，而非调用槽函数
    connect(m_pProc, SIGNAL(ClassEntered()), this, SLOT(ClassEntered()));
    connect(m_pProc, SIGNAL(ClassExited()), this, SLOT(ClassExited()));
    connect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    connect(m_pProc, SIGNAL(RecvScreen(QImage)), this, SLOT(RecvScreen(QImage)));
    connect(m_pProc, SIGNAL(RecvProblem(QString, unsigned int, unsigned int, bool)),
            this, SLOT(RecvProblem(QString, unsigned int, unsigned int, bool)));
    connect(m_pProc, SIGNAL(ClassToEnd()), this, SLOT(ClassToEnd()));
    m_pTimer = new QTimer();
    m_pTimer->setInterval(200);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    m_pTimer->start();
    //只显示关闭窗口按钮，没有？按钮
    this->setWindowFlags(  Qt::Dialog
                         | Qt::WindowCloseButtonHint
                         | Qt::WindowMaximizeButtonHint
                         | Qt::WindowFullscreenButtonHint);
    //设定控件是否可用
    UpdateControlEnabled(false);
}

/*************************************************************************
【函数名称】StudentMainWindow::~StudentMainWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-20 徐赫临做了代码规范调整
*************************************************************************/
StudentMainWindow::~StudentMainWindow()
{
    m_pTimer->stop();
    disconnect(m_pTimer, SIGNAL(timeout()), this, SLOT(TimerEvent()));
    delete m_pTimer;
    m_pTimer = nullptr;
    //先disconnected，再释放业务流程类
    disconnect(m_pProc, SIGNAL(ClassEntered()), this, SLOT(ClassEntered()));
    disconnect(m_pProc, SIGNAL(ClassExited()), this, SLOT(ClassExited()));
    disconnect(m_pProc, SIGNAL(RecvChat(QString)), this, SLOT(RecvChat(QString)));
    disconnect(m_pProc, SIGNAL(RecvScreen(QImage)), this, SLOT(RecvScreen(QImage)));
    disconnect(m_pProc, SIGNAL(RecvProblem(QString, unsigned int, unsigned int, bool)),
               this, SLOT(RecvProblem(QString, unsigned int, unsigned int, bool)));
    disconnect(m_pProc, SIGNAL(ClassToEnd()), this, SLOT(ClassToEnd()));
    delete m_pProc;
    m_pProc = nullptr;
    delete m_pChatWin;
    m_pChatWin = nullptr;
    delete ui;
}

/*************************************************************************
【函数名称】StudentMainWindow::UpdateControlEnabled(bool IsInClass)
【函数功能】调整上课下课的按钮状态。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-20 徐赫临做了代码规范调整
*************************************************************************/
void StudentMainWindow::UpdateControlEnabled(bool IsInClass) {
    //非上课状态，清空共享屏幕显示、清空聊天记录、清空聊天输入文本框
    if (!IsInClass) {
        ui->lblSharedScreen->clear();
        ui->btnChat->setStyleSheet("");
    }
    //IP输入文本框在非上课状态可用
    ui->edtIP->setEnabled(!IsInClass);
    //进入课堂按钮在非上课状态可用
    ui->btnEnterClass->setEnabled(!IsInClass);
    //退出课堂按钮在上课状态可用
    ui->btnExitClass->setEnabled(IsInClass);
    //聊天按钮在上课状态可用
    ui->btnChat->setEnabled(IsInClass);
}

/*************************************************************************
【函数名称】StudentMainWindow::on_btnEnterClass_clicked()
【函数功能】进入课堂
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】2020-06-19 徐赫临更新了开始计时的数据初值
*************************************************************************/
void StudentMainWindow::on_btnEnterClass_clicked() {
    //IP不为空在能进入课堂
    if (!ui->edtIP->text().isEmpty()) {
        //更新界面控件状态为非上课状态
        UpdateControlEnabled(false);
        //临时锁死IP输入框
        ui->edtIP->setEnabled(false);
        //临时锁死退出课堂按钮
        ui->btnExitClass->setEnabled(false);
        //尝试进入课堂
        m_pProc->EnterClass(ui->edtIP->text());
        //开始计时
        m_pTimer->start();
        m_uTotalCount = 0;
        m_uInClassCount = 0;
    }
}

/*************************************************************************
【函数名称】StudentMainWindow::on_btnExitClass_clicked()
【函数功能】推出课堂，并在推出之前发送注意力信息
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::on_btnExitClass_clicked() {
    m_pProc->SendAttention(m_rAttention);
    m_pTimer->stop();
    ui->btnExitClass->setEnabled(0);
    ui->btnExitClass->setText("Please wait.");
    //等待3秒再推出
    QTime dieTime = QTime::currentTime().addMSecs(3000);
    while( QTime::currentTime() < dieTime ) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
    m_pProc->ExitClass();
    ui->btnExitClass->setText("Quit Class");
    ui->btnEnterClass->setEnabled(1);
}

/*************************************************************************
【函数名称】StudentMainWindow::closeEvent (QCloseEvent* e)
【函数功能】当学生在课堂时禁止推出
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
2020-06-18 链接的10秒等待期禁止关闭
2020-06-18 徐赫临添加了是否正在尝试链接的判断,但是问题还是没有解决。
*************************************************************************/
void StudentMainWindow::closeEvent (QCloseEvent* e) {
    //上课中禁止关闭窗口,链接的10秒等待期禁止关闭
    if (m_pProc->IsInClass) {
        e->ignore();
        return;
    }
    m_pLogin->setWindowOpacity(1.0);
}

/*************************************************************************
【函数名称】StudentMainWindow::TimerEvent()
【函数功能】计时，计算学生的注意力，并在界面上显示
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::TimerEvent() {
    //定时更新窗口标题
    if (m_pProc->IsInClass) {
        //上课中，窗口是激活状态
        if(this->isActiveWindow()) {
            this->setWindowTitle("Student "
                                 + QString::fromStdString(User::GetLoginedUser()->GetName())
                                 +  " Focused");
            m_uInClassCount++;
            m_uTotalCount++;
        }
        //上课中，窗口不是激活状态
        else {
            this->setWindowTitle("Student "
                                 + QString::fromStdString(User::GetLoginedUser()->GetName())
                                 + " unFocused");
            m_uTotalCount++;
        }
        m_rAttention = (double)m_uInClassCount / (double)m_uTotalCount;
        ui->lblAttention->setText("Attention: "
                                  + QString::fromStdString(to_string((unsigned int)(m_rAttention * 100)))
                                  + "%");
    }
    else {
        //非上课
        this->setWindowTitle("Student "
                             + QString::fromStdString(User::GetLoginedUser()->GetName())
                             + " offline");
    }
}

/*************************************************************************
【函数名称】StudentMainWindow::ClassToEnd()
【函数功能】收到教师即将下课的信号，主动推出课堂并发送注意力信息
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::ClassToEnd() {
    on_btnExitClass_clicked();
}

/*************************************************************************
【函数名称】StudentMainWindow::ClassEntered()
【函数功能】进入课堂
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
//进入课堂信号
void StudentMainWindow::ClassEntered() {
    ui->btnEnterClass->setText("Enter Class");
    m_pTimer->start();
    UpdateControlEnabled(true);
}

/*************************************************************************
【函数名称】StudentMainWindow::ClassExited()
【函数功能】设置界面为推出课堂的
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
//退出课堂信号
void StudentMainWindow::ClassExited() {
    UpdateControlEnabled(false);
}

/*************************************************************************
【函数名称】StudentMainWindow::RecvChat(QString Msg)
【函数功能】//收到文字消息信号,按钮变成黄色
【参数】没有用
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::RecvChat(QString Msg) {
    ui->btnChat->setStyleSheet("background: rgb(225, 158, 51);");
}

/*************************************************************************
【函数名称】StudentMainWindow::RecvScreen(QImage Img)
【函数功能】//收到屏幕共享消息信号
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::RecvScreen(QImage Img) {
    //收到的图像尺寸和滚动区尺寸不一致，则调整滚动区尺寸
    if (ui->scrollAreaWidgetContents->minimumSize() != Img.size()) {
        ui->scrollAreaWidgetContents->setMinimumSize(Img.size());
    }
    //收到的图像尺寸和Label尺寸不一致，则调整Label尺寸
    if (ui->lblSharedScreen->minimumSize() != Img.size()) {
        ui->lblSharedScreen->setMinimumSize(Img.size());
    }
    //刷新Label显示
    ui->lblSharedScreen->setPixmap(QPixmap::fromImage(Img));
}

/*************************************************************************
【函数名称】StudentMainWindow::RecvProblem(QString MtpChoiceText,
                                    unsigned int TimeLimit,
                                    unsigned int ProblemNum,
                                    bool IsSingleChoice)
【函数功能】收到问题，显示问题窗口
【参数】问题的各种信息
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::RecvProblem(QString MtpChoiceText,
                                    unsigned int TimeLimit,
                                    unsigned int ProblemNum,
                                    bool IsSingleChoice) {
    m_pAnsWin = new AnswerWindow(ProblemNum,
                                 m_pProc,
                                 MtpChoiceText,
                                 TimeLimit,
                                 IsSingleChoice);
    m_pAnsWin->exec();
    delete m_pAnsWin;
    m_pAnsWin = nullptr;
}

/*************************************************************************
【函数名称】StudentMainWindow::on_btnChat_clicked()
【函数功能】打开聊天窗口
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void StudentMainWindow::on_btnChat_clicked()
{
    m_pChatWin->close();
    ui->btnChat->setStyleSheet("");
    m_pChatWin->show();
}
