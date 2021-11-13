/*************************************************************************
【文件名】multiplechoice
【功能模块和目的】题目类。包括了多选题和单选题！其中单选题是多选题的一个特例
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-17 徐赫临增加了时间限制，单选与多选的区别
2020-06-20 徐赫临增加注释
*************************************************************************/
#include "multiplechoice.h"

vector<MultipleChoice*> MultipleChoice::m_MtpChoiceList;

/*************************************************************************
【函数名称】MultipleChoice::MultipleChoice()
【函数功能】构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
MultipleChoice::MultipleChoice()
{
    m_uProblemNumber = m_MtpChoiceList.size();
    m_uTotalAnswersCount = 0;
    m_uCorrectAnswersCount = 0;
    m_bIsSingleChoice = false;
}

/*************************************************************************
【函数名称】MultipleChoice::~MultipleChoice()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
MultipleChoice::~MultipleChoice() {

}

/*************************************************************************
【函数名称】MultipleChoice::MultipleChoice(const MultipleChoice& a)
【函数功能】拷贝构造函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
MultipleChoice::MultipleChoice(const MultipleChoice& a){
    this->m_bC1 = a.m_bC1;
    this->m_bC2 = a.m_bC2;
    this->m_bC3 = a.m_bC3;
    this->m_bC4 = a.m_bC4;
    this->m_WholeText = a.m_WholeText;
    this->m_uTimeLimit = a.m_uTimeLimit;
    this->m_uTotalAnswersCount = a.m_uTotalAnswersCount;
    this->m_uProblemNumber = a.m_uProblemNumber;
    this->m_StundentNum_ChooseA = a.m_StundentNum_ChooseA;
    this->m_StundentNum_ChooseB = a.m_StundentNum_ChooseB;
    this->m_StundentNum_ChooseC = a.m_StundentNum_ChooseC;
    this->m_StundentNum_ChooseD = a.m_StundentNum_ChooseD;
}

/*************************************************************************
【函数名称】MultipleChoice& MultipleChoice::operator=(const MultipleChoice& a)
【函数功能】赋值运算符
【参数】
【返回值】
【开发者及日期】徐赫临 2020-6-13
【更改记录】
*************************************************************************/
MultipleChoice& MultipleChoice::operator=(const MultipleChoice& a){
    if (this != &a) {
        this->m_bC1 = a.m_bC1;
        this->m_bC2 = a.m_bC2;
        this->m_bC3 = a.m_bC3;
        this->m_bC4 = a.m_bC4;
        this->m_WholeText = a.m_WholeText;
        this->m_uTimeLimit = a.m_uTimeLimit;
        this->m_uTotalAnswersCount = a.m_uTotalAnswersCount;
        this->m_uProblemNumber = a.m_uProblemNumber;
        this->m_StundentNum_ChooseA = a.m_StundentNum_ChooseA;
        this->m_StundentNum_ChooseB = a.m_StundentNum_ChooseB;
        this->m_StundentNum_ChooseC = a.m_StundentNum_ChooseC;
        this->m_StundentNum_ChooseD = a.m_StundentNum_ChooseD;
    }
    return *this;
}

