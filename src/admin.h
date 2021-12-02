/*************************************************************************
【文件名】admin.h
【功能模块和目的】Admin管理员类声明
【开发者及日期】徐赫临 2020-5-27
【版权信息】原文件参考：范静涛(fanjingtao@tsinghua.edu.cn)声明放弃任何版权诉求，任何使用者可做出任何修改、用于任何目的
【更改记录】
2020-5-27 徐赫临增加注释
*************************************************************************/
#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"

/*************************************************************************
【类名】Admin
【功能】管理员类
【接口说明】AddUser用于新增一个用户对象，具体功能见相应函数定义处的注释
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 徐赫临增加AddUser,DelUser,ResUser
*************************************************************************/
class Admin : public User
{
public:
    //新增用户
    bool AddUser(const string &Name, const string &Password, const string &Type) override;

    //删除用户
    bool DelUser(const string &Name) override;

    //更改密码
    bool ResUser(const string &Name, const string &Password) override;
private:
    //友元
    friend class User;

    //私有构造函数，不允许在类外显性创建Admin对象。
    //Admin只有在最初loadfromfile的时候创建了一个，
    //之后如果要用里面的函数，只能用这个最初的对象来访问，而不再新创建另外的Admin对象
    //通过uesr指针（指针类型转换）来访问这个对象。
    Admin();
};

#endif // ADMIN_H
