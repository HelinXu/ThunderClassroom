/*************************************************************************
【文件名】user.cpp
【功能模块和目的】用于用户类的定义
【开发者及日期】范静涛(fanjingtao@tsinghua.edu.cn) 2020-5-11
【版权信息】范静涛(fanjingtao@tsinghua.edu.cn)声明放弃任何版权诉求，任何使用者可做出任何修改、用于任何目的
【更改记录】
    2020-05-19 由范静涛增加了注释
    2020-05-19 由范静涛修改了LoadFromFile函数，在为找到账号文件时，会自动创建一个只包含Admin账户的文件
*************************************************************************/
#include "user.h"
#include "admin.h"
#include "teacher.h"
#include "student.h"

unsigned int User::m_uUserCount = 0;
const unsigned int& User::UserCount = User::m_uUserCount;
vector<User*> User::m_UserList;
User* User::m_LoginedUser = nullptr;

/*************************************************************************
【函数名称】User(const string& Name, const string& Password, const string& Type)
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User::User(const string& Name, const string& Password, const string& Type):Type(m_sType){
    m_sName = Name;
    m_sPassword = Password;
    m_sType = Type;
    m_uUserCount++;
}

/*************************************************************************
【函数名称】User(ifstream& inFile)
【函数功能】构造函数，从文件读取
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User::User(ifstream& inFile):Type(m_sType){
    getline(inFile, m_sName);
    getline(inFile, m_sPassword);
    getline(inFile, m_sType);
    m_uUserCount++;
}

/*************************************************************************
【函数名称】~User()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User::~User(){
    m_uUserCount--;
}

/*************************************************************************
【函数名称】User(const User& anUser)
【函数功能】User拷贝构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User::User(const User& anUser):Type(m_sType){
    m_sName = anUser.m_sName;
    m_sPassword = anUser.m_sPassword;
    m_sType = anUser.m_sType;
}

/*************************************************************************
【函数名称】User::operator=(const User& anUser)
【函数功能】赋值运算符
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User& User::operator=(const User& anUser){
    if (this != &anUser) {
        m_sName = anUser.m_sName;
        m_sPassword = anUser.m_sPassword;
        m_sType = anUser.m_sType;
    }
    return *this;
}

/*************************************************************************
【函数名称】User::ToMessage() const
【函数功能】打包用户信息的message
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
Message User::ToMessage() const {
    unsigned int NameLen = m_sName.length();
    unsigned int PasswordLen = m_sPassword.length();
    unsigned char* Buffer = new unsigned char[NameLen + PasswordLen + 2 * sizeof (NameLen)];
    memcpy(Buffer, (char*)&NameLen, sizeof(NameLen));
    memcpy(Buffer + sizeof(NameLen), m_sName.c_str(), NameLen);
    memcpy(Buffer + sizeof(NameLen) + NameLen, (char*)&PasswordLen, sizeof(PasswordLen));
    memcpy(Buffer +  2 * sizeof(NameLen) + NameLen, m_sPassword.c_str(), PasswordLen);
    Message ret(MSG_ID_PSW, Buffer, NameLen + PasswordLen + 2 * sizeof (NameLen));
    delete [] Buffer;
    return ret;
}

/*************************************************************************
【函数名称】User::SaveToFileStream(ofstream& OutFile) const
【函数功能】出存到文件
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
void User::SaveToFileStream(ofstream& OutFile) const {
    OutFile << m_sName << endl;
    OutFile << m_sPassword << endl;
    OutFile << m_sType << endl;
}

/*************************************************************************
【函数名称】User::GetName() const
【函数功能】返回用户姓名
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
string User::GetName() const{
    return m_sName;
}

/*************************************************************************
【函数名称】User::TestPassword(const string& Password) const
【函数功能】测试密码是否正确
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
bool User::TestPassword(const string& Password) const {
    if (Password == m_sPassword) {
        return true;
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】User::AddUser
【函数功能】新建具有一定用户名、密码、用户类型的用户对象，对象的指针保存在基类User的静态对象vector<User*> UserList中
【参数】用户名、密码、用户类型，QString
【返回值】true表示成功，false表示失败
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
bool User::AddUser(const string& Name, const string& Password, const string& Type){
    Admin* p = nullptr;
    p = dynamic_cast<Admin*>(this);
    if (p != nullptr) {
        if (Type == "Admin") {
            for (unsigned int i  = 0; i < m_UserList.size(); i++) {
                if (m_UserList[i]->Type == "Admin") {
                    return false;
                }
            }
            m_UserList.push_back(new Admin());
            return true;
        }
        else if (Type == "Teacher"){
            m_UserList.push_back(new Teacher(Name, Password));
            return true;
        }
        else {
            m_UserList.push_back((User*) new Student(Name, Password));
            return true;
        }
    }
    else {
        return false;
    }
}

/*************************************************************************
【函数名称】User::DelUser
【函数功能】按用户名删除用户对象，对象的指针保存在基类User的静态对象vector<User*> UserList中
【参数】用户名
【返回值】true表示删除成功，false表示删除失败
【开发者及日期】徐赫临 2020-5-27
【更改记录】
2020-5-27 @TODO是否会存在没有释放内存的情况？
*************************************************************************/
bool User::DelUser(const string& Name) {
    //一定要注意，不能把自己管理员删除
    if(Name == "Admin"){
        return false;
    }
    Admin* p = nullptr;
    p = dynamic_cast<Admin*>(this); //动态地把user指针变成admin类型指针
    if (p != nullptr) {
        for (unsigned int i  = 0; i < m_UserList.size(); i++) {
            if (m_UserList[i]->GetName() == Name) {
                m_UserList.erase(m_UserList.begin() + i);
                return true;//question
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】User::ResUser
【函数功能】按用户名、密码重设用户对象的密码，不检查是否与原来密码一致，对象的指针保存在基类User的静态对象vector<User*> UserList中
【参数】用户名
【返回值】true表示成功，false表示失败
【开发者及日期】徐赫临 2020-5-27
【更改记录】
*************************************************************************/
bool User::ResUser(const string& Name, const string& Password){
    //一定要注意，不能把自己管理员更改
    if(Name == "Admin"){
        return false;
    }
    Admin* p = nullptr;
    p = dynamic_cast<Admin*>(this); //动态地把user指针变成admin类型指针
    if (p != nullptr) {
        for (unsigned int i  = 0; i < m_UserList.size(); i++) {
            if (m_UserList[i]->GetName() == Name) {
                m_UserList[i]->m_sPassword = Password;
                return true;//question
            }
        }
    }
    return false;
}

/*************************************************************************
【函数名称】User::LoadFromFile(const string& FileName)
【函数功能】从文件读取用户信息
【参数】文件名
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】//2020-05-19 范静涛增加了未找到文件则自动创建只包含Admin用户的功能
//2020-05-23 范静涛修改了重复调用此函数导致用户数翻倍的问题，感谢李浦豪同学发现此问题
*************************************************************************/
void User::LoadFromFile(const string& FileName) {
    ifstream inFile(FileName.c_str());
    if (inFile.fail()) {
        ofstream OutFile(FileName.c_str(), ios::out | ios::app);
        OutFile << 1 << endl << "Admin" << endl << "Admin" << endl << "Admin" << endl;
        OutFile.close();
    }
    inFile.close();
    inFile.open(FileName.c_str());

    //2020-05-23 新增开始
    for (int i = m_UserList.size() - 1; i >= 0 ; i--) {
        User* pUser = m_UserList[i];
        delete pUser;
    }
    //2020-05-23 新增结束
    m_UserList.clear();
    unsigned int UserCount;
    inFile >> UserCount;
    inFile.get();
    for (unsigned int i  = 0; i < UserCount; i++) {
        string Name;
        string Password;
        string Type;
        getline(inFile, Name);
        getline(inFile, Password);
        getline(inFile, Type);
        if (Type == "Admin"){
            m_UserList.push_back(new Admin());
        }
        else if (Type == "Teacher"){
            m_UserList.push_back(new Teacher(Name, Password));
        }
        else {
            m_UserList.push_back((User*)new Student(Name, Password));
        }
    }
    inFile.close();
}

/*************************************************************************
【函数名称】User::SaveToFile(const string& FileName)
【函数功能】储存到文件
【参数】文件名
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
void User::SaveToFile(const string& FileName){
    ofstream OutFile(FileName.c_str());
    OutFile << m_UserList.size() << endl;
    for (unsigned int i  = 0; i < m_UserList.size(); i++) {
        m_UserList[i]->SaveToFileStream(OutFile);
    }
}

/*************************************************************************
【函数名称】User* User::GetUser(const string& Name, const string& Password)
【函数功能】找到用户的指针
【参数】用户名和密码
【返回值】用户指针
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
const User* User::GetUser(const string& Name, const string& Password) {
    const User* Current = nullptr;
    for (unsigned int i  = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->GetName() == Name && m_UserList[i]->TestPassword(Password)) {
            Current = m_UserList[i];
            m_LoginedUser = m_UserList[i];
            break;
        }
    }
    return Current;

}

/*************************************************************************
【函数名称】User::GetUser(const string& Name)
【函数功能】根据用户名返回用户指针
【参数】用户名
【返回值】用户指针
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
const User* User::GetUser(const string& Name) {
    const User* Current = nullptr;
    for (unsigned int i  = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->GetName() == Name) {
            Current = m_UserList[i];
            break;
        }
    }
    return Current;

}

/*************************************************************************
【函数名称】User::GetLoginedUser()
【函数功能】获得当前登录的用户指针
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
User* User::GetLoginedUser() {
    return m_LoginedUser;
}

/*************************************************************************
【函数名称】User::OfflineAllStudents()
【函数功能】用于教师端，下线所有学生
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
void User::OfflineAllStudents() {
    Student* pStudent;
    for (unsigned int i  = 0; i < m_UserList.size(); i++) {
        if (m_UserList[i]->Type == "Student") {
            pStudent = dynamic_cast<Student*>(m_UserList[i]);
            pStudent->Offline();
        }
    }
}