/*************************************************************************
【函数名称】新建题目MultipleChoice::NewMtpChoice()
【函数功能】新建题目并加入vector
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void MultipleChoice::NewMtpChoice() {
    m_MtpChoiceList.push_back(new MultipleChoice());
}

/*************************************************************************
【函数名称】编辑题目MultipleChoice::EditMtpChoice(const string& Text0,
                                   const string& Choice1, const string& Choice2,
                                   const string& Choice3, const string& Choice4,
                                   bool C1, bool C2,
                                   bool C3, bool C4,
                                   unsigned int TimeLim)
【函数功能】编辑题目，给正确答案赋值，并处理题目的文本
【参数】题干，每个选项的文本，正确答案
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
void MultipleChoice::EditMtpChoice(const string& Text0,
                                   const string& Choice1, const string& Choice2,
                                   const string& Choice3, const string& Choice4,
                                   bool C1, bool C2,
                                   bool C3, bool C4,
                                   unsigned int TimeLim) {
    this->m_WholeText = "  " + Text0
            + "\n  A. " + Choice1
            + "\n  B. " + Choice2
            + "\n  C. " + Choice3
            + "\n  D. " + Choice4;
    this->m_bC1 = C1;
    this->m_bC2 = C2;
    this->m_bC3 = C3;
    this->m_bC4 = C4;
    m_uTimeLimit = TimeLim;
    unsigned int ChooseCount = C1 + C2 + C3 + C4;
    if (ChooseCount == 1) {
        m_bIsSingleChoice = true;
    }
    else {
        m_bIsSingleChoice = false;
    }
}

/*************************************************************************
【函数名称】收到答案MultipleChoice::ReceiveAnswer(unsigned int ProblemNum,
                                   unsigned int StudentNumber,
                                   bool C1, bool C2,
                                   bool C3, bool C4,
                                   unsigned int Time)
【函数功能】收到答案，并存入vector对应指针的题目里面
//按照题号-答案列表（选择列表）来收题，这样用static就可以一起收题，并统计到各个题目上去。
【参数】收到的答案题目编号、学生的connectionid（Student Number），四个选项的布尔值，作答用时间（未统计）
【返回值】
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
//按照题号-答案列表（选择列表）来收题，这样用static就可以一起收题，并统计到各个题目上去。
void MultipleChoice::ReceiveAnswer(unsigned int ProblemNum,
                                   unsigned int StudentNumber,
                                   bool C1, bool C2,
                                   bool C3, bool C4,
                                   unsigned int Time) {
    MultipleChoice* pThis = m_MtpChoiceList[ProblemNum];
    if (   pThis->m_bC1 == C1
        && pThis->m_bC2 == C2
        && pThis->m_bC3 == C3
        && pThis->m_bC4 == C4) {
        pThis->m_uCorrectAnswersCount += 1;
    }
    pThis->m_uTotalAnswersCount += 1;
    if (C1) {
        pThis->m_StundentNum_ChooseA.push_back(StudentNumber);
    }
    if (C2) {
        pThis->m_StundentNum_ChooseB.push_back(StudentNumber);
    }
    if (C3) {
        pThis->m_StundentNum_ChooseC.push_back(StudentNumber);
    }
    if (C4) {
        pThis->m_StundentNum_ChooseD.push_back(StudentNumber);
    }
}

/*************************************************************************
【函数名称】获得题目的题干MultipleChoice::GetText() const
【函数功能】返回题目题干
【参数】无
【返回值】string，为整个题目的题干
【开发者及日期】徐赫临 2020-06-14
【更改记录】
*************************************************************************/
string MultipleChoice::GetText() const {
    return m_WholeText;
}

