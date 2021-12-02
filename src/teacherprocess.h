/*************************************************************************
【文件名】teacherprocess.h
【功能模块和目的】教师业务流程类声明
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-12
【版权信息】开发者范静涛(fanjingtao@tsinghua.edu.cn)声明放弃任何版权诉求，任何使用者可做出任何修改、用于任何目的
【更改记录】
    2020-05-19 由范静涛修改为从QObject继承，并添加了使用信号更新界面的机制
*************************************************************************/
#ifndef TEACHERPROCESS_H
#define TEACHERPROCESS_H

#include <QObject>
#include "Server.h"
#include "Message.h"
#include "audio.h"
#include <vector>
#include <utility>
#include <QComboBox>
#include <QLineEdit>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QTime>

/*************************************************************************
TeacherProcess
【功能】学生上课业务流程类
【接口说明】
    构造函数TeacherProcess
    析构函数~TeacherProcess
    函数BeginClass上课
    函数EndClass下课
    函数StartScreenShare开始屏幕共享
    函数StopScreenShare停止屏幕共享
    函数StartVoiceShare开始语音直播
    函数StopVoiceShare停止语音直播
    函数SendStrChat群发文本信息
    函数bool& IsInClass;
    函数bool& IsScreenSharing;
    函数bool& IsVoiceSharing;
    信号
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-12
【更改记录】
    2020-05-19 由范静涛修改为从QObject继承，并添加了使用信号更新界面的机制
*************************************************************************/
class TeacherProcess : public QObject{
    Q_OBJECT
public:
    //构造函数
    explicit TeacherProcess(QObject* Parent = nullptr);

    //析构函数
    ~TeacherProcess();

    //禁用拷贝构造函数
    TeacherProcess(const TeacherProcess&) = delete;

    //禁用赋值运算符
    TeacherProcess& operator=(const TeacherProcess&) = delete;

    //上课
    bool BeginClass();

    //下课
    bool EndClass();

    //开始屏幕共享
    bool StartScreenShare();

    //停止屏幕共享
    bool StopScreenShare();

    //开始语音直播
    bool StartVoiceShare();

    //停止语音直播
    bool StopVoiceShare();

    //群发文字
    bool SendStrChat(const QString& ChatStr);

    //给一个学生发送消息
    bool SendStrChatTo(unsigned int idx, const QString& ChatStr);

    //将学生的聊天发送给全体，重载。
    bool SendStrChat(const QString& ChatStr, unsigned int StudentNumber);

    //新建题目
    bool AddNewMtpChoice();

    //编辑题目。可以反复动态覆盖之前的内容。
    string EditMtpChoice(const QString& Text,
                         const QString& Choice1, const QString& Choice2,
                         const QString& Choice3, const QString& Choice4,
                         bool C1, bool C2, bool C3, bool C4, unsigned int TimeLim);

    //发送当前的题目
    bool SendMtpChoice();

    //接收学生传来的答案，返回固定格式的作答信息，并将做大情况储存在MultipleChoice类的成员中。
    string ReceiveAnswer(unsigned int MtpChoiceNumber, unsigned int ConnectionIdx, bool C1, bool C2, bool C3, bool C4, unsigned int Time);

    //停止学生作答，并强制交卷。
    bool StopAnswering();

    //输入下标，返回学生姓名
    string GetStudentName(unsigned int Idx);

    //输入connection编号，返回学生姓名
    string GetStudentNameByConnection(unsigned int ConnectionIdx);

    //输入下标，返回connection编号
    unsigned int GetConnectionIdx(unsigned int Idx);

    //发出课堂即将结束的信号
    bool SendEndingSignal();

    //随机生成下标
    unsigned int GetRdmConnectionIdx();

    //获得当前学生数量
    unsigned int GetStudentCount();

    //把相应信息储存到文件
    void SaveToFile(const string& FileName, const string& Data);

    //在不在上课
    const bool& IsInClass;

    //在不在共享屏幕
    const bool& IsScreenSharing;

    //在不在语音直播
    const bool& IsVoiceSharing;

signals:
    //开始上课
    void ClassBegined();

    //下课了
    void ClassEnded();

    //
    void RecvBeginClass();

    //收到学生登陆信息
    void RecvStudentLogin(QString Name);

    //收到学生下线信息
    void RecvStudentLogout(QString Name, unsigned int Attention);

    //收到学生聊天
    void RecvChat(QString Msg);

    //收到题目作答
    void RecvAnswer(QString Ans);

private:

    //上线一个学生
    bool OnlineStudent(const pair<unsigned int, Message>& Pair);

    //下线一个学生
    void OffLineStudent(unsigned int Idx, unsigned int Attention);

    //在不在上课
    bool m_bIsInClass;

    //服务端
    Server* m_pServer;

    //音频播放对象
    Audio* m_pVoiceCapture;

    //屏幕共享线程函数
    static DWORD WINAPI ScreenShareThread(LPVOID lpParameter);

    //屏幕共享线程句柄
    HANDLE m_hScreeShareThread;

    //是否正在屏幕共享
    bool m_bIsScreenSharing;

    //语音直播线程函数
    static DWORD WINAPI VoiceShareThread(LPVOID lpParameter);

    //语音直播线程句柄
    HANDLE m_hVoiceShareThread;

    //是否正在语音直播
    bool m_bIsVoiceSharing;

    //对收到的消息进行执行的线程函数
    static DWORD WINAPI MsgReceiveThread(LPVOID lpParameter);

    //对收到的消息进行执行的线程句柄
    HANDLE m_hMsgReceiveThread;

    //保存用户名的数组*
    vector<string> m_Names;

    //保存密码的数组*
    vector<string> m_Passwords;

    //保存连接号的数组*
    vector<unsigned int> m_ConnectionIdx;
    //*标注星号，表示同一个学生的用户名、密码、连接号在三个数组中下标一致

    //总共发送了题目的数量
    unsigned int m_uMtpChoiceCount;
};

#endif // TEACHERPROCESS_H
