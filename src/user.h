/*************************************************************************
【文件名】user.h
【功能模块和目的】用于用户类的声明
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-11
【版权信息】范静涛(fanjingtao@tsinghua.edu.cn)声明放弃任何版权诉求，任何使用者可做出任何修改、用于任何目的
【更改记录】
    2020-05-19 由范静涛增加了注释
    2020-05-19 由范静涛修改了LoadFromFile函数，在为找到账号文件时，会自动创建一个只包含Admin账户的文件
*************************************************************************/

#ifndef USER_H
#define USER_H

#include <string>
#include <fstream>
#include <vector>
#include "Message.h"
using namespace std;

/*************************************************************************
【类名】User
【功能】用于操作用户
【接口说明】
    析构函数~User();
    拷贝构造函数User(const User& anUser);
    赋值运算符User& operator=(const User& anUser);
    函数GetName返回用名;
    函数ToMessage将用户信息打包为一个消息
    函数TestPassword用于测试给定密码是否为用户密码
    静态函数LoadFromFile从文件读入一批用户
    静态函数SaveToFile将全部用户信息存入文件
    静态函数GetUser(const string& Name, const string& Password)按用户名密码搜索用户
    静态函数GetUser(const string& Name)按用户名搜索用户
    静态函数GetLoginedUser获得最后一次登录的用户指针
    静态函数OfflineAllStudents使得所有学生用户对象离线
    静态常引用UserCount表示用户总个数
    常引用Type表示用户类型字串
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-3
【更改记录】
*************************************************************************/
class User {
public:
    //虚析构函数~User();//2020-05-23 修改为虚析构函数
    virtual ~User();//2020-05-23 修改为虚析构函数
    //拷贝构造函数User(const User& anUser);
    User(const User& anUser);
    //赋值运算符User& operator=(const User& anUser);
    User& operator=(const User& anUser);
    //函数GetName返回用名;
    string GetName() const;
    //函数ToMessage将用户信息打包为一个消息 //@TODO
    Message ToMessage() const;
    //函数TestPassword用于测试给定密码是否为用户密码
    bool TestPassword(const string& Password) const;
    //静态函数LoadFromFile从文件读入一批用户
    static void LoadFromFile(const string& FileName);
    //静态函数SaveToFile将全部用户信息存入文件
    static void SaveToFile(const string& FileName);
    //静态函数GetUser(const string& Name, const string& Password)按用户名密码搜索用户
    static const User* GetUser(const string& Name, const string& Password);
    //静态函数GetUser(const string& Name)按用户名搜索用户
    static const User* GetUser(const string& Name);
    //静态函数GetLoginedUser获得最后一次登录的用户指针
    static User* GetLoginedUser();
    //静态函数OfflineAllStudents使得所有学生用户对象离线
    static void OfflineAllStudents();
    //静态常引用UserCount表示用户总个数
    static const unsigned int& UserCount;
    //常引用Type表示用户类型字串
    const string& Type;
protected:
    //构造函数
    User(const string& Name, const string& Password, const string& Type);
    //构造函数
    User(ifstream& inFile);
    //添加用户到userlist
    virtual bool AddUser(const string& Name, const string& Password, const string& Type);
    //从userlist删除用户
    virtual bool DelUser(const string& Name);
    //改变userlist中用户密码
    virtual bool ResUser(const string& Name, const string& Password);
private:
    //保存到文件流
    void SaveToFileStream(ofstream& OutFile) const;
    //用户对象总个数
    static unsigned int m_uUserCount;
    //全部用户的指针数组。注意多态在此处的巧妙应用
    static vector<User*> m_UserList;
    //最后一个从登录的用户指针
    static User* m_LoginedUser;
    string m_sName;
    string m_sPassword;
    string m_sType;
};

#endif // USER_H