/*************************************************************************
【函数名称】MultipleChoice::GetMtpChoice(unsigned int Number)
【函数功能】获得对应题号的题目指针
【参数】题目的序号
【返回值】对应题目的指针
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//返回对应题号的指针
MultipleChoice* MultipleChoice::GetMtpChoice(unsigned int Number) {
    return m_MtpChoiceList[Number];
}

/*************************************************************************
【函数名称】MultipleChoice::GetAStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
【函数功能】将选择A的同学的编号的vector添加到StuNumList里面，并在count中返回对应选项人数
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//取得对应题号选择对应选项的学生编号
void MultipleChoice::GetAStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
    StuNumList = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseA;
    Count = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseA.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetAStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
【函数功能】将选择A的同学的编号的vector添加到StuNumList里面，并在count中返回对应选项人数
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
void MultipleChoice::GetBStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
    StuNumList = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseB;
    Count = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseB.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetAStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
【函数功能】将选择A的同学的编号的vector添加到StuNumList里面，并在count中返回对应选项人数
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
void MultipleChoice::GetCStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
    StuNumList = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseC;
    Count = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseC.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetAStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
【函数功能】将选择A的同学的编号的vector添加到StuNumList里面，并在count中返回对应选项人数
【参数】无
【返回值】无
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
void MultipleChoice::GetDStuNum(
        unsigned int MtpChoiceNum,
        vector<unsigned int>& StuNumList,
        unsigned int& Count) {
    StuNumList = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseD;
    Count = GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseD.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetACount(unsigned int MtpChoiceNum)
【函数功能】更便捷地返回对应题号的题目选项人数
【参数】题号
【返回值】对应题号的题目选项人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//返回每个选项的人数
unsigned int MultipleChoice::GetACount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseA.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetACount(unsigned int MtpChoiceNum)
【函数功能】更便捷地返回对应题号的题目选项人数
【参数】题号
【返回值】对应题号的题目选项人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetBCount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseB.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetACount(unsigned int MtpChoiceNum)
【函数功能】更便捷地返回对应题号的题目选项人数
【参数】题号
【返回值】对应题号的题目选项人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetCCount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseC.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetACount(unsigned int MtpChoiceNum)
【函数功能】更便捷地返回对应题号的题目选项人数
【参数】题号
【返回值】对应题号的题目选项人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetDCount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_StundentNum_ChooseD.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetCorrectRate(unsigned int MtpChoiceNum)
【函数功能】返回对应题号的正确率
【参数】题号
【返回值】正确率，是小于一的double
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//返回题目正确率
double MultipleChoice::GetCorrectRate(unsigned int MtpChoiceNum) {
    return ((double)GetMtpChoice(MtpChoiceNum)->m_uCorrectAnswersCount
            / (double)GetMtpChoice(MtpChoiceNum)->m_uTotalAnswersCount);
}

/*************************************************************************
【函数名称】MultipleChoice::GetMtpChoiceNum()
【函数功能】返回题号
【参数】无
【返回值】返回该题的题号m_uProblemNumber
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//返回本题题号
unsigned int MultipleChoice::GetMtpChoiceNum() const {
    return m_uProblemNumber;
}

/*************************************************************************
【函数名称】MultipleChoice::GetTotalMtpChoiceCount()
【函数功能】返回现在总共的题目数量
【参数】无
【返回值】返回现在总共的题目数量
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetTotalMtpChoiceCount() {
    return m_MtpChoiceList.size();
}

/*************************************************************************
【函数名称】MultipleChoice::GetCorrectCount(unsigned int MtpChoiceNum)
【函数功能】返回对应题号的题目答对的人数
【参数】题号
【返回值】返回对应题号的题目答对的人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetCorrectCount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_uCorrectAnswersCount;
}

/*************************************************************************
【函数名称】MultipleChoice::GetTotalAnswerCount(unsigned int MtpChoiceNum)
【函数功能】返回对应题号的题目的作答总人数
【参数】题号
【返回值】返回对应题号的题目的作答总人数
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetTotalAnswerCount(unsigned int MtpChoiceNum) {
    return GetMtpChoice(MtpChoiceNum)->m_uTotalAnswersCount;
}

/*************************************************************************
【函数名称】unsigned int MultipleChoice::GetTimeLimit() const
【函数功能】返回本题的时间限制
【参数】
【返回值】返回本题的时间限制
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
unsigned int MultipleChoice::GetTimeLimit() const {
    return m_uTimeLimit;
}

/*************************************************************************
【函数名称】MultipleChoice::IsSingleChoice() const
【函数功能】返回是否单选
【参数】
【返回值】返回是否单选
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-19 徐赫临增加了注释
*************************************************************************/
//返回本题是不是单选题。
bool MultipleChoice::IsSingleChoice() const {
    return m_bIsSingleChoice;
}
