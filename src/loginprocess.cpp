/*************************************************************************
【文件名】loginprocess.cpp
【功能模块和目的】LoginProcess类，登录过程类
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "loginprocess.h"

/*************************************************************************
【函数名称】LoginProcess::LoginProcess()
【函数功能】构造函数
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-5-26
【更改记录】
2020-5-27 增加注释
*************************************************************************/
LoginProcess::LoginProcess()
{
    User::LoadFromFile("UserInformation.txt");
}

/*************************************************************************
【函数名称】LoginProcess::Login
【函数功能】只返回登录结果，但是负责链接等功能不在此处（在user中）
【参数】const QString& UserName, const QString& Password
【返回值】LoginResult
【开发者及日期】徐赫临 2020-5-26
【更改记录】
*************************************************************************/
LoginResult LoginProcess::Login(const QString& UserName, const QString& Password){
    const User* pCurrentUser = User::GetUser(UserName.toStdString(), Password.toStdString());
    if (pCurrentUser == nullptr) {
        return LR_NOUSER;
    }
    if (pCurrentUser->Type == "Admin") {
        return LR_ADMIN;
    }
    else if (pCurrentUser->Type == "Teacher") {
        return LR_TEACHER;
    }
    else {
        return LR_STUDENT;
    }
}

