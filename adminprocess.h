/*************************************************************************
【文件名】adminprocess.h
【功能模块和目的】AdminProcess类，管理员过程类，包含增加、删除、更改操作函数。此过程类在多个管理员有关界面都会使用
【开发者及日期】徐赫临 2020-5-26
【版权信息】开发者徐赫临
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMINPROCESS_H
#define ADMINPROCESS_H
#include <vector>
#include <string>
#include <QString>
#include "user.h"
#include "admin.h"
using namespace std;

enum AdminResult {AR_NOUSER, AR_ALREADYEXIST, AR_SUCCEED};

/*************************************************************************
【类名】AdminProcess
【功能】管理员过程类
【接口说明】Add，Del，Res三种操作
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
class AdminProcess
{
public:
    //构造函数
    AdminProcess();

    //增加用户
    AdminResult Add(const QString& UserName, const QString& Password, const QString& UserType);

    //删除用户
    AdminResult Del(const QString& UserName);

    //重新设置用户密码
    AdminResult Res(const QString& UserName, const QString& Password);
private:
    //不包含数据成员
};

#endif // ADMINPROCESS_H
