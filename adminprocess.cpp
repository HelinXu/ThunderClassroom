/*************************************************************************
【文件名】adminprocess.cpp
【功能模块和目的】AdminProcess类，管理员过程类，包含增加、删除、更改操作函数。此过程类在多个管理员有关界面都会使用
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#include "adminprocess.h"

/*************************************************************************
【函数名称】AdminProcess::AdminProcess()
【函数功能】构造函数。
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 @TODO 是否需要重新导入txt文件？注释掉了该语句，似乎没有区别。
*************************************************************************/
AdminProcess::AdminProcess()
{
}

/*************************************************************************
【函数名称】AdminProcess::Add
【函数功能】增加用户
【参数】const QString& UserName, const QString& Password, const QString& UserType
【返回值】AdminResult，成功/已有此用户
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 修正了未将list存盘的bug
*************************************************************************/
AdminResult AdminProcess::Add(const QString& UserName, const QString& Password, const QString& UserType) {
    const User* pCurrentUser = User::GetUser(UserName.toStdString());
    if (pCurrentUser == nullptr) {
        ((Admin*)User::GetLoginedUser())->
                AddUser(UserName.toStdString(), Password.toStdString(), UserType.toStdString());
        User::SaveToFile("UserInformation.txt");
        return AR_SUCCEED;
    }
    else {
        return AR_ALREADYEXIST;
    }
}

/*************************************************************************
【函数名称】AdminProcess::Del
【函数功能】删除用户
【参数】const QString& UserName
【返回值】AdminResult，成功/没有此用户
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 修正了未将list存盘的bug
*************************************************************************/
AdminResult AdminProcess::Del(const QString& UserName) {
    const User* pCurrentUser = User::GetUser(UserName.toStdString());
    if (pCurrentUser == nullptr) {
        return AR_NOUSER;
    }
    else {
        ((Admin*)User::GetLoginedUser())->DelUser(UserName.toStdString());
        User::SaveToFile("UserInformation.txt");
        return AR_SUCCEED;
    }
}

/*************************************************************************
【函数名称】AdminProcess::Res
【函数功能】更改用户密码
【参数】const QString& UserName, const QString& Password
【返回值】AdminResult，成功/没有此用户
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 修正了未将list存盘的bug
*************************************************************************/
AdminResult AdminProcess::Res(const QString& UserName, const QString& Password) {
    const User* pCurrentUser = User::GetUser(UserName.toStdString());
    if (pCurrentUser == nullptr) {
        return AR_NOUSER;
    }
    else {
        ((Admin*)User::GetLoginedUser())->ResUser(UserName.toStdString(), Password.toStdString());
        User::SaveToFile("UserInformation.txt");
        return AR_SUCCEED;
    }
}
