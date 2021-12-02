/*************************************************************************
【文件名】loginprocess.h
【功能模块和目的】LoginProcess类，登录过程类
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef LOGINPROCESS_H
#define LOGINPROCESS_H
#include <vector>
#include <string>
#include <QString>
#include "user.h"
using namespace std;

enum LoginResult {LR_NOUSER, LR_ADMIN, LR_TEACHER, LR_STUDENT};

/*************************************************************************
【类名】LoginProcess
【功能】登录过程类
【接口说明】Login函数，输入用户名密码，返回登录结果（LoginResult）
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class LoginProcess
{
public:
    //构造函数
    LoginProcess();

    //登录和登录结果
    LoginResult Login(const QString& UserName, const QString& Password);
private:
    //没有数据成员
};

#endif // LOGINPROCESS_H
