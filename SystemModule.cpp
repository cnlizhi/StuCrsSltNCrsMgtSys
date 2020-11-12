#include "SystemModule.h"
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>
#include <QCoreApplication>

SystemModule::SystemModule(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("系统管理模块");
    QMenuBar* menubar = new QMenuBar(this);
    QAction* actionaa = new QAction(tr("增加学生信息"), this);
    QAction* actionab = new QAction(tr("增加老师信息"), this);
    QAction* actionba = new QAction(tr("删除学生信息"), this);
    QAction* actionbb = new QAction(tr("删除老师信息"), this);
    QAction* actionca = new QAction(tr("增加课程信息"), this);
    QAction* actioncb = new QAction(tr("删除课程信息"), this);
    connect(actionaa, SIGNAL(triggered(bool)), this, SLOT(slot1a()));
    connect(actionab, SIGNAL(triggered(bool)), this, SLOT(slot1b()));
    connect(actionba, SIGNAL(triggered(bool)), this, SLOT(slot2a()));
    connect(actionbb, SIGNAL(triggered(bool)), this, SLOT(slot2b()));
    connect(actionca, SIGNAL(triggered(bool)), this, SLOT(slot3a()));
    connect(actioncb, SIGNAL(triggered(bool)), this, SLOT(slot3b()));
    menubar->addAction(actionaa);
    menubar->addAction(actionab);
    menubar->addAction(actionba);
    menubar->addAction(actionbb);
    menubar->addAction(actionca);
    menubar->addAction(actioncb);
    this->setMenuBar(menubar);
    this->resize(500, 500);
    QString originalpath = qApp->applicationDirPath();
    studentpath = originalpath + tr("\\student.txt");
    scorepath = originalpath + tr("\\score.txt");
    staffpath = originalpath + tr("\\staff.txt");
    modulepath = originalpath + tr("\\module.txt");
    studentnode = new LinkNode<STUDENT>;
    QFile studentfile(studentpath);
    studentfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream1(&studentfile);
    while(!textstream1.atEnd())
    {
        QStringList list = textstream1.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        STUDENT newstudent;
        newstudent.name = str;
        iter++;
        str = *iter;
        newstudent.ID = str;
        iter++;
        str = *iter;
        newstudent._class = str;
        LinkNode<STUDENT>* newnode = new LinkNode<STUDENT>;
        newnode->value = newstudent;
        newnode->p = studentnode->p;
        studentnode->p = newnode;
    }
    studentfile.close();
    staffnode = new LinkNode<STAFF>;
    QFile stafffile(staffpath);
    stafffile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream2(&stafffile);
    while(!textstream2.atEnd())
    {
        QStringList list = textstream2.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        STAFF newstaff;
        newstaff.name = str;
        iter++;
        str = *iter;
        newstaff.id = str;
        LinkNode<STAFF>* newnode = new LinkNode<STAFF>;
        newnode->value = newstaff;
        newnode->p = staffnode->p;
        staffnode->p = newnode;
    }
    stafffile.close();
    QFile scorefile(scorepath);
    scorefile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream3(&scorefile);
    while(!textstream3.atEnd())
    {
        QStringList list = textstream3.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        SCORE newscore;
        newscore.stuname = str;
        iter++;
        str = *iter;
        newscore.modname = str;
        iter++;
        str = *iter;
        newscore.stfname = str;
        iter++;
        str = *iter;
        newscore.score = str;
        vecscore.push_back(newscore);
    }
    scorefile.close();
    QFile modulefile(modulepath);
    modulefile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream4(&modulefile);
    while(!textstream4.atEnd())
    {
        QStringList list = textstream4.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        MODULE newmodule;
        newmodule.modname = str;
        iter++;
        str = *iter;
        newmodule.stfname = str;
        iter++;
        str = *iter;
        newmodule.n1 = str;
        iter++;
        str = *iter;
        newmodule.n2 = str;
        iter++;
        str = *iter;
        newmodule.n3 = str;
        vecmodule.push_back(newmodule);
    }
    modulefile.close();
}

