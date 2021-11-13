/*************************************************************************
【文件名】multiplechoice
【功能模块和目的】题目类。包括了多选题和单选题！其中单选题是多选题的一个特例
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-17 徐赫临增加了时间限制，单选与多选的区别
2020-06-20 徐赫临增加注释
*************************************************************************/
#ifndef MULTIPLECHOICE_H
#define MULTIPLECHOICE_H

#include <string>
#include <vector>

class TeacherProcess;

using namespace std;

/*************************************************************************
【类名】MultipleChoice
【接口说明】槽函数
【功能模块和目的】题目类。包括了多选题和单选题！其中单选题是多选题的一个特例
【开发者及日期】徐赫临 2020-06-13
【版权信息】徐赫临
【更改记录】
2020-06-17 徐赫临增加了时间限制，单选与多选的区别
2020-06-20 徐赫临增加注释
*************************************************************************/
class MultipleChoice
{
public:
    //构造函数
    MultipleChoice();

    //析构函数
    ~MultipleChoice();

    //拷贝构造函数
    MultipleChoice(const MultipleChoice& anUser);

    //复制运算符
    MultipleChoice& operator=(const MultipleChoice& aMtpChoice);

    //新建题目并添加到vector
    static void NewMtpChoice();

    //编辑本题
    void EditMtpChoice(const string& Text0,
                       const string& Choice1,
                       const string& Choice2,
                       const string& Choice3,
                       const string& Choice4,
                       bool m_bC1, bool m_bC2,
                       bool m_bC3, bool m_bC4,
                       unsigned int TimeLim);

    //按照题号-答案列表（选择列表）来收题，这样用static就可以一起收题，并统计到各个题目上去。
    static void ReceiveAnswer(unsigned int ProblemNum, unsigned int StudentNumber, bool m_bC1, bool m_bC2, bool m_bC3, bool m_bC4, unsigned int Time);

    //返回题目的text
    string GetText() const;

    //返回本题题号
    unsigned int GetMtpChoiceNum() const;

    //返回本题时间限制
    unsigned int GetTimeLimit() const;

    //返回本题是不是单选题。
    bool IsSingleChoice() const;

    //返回对应题号的指针
    static MultipleChoice* GetMtpChoice(unsigned int Number);

    //取得对应题号选择对应选项的学生编号
    static void GetAStuNum(unsigned int MtpChoiceNum, vector<unsigned int>& StuNumList, unsigned int& Count);
    static void GetBStuNum(unsigned int MtpChoiceNum, vector<unsigned int>& StuNumList, unsigned int& Count);
    static void GetCStuNum(unsigned int MtpChoiceNum, vector<unsigned int>& StuNumList, unsigned int& Count);
    static void GetDStuNum(unsigned int MtpChoiceNum, vector<unsigned int>& StuNumList, unsigned int& Count);

    //返回每个选项的人数
    static unsigned int GetACount(unsigned int MtpChoiceNum);
    static unsigned int GetBCount(unsigned int MtpChoiceNum);
    static unsigned int GetCCount(unsigned int MtpChoiceNum);
    static unsigned int GetDCount(unsigned int MtpChoiceNum);

    //返回题目正确率
    static double GetCorrectRate(unsigned int MtpChoiceNum);

    //返回当前总共发送的题目数量
    static unsigned int GetTotalMtpChoiceCount();

    //返回对应题号的正确答案数量
    static unsigned int GetCorrectCount(unsigned int MtpChoiceNum);

    //返回对应题号收到总共答案数量
    static unsigned int GetTotalAnswerCount(unsigned int MtpchoiceNum);

private:
    //题目文本
    string m_WholeText;

    //是否单选题
    bool m_bIsSingleChoice;

    //时间限制
    unsigned int m_uTimeLimit;

    //选项答案
    bool m_bC1;
    bool m_bC2;
    bool m_bC3;
    bool m_bC4;

    //本题作答人数
    unsigned int m_uTotalAnswersCount;

    //本题答对人数
    unsigned int m_uCorrectAnswersCount;

    //本题题号
    unsigned int m_uProblemNumber;

    //vector<string> Answers;选各个选项的学生connection index
    vector<unsigned int> m_StundentNum_ChooseA;
    vector<unsigned int> m_StundentNum_ChooseB;
    vector<unsigned int> m_StundentNum_ChooseC;
    vector<unsigned int> m_StundentNum_ChooseD;

    //包含所有题目list指针
    static vector<MultipleChoice*> m_MtpChoiceList;
};

#endif // MULTIPLECHOICE_H
