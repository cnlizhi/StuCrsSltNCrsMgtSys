#include "TeacherModule.h"
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <algorithm>
#include <QCoreApplication>

TeacherModule::TeacherModule(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Teacher's Module");
    QMenuBar* menubar = new QMenuBar(this);
    QAction* actiona = new QAction(tr("成绩录入"), this);
    QAction* actionb = new QAction(tr("成绩修改"), this);
    QAction* actionca = new QAction(tr("学生姓名查找"), this);
    QAction* actioncb = new QAction(tr("根据分数段查找"), this);
    QAction* actiond = new QAction(tr("统计分析"), this);
    QAction* actione = new QAction(tr("排序"), this);
    connect(actiona, SIGNAL(triggered(bool)), this, SLOT(slot1()));
    connect(actionb, SIGNAL(triggered(bool)), this, SLOT(slot2()));
    connect(actionca, SIGNAL(triggered(bool)), this, SLOT(slot3a()));
    connect(actioncb, SIGNAL(triggered(bool)), this, SLOT(slot3b()));
    connect(actiond, SIGNAL(triggered(bool)), this, SLOT(slot4()));
    connect(actione, SIGNAL(triggered(bool)), this, SLOT(slot5()));
    menubar->addAction(actiona);
    menubar->addAction(actionb);
    menubar->addAction(actionca);
    menubar->addAction(actioncb);
    menubar->addAction(actiond);
    menubar->addAction(actione);
    this->setMenuBar(menubar);
    this->resize(500, 500);
    model = new QStringListModel(this);
    model->setStringList(strtext);
    view = new QListView(this);
    view->setModel(model);
    _resize();
    QString originalpath = qApp->applicationDirPath();
    studentpath = originalpath + tr("\\student.txt");
    scorepath = originalpath + tr("\\score.txt");
    staffpath = originalpath + tr("\\staff.txt");
    modulepath = originalpath + tr("\\module.txt");
    teachername = QInputDialog::getText(this, tr("输入界面"), tr("输入老师姓名"));
    QFile stafffile(staffpath);
    stafffile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream1(&stafffile);
    while (!textstream1.atEnd())
    {
        QStringList list = textstream1.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        if (str == teachername)
        {
            iter++;
            str = *iter;
            teacherID = str;
        }
    }
    stafffile.close();
    QFile scorefile(scorepath);
    scorefile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream2(&scorefile);
    while (!textstream2.atEnd())
    {
        QStringList list = textstream2.readLine().split(' ');
        QStringList::iterator iter1 = list.begin();
        iter1++;
        iter1++;
        QString str = *iter1;
        if (str == teachername)
        {
            StuScore newstuscore;
            QStringList::iterator iter2 = list.begin();
            str = *iter2;
            newstuscore.stuname = str;
            iter2++;
            str = *iter2;
            newstuscore.modulename = str;
            *iter1++;
            str = *iter1;
            newstuscore.score = str.toDouble();
            vec.push_back(newstuscore);
        }
    }
    scorefile.close();
    print(vec);
}

void TeacherModule::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    _resize();
}

void TeacherModule::slot1()
{
    /* 成绩的录入
     * 要求从文件读取 */
    QString filepath = QFileDialog::getOpenFileName(this, tr("请选择文件"), "D:", tr("文本文件(* txt)"));
    QFile file(filepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream(&file);
    while (!textstream.atEnd())
    {
        QStringList list = textstream.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        StuScore newstuscore;
        newstuscore.stuname = str;
        iter++;
        str = *iter;
        newstuscore.modulename = str;
        iter++;
        str = *iter;
        newstuscore.score = str.toDouble();
        vec.push_back(newstuscore);
    }
    file.close();
    print(vec);
    reset(scorepath);
}

void TeacherModule::slot2()
{
    /* 成绩修改
     * 若输入错误可进行修改
     * 要求可以先查找，再修改 */
    QString stuname = QInputDialog::getText(this, tr("输入界面"), tr("输入学生姓名"));
    QString crsname = QInputDialog::getText(this, tr("输入界面"), tr("输入课程名"));
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        if (stuname == mystuscore.stuname && crsname == mystuscore.modulename)
        {
            QString newscore = QInputDialog::getText(this, tr("输入界面"), tr("输入更改后的课程分数"));
            mystuscore.score = newscore.toDouble();
            *iter = mystuscore;
        }
    }
    print(vec);
    reset(scorepath);
}