void SystemModule::slot1a()
{
    /* 学生入学或引进新教师时增加学生或老师的功能
     * 学生入学增加学生的功能 */
    QString stuname = QInputDialog::getText(this, tr("输入界面"), tr("输入学生姓名"));
    QString stuid = QInputDialog::getText(this, tr("输入界面"), tr("输入学生学号"));
    QString stuclass = QInputDialog::getText(this, tr("输入界面"), tr("输入班级"));
    STUDENT newstudent;
    newstudent.name = stuname;
    newstudent.ID = stuid;
    newstudent._class = stuclass;
    LinkNode<STUDENT>* newnode = new LinkNode<STUDENT>;
    newnode->value = newstudent;
    newnode->p = studentnode->p;
    studentnode->p = newnode;
    QFile file(studentpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream(&file);
    for (LinkNode<STUDENT>* ptr = studentnode; ptr != NULL; ptr = ptr->p)
    {
        STUDENT mystudent = ptr->value;
        textstream << mystudent.name << " " << mystudent.ID << " " << mystudent._class << "\n";
    }
    file.close();
}

void SystemModule::slot1b()
{
    /* 学生入学或引进新教师时增加学生或老师的功能
     * 引进新教师增加老师的功能 */
    QString stfname = QInputDialog::getText(this, tr("输入界面"), tr("输入老师姓名"));
    QString stfid = QInputDialog::getText(this, tr("输入界面"), tr("输入老师编号"));
    STAFF newstaff;
    newstaff.name = stfname;
    newstaff.id = stfid;
    LinkNode<STAFF>* newnode = new LinkNode<STAFF>;
    newnode->value = newstaff;
    newnode->p = staffnode->p;
    staffnode->p = newnode;
    QFile file(staffpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream(&file);
    for (LinkNode<STAFF>* ptr = staffnode; ptr != NULL; ptr = ptr->p)
    {
        STAFF mystaff = ptr->value;
        textstream << mystaff.name << " " << mystaff.id << "\n";
    }
    file.close();
}

void SystemModule::slot2a()
{
    /* 学生毕业或老师离职时删除学生或老师的功能
     * 学生毕业时删除学生的功能 */
    QString stuname = QInputDialog::getText(this, tr("输入界面"), tr("输入学生姓名"));
    for (LinkNode<STUDENT>* ptr = studentnode; ptr != NULL; ptr = ptr->p)
    {
        if (ptr->value.name == stuname)
        {
            for (LinkNode<STUDENT>* index = studentnode; index->p != NULL; index = index->p)
            {
                if (index->p == ptr)
                {
                    index->p = ptr->p;
                }
            }
        }
    }
    QFile file(studentpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream(&file);
    for (LinkNode<STUDENT>* ptr = studentnode; ptr != NULL; ptr = ptr->p)
    {
        STUDENT mystudent = ptr->value;
        textstream << mystudent.name << " " << mystudent.ID << " " << mystudent._class << "\n";
    }
    file.close();
}

void SystemModule::slot2b()
{
    /* 学生毕业或老师离职时删除学生或老师的功能
     * 老师离职时删除老师的功能 */
    QString stfname = QInputDialog::getText(this, tr("输入界面"), tr("输入老师姓名"));
    for (LinkNode<STAFF>* ptr = staffnode; ptr != NULL; ptr = ptr->p)
    {
        if (ptr->value.name == stfname)
        {
            for (LinkNode<STAFF>* index = staffnode; index->p != NULL; index = index->p)
            {
                if (index->p == ptr)
                {
                    index->p = ptr->p;
                }
            }
        }
    }
    QFile file(staffpath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream(&file);
    for (LinkNode<STAFF>* ptr = staffnode; ptr != NULL; ptr = ptr->p)
    {
        STAFF mystaff = ptr->value;
        textstream << mystaff.name << " " << mystaff.id << "\n";
    }
    file.close();
}

void SystemModule::slot3a()
{
    /* 增加或删除某一门课程信息
     * 增加某一门课程信息 */
    QString name = QInputDialog::getText(this, tr("输入界面"), tr("输入课程名"));
    QString staff = QInputDialog::getText(this, tr("输入界面"), tr("输入任课老师"));
    QString credit = QInputDialog::getText(this, tr("输入界面"), tr("输入课程学时"));
    QString period = QInputDialog::getText(this, tr("输入界面"), tr("输入课程学分"));
    QString flag = QInputDialog::getText(this, tr("输入界面"), tr("输入课程性质（必修为1，选修为0）"));
    MODULE newmodule;
    newmodule.modname = name;
    newmodule.stfname = staff;
    newmodule.n1 = credit;
    newmodule.n2 = period;
    newmodule.n3 = flag;
    vecmodule.push_back(newmodule);
    QFile file(modulepath);
    file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream(&file);
    for (vector<MODULE>::iterator iter = vecmodule.begin(); iter != vecmodule.end(); iter++)
    {
        MODULE mymodule = *iter;
        textstream << mymodule.modname << " " << mymodule.stfname << " " << mymodule.n1 << " " << mymodule.n2 << " " << mymodule.n3 << "\n";
    }
    file.close();
}

void SystemModule::slot3b()
{
    /* 增加或删除某一门课程信息
     * 删除某一门课程信息 */
    QString name = QInputDialog::getText(this, tr("输入界面"), tr("输入课程名"));
    for (vector<MODULE>::iterator iter = vecmodule.begin(); iter != vecmodule.end(); iter++)
    {
        MODULE mymodule = *iter;
        if (mymodule.modname == name)
        {
            vecmodule.erase(iter);
            iter--;
        }
    }
    for (vector<SCORE>::iterator iter = vecscore.begin(); iter != vecscore.end(); iter++)
    {
        SCORE myscore = *iter;
        if (myscore.modname == name)
        {
            vecscore.erase(iter);
            iter--;
        }
    }
    QFile file1(modulepath);
    file1.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream1(&file1);
    for (vector<MODULE>::iterator iter = vecmodule.begin(); iter != vecmodule.end(); iter++)
    {
        MODULE mymodule = *iter;
        textstream1 << mymodule.modname << " " << mymodule.stfname << " " << mymodule.n1 << " " << mymodule.n2 << " " << mymodule.n3 << "\n";
    }
    file1.close();
    QFile file2(scorepath);
    file2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream2(&file1);
    for (vector<SCORE>::iterator iter = vecscore.begin(); iter != vecscore.end(); iter++)
    {
        SCORE myscore = *iter;
        textstream2 << myscore.stuname << " " << myscore.modname << " " << myscore.stfname << " " << myscore.score << "\n";
    }
    file2.close();
}
