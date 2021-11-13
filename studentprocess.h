/*************************************************************************
【文件名】studentprocess.h
【功能模块和目的】学生业务流程类声明
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-12
【版权信息】开发者范静涛(fanjingtao@tsinghua.edu.cn)声明放弃任何版权诉求，任何使用者可做出任何修改、用于任何目的
【更改记录】
    2020-05-19 由范静涛修改为从QObject继承，用信号实现界面更新
*************************************************************************/
#ifndef STUDENTPROCESS_H
#define STUDENTPROCESS_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <QComboBox>
#include <QScrollArea>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <string>
#include "client.h"
#include "Message.h"
#include "audio.h"
#include "user.h"
using namespace std;

/*************************************************************************
【类名】StudentProcess
【功能】学生上课业务流程类
【接口说明】
    构造函数StudentProcess
    析构函数~StudentProcess
    函数EnterClass进入指定IP的课堂
    函数ExitClass退出课堂
    函数Send向教师发送文本消息
    常引用数据成员IsInClass表示是否在上课
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-12
【更改记录】
    2020-05-19 由范静涛修改为从QObject继承，用信号实现界面更新
*************************************************************************/
class StudentProcess : public QObject{
    Q_OBJECT
public:
    //构造函数
    explicit StudentProcess(QObject* Parent = nullptr);

    //析构函数
    ~StudentProcess();

    //禁用拷贝构造函数
    StudentProcess(const StudentProcess&) = delete;

    //禁用赋值运算符
    StudentProcess& operator=(const StudentProcess&) = delete;

    //进入课堂
    bool EnterClass(const QString& IP);

    //退出课堂
    bool ExitClass();

    //发送文本消息给教师或者全体
    bool Send(const QString& Msg, bool IsToAll);

    //发送答案
    bool HandInMtpChoice(unsigned int ProblemNumber, unsigned int Time, bool C1, bool C2, bool C3, bool C4);

    bool SendAttention(double Attention);

    //是否在上课
    const bool& IsInClass;
    const bool& IsTryingToConnect;

signals:
    //进入课堂信号
    void ClassEntered();

    //退出课堂信号
    void ClassExited();

    //收到文字消息信号
    void RecvChat(QString Msg);

    //收到屏幕共享消息信号
    void RecvScreen(QImage Img);

    //收到题目
    void RecvProblem(QString MtpChoiceText, unsigned int TimeLimit, unsigned int ProblemNum, bool IsSingleChoice);

    //停止答题
    void StopAnswering();

    //课程即将结束
    void ClassToEnd();
private:
    //是否在上课
    bool m_bIsInClass;

    //是否正在链接的过程中
    bool m_bIsTryingToConnect;

    //Socket客户端对象指针
    Client* m_pClient;

    //音频播放对象指针
    Audio* m_pVoicePlayer;

    //接收消息并处理消息的线程函数
    static DWORD WINAPI MsgReceiveThread(LPVOID lpParameter);

    //对收到的消息进行执行的线程句柄
    HANDLE m_hMsgReceiveThread;
    Message m_RemoteLoginMsg;
};

#endif // STUDENTPROCESS_H
