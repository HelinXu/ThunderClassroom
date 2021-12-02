/*************************************************************************
【文件名】ansdatawindow
【功能模块和目的】学生答题情况统计页面
【开发者及日期】徐赫临 2020-06-18
【版权信息】徐赫临
【更改记录】
2020-06-20 徐赫临增加注释
*************************************************************************/
#include "ansdatawindow.h"
#include "ui_ansdatawindow.h"

/*************************************************************************
【函数名称】构造函数AnsDataWindow::AnsDataWindow(TeacherProcess* pProc, QWidget *parent)
【函数功能】在界面上建立表格。
【参数】传入process指针（收到答案的信号）。
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18 还没有解决横轴的显示问题。
*************************************************************************/
AnsDataWindow::AnsDataWindow(TeacherProcess* pProc, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AnsDataWindow)
{
    ui->setupUi(this);
    this->m_pProc = pProc;
    connect(pProc, SIGNAL(RecvAnswer(QString)), this, SLOT(RecvAnswer()));
    QChart *chart = new QChart();
    QBarSet *set1 = new QBarSet("A");
    QBarSet *set2 = new QBarSet("B");
    QBarSet *set3 = new QBarSet("C");
    QBarSet *set4 = new QBarSet("D");
    QBarSet *set5 = new QBarSet("Correct");
    QBarCategoryAxis *axis = new QBarCategoryAxis();
    QStringList categories;

    //依次插入学生作答数据
    unsigned int m_uTotalMCNum = MultipleChoice::GetTotalMtpChoiceCount();
    for(unsigned int i = 0; i < m_uTotalMCNum; i++) {
        *set1 << MultipleChoice::GetACount(i);
        *set2 << MultipleChoice::GetBCount(i);
        *set3 << MultipleChoice::GetBCount(i);
        *set4 << MultipleChoice::GetBCount(i);
        *set5 << MultipleChoice::GetCorrectCount(i);
        categories << QString::fromStdString("Question" + to_string(i));
    }

    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);

    //将作答数据显示出来
    chart->addSeries(series);
    axis->append(categories);
    //创建默认的左侧的坐标轴
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    chart->createDefaultAxes();
    chart->setTitle("AnswerData");
    this->setCentralWidget(new QChartView(chart));
}

/*************************************************************************
【函数名称】AnsDataWindow::~AnsDataWindow()
【函数功能】析构函数
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18
*************************************************************************/
AnsDataWindow::~AnsDataWindow()
{
    delete ui;
}

/*************************************************************************
【函数名称】收到答案槽函数void AnsDataWindow::RecvAnswer()
【函数功能】根据答案在界面上建立更新表格。
【参数】
【返回值】
【开发者及日期】徐赫临 2020-06-18
【更改记录】2020-06-18 还没有解决横轴的显示问题。
*************************************************************************/
void AnsDataWindow::RecvAnswer() {
    QChart *chart = new QChart();
    QBarSet *set1 = new QBarSet("A");
    QBarSet *set2 = new QBarSet("B");
    QBarSet *set3 = new QBarSet("C");
    QBarSet *set4 = new QBarSet("D");
    QBarSet *set5 = new QBarSet("Correct");
    QBarCategoryAxis *axis = new QBarCategoryAxis();

    unsigned int m_uTotalMCNum = MultipleChoice::GetTotalMtpChoiceCount();
    for(unsigned int i = 0; i < m_uTotalMCNum; i++) {
        *set1 << MultipleChoice::GetACount(i);
        *set2 << MultipleChoice::GetBCount(i);
        *set3 << MultipleChoice::GetCCount(i);
        *set4 << MultipleChoice::GetDCount(i);
        *set5 << MultipleChoice::GetCorrectCount(i);
        axis->append(QStringList() << QString::fromStdString("Question" + to_string(i)));
    }


    QBarSeries *series = new QBarSeries();
    series->append(set1);
    series->append(set2);
    series->append(set3);
    series->append(set4);
    series->append(set5);

    chart->addSeries(series);
    chart->setAxisX(axis,series);
    chart->createDefaultAxes();
    chart->setTitle("AnswerData");

    this->setCentralWidget(new QChartView(chart));
}