void TeacherModule::slot3a()
{
    /* 查找
     * 可以根据姓名（或学号）查找某个学生的课程成绩，
     * 查找某门课程成绩处于指定分数段内的学生名单等等
     * 根据姓名查找 */
    QString stuname = QInputDialog::getText(this, tr("输入界面"), tr("输入学生姓名"));
    vector<StuScore> VEC;
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        if (stuname == mystuscore.stuname)
        {
            VEC.push_back(mystuscore);
        }
    }
    print(VEC);
}

void TeacherModule::slot3b()
{
    /* 查找
     * 可以根据姓名（或学号）查找某个学生的课程成绩，
     * 查找某门课程成绩处于指定分数段内的学生名单等等
     * 查找某门课程成绩处于指定分数段内的学生名单 */
    QString crsname = QInputDialog::getText(this, tr("输入界面"), tr("输入课程名"));
    double min = QInputDialog::getDouble(this, tr("输入界面"), tr("最小值"));
    double max = QInputDialog::getDouble(this, tr("输入界面"), tr("最大值"));
    vector<StuScore> VEC;
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        if (crsname == mystuscore.modulename && min <= mystuscore.score && max >= mystuscore.score)
        {
            VEC.push_back(mystuscore);
        }
    }
    print(VEC);
}

void TeacherModule::slot4()
{
    /* 统计分析
     * 对某个班级学生或所有选课的学生的单科成绩进行统计，
     * 求出平均成绩，标准差和及格率 */
    unsigned count = 0;
    double sum = 0;
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        if (mystuscore.score != -1)
        {
            sum += mystuscore.score;
            count++;
        }
    }
    double average = sum / static_cast<double>(count);
    sum = 0;
    unsigned count2 = 0;
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        sum += pow(mystuscore.score - average, 2);
        if (mystuscore.score >= 60)
        {
            count2++;
        }
    }
    double std = sqrt(sum / static_cast<double>(count));
    double rate = static_cast<double>(count2) / static_cast<double>(count);
    QString str = "平均值：" + QString::number(average) + "\n"
            + "标准差：" + QString::number(std) + "\n"
            + "及格率：" + QString::number(rate) + "\n"; 
    QMessageBox::information(this, tr("统计信息"), str);
}

void TeacherModule::slot5()
{
    /* 排序功能
     * 对某个班级学生或所有选课的学生的单科成绩由高到低进行排序 */
    sort(vec.begin(), vec.end(), StuScoreSort);
    print(vec);
}

void TeacherModule::_resize()
{
    model->setStringList(strtext);
    view->setModel(model);
    view->resize(this->width(), this->height() - 50);
    view->move(0, 50);
    view->show();
}

void TeacherModule::print(vector<StuScore> VEC)
{
    strtext.clear();
    QString str;
    for (vector<StuScore>::iterator iter = VEC.begin(); iter != VEC.end(); iter++)
    {
        StuScore mystuscore = *iter;
        str += "姓名：" + mystuscore.stuname + " ";
        str += "课程名：" + mystuscore.modulename + " ";
        if (mystuscore.score != -1)
        {
            str += "分数：" + QString::number(mystuscore.score);
        }
        else
        {
            str += "未给分";
        }
        strtext << str;
        str.clear();
    }
}

void TeacherModule::reset(QString path)
{
    vector<StuScore> VEC;
    QFile file1(path);
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream1(&file1);
    while (!textstream1.atEnd())
    {
        QStringList list = textstream1.readLine().split(' ');
        QStringList::iterator iter1 = list.begin();
        iter1++;
        iter1++;
        QString str = *iter1;
        if (str != teachername)
        {
            StuScore newstuscore;
            QStringList::iterator iter2 = list.begin();
            str = *iter2;
            newstuscore.stuname = str;
            iter2++;
            str = *iter2;
            newstuscore.modulename = str;
            *iter1++;
            str = *iter1;
            newstuscore.score = str.toDouble();
            VEC.push_back(newstuscore);
        }
    }
    file1.close();
    QFile file2(path);
    file2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream2(&file2);
    for (vector<StuScore>::iterator iter = VEC.begin(); iter != VEC.end(); iter++)
    {
        StuScore mystuscore = *iter;
        textstream2 << mystuscore.stuname << " " << mystuscore.modulename << " " << teachername << " " << QString::number(mystuscore.score) << "\n";
    }
    for (vector<StuScore>::iterator iter = vec.begin(); iter != vec.end(); iter++)
    {
        StuScore mystuscore = *iter;
        textstream2 << mystuscore.stuname << " " << mystuscore.modulename << " " << teachername << " " << QString::number(mystuscore.score) << "\n";
    }
    file2.close();
}
