#include "StudentModule.h"
#include <QMenuBar>
#include <QAction>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QLayout>
#include <QLabel>
#include <QMessageBox>
#include <QInputDialog>
#include <QCoreApplication>

StudentModule::StudentModule(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("学生模块");
    QMenuBar* menubar = new QMenuBar(this);
    QAction* actiona = new QAction(tr("选课"), this);
    QAction* actionb = new QAction(tr("退选"), this);
    QAction* actionc = new QAction(tr("查看"), this);
    connect(actiona, SIGNAL(triggered(bool)), this, SLOT(slot1()));
    connect(actionb, SIGNAL(triggered(bool)), this, SLOT(slot2()));
    connect(actionc, SIGNAL(triggered(bool)), this, SLOT(slot3()));
    menubar->addAction(actiona);
    menubar->addAction(actionb);
    menubar->addAction(actionc);
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
    studentname = QInputDialog::getText(this, tr("输入模块"), tr("请输入学生姓名"));
    QFile studentfile(studentpath);
    studentfile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream1(&studentfile);
    while (!textstream1.atEnd())
    {
        QStringList list = textstream1.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        if (str == studentname)
        {
            iter++;
            str = *iter;
            studentID = str;
            iter++;
            str = *iter;
            studentclass = str;
        }
    }
    studentfile.close();
    vector<Module> Modulevec;
    QFile modulefile(modulepath);
    modulefile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream2(&modulefile);
    while (!textstream2.atEnd())
    {
        QStringList list = textstream2.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        Module newmodule;
        newmodule.name = str;
        iter++;
        str = *iter;
        newmodule.staff = str;
        iter++;
        str = *iter;
        newmodule.credit = str.toDouble();
        iter++;
        str = *iter;
        newmodule.period = str.toDouble();
        iter++;
        str = *iter;
        if (str.toInt() == 1)
        {
            newmodule.flag = true;
        }
        else if (str.toInt() == 0)
        {
            newmodule.flag = false;
        }
        Modulevec.push_back(newmodule);
    }
    modulefile.close();
    QFile scorefile(scorepath);
    scorefile.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream3(&scorefile);
    while (!textstream3.atEnd())
    {
        QStringList list = textstream3.readLine().split(' ');
        QStringList::iterator iter1 = list.begin();
        QString str = *iter1;
        if (str == studentname)
        {
            iter1++;
            str = *iter1;
            for (vector<Module>::iterator iter2 = Modulevec.begin(); iter2 != Modulevec.end(); iter2++)
            {
                Module mymodule = *iter2;
                if (mymodule.name == str)
                {
                    iter1++;
                    str = *iter1;
                    if (mymodule.staff == str)
                    {
                        iter1++;
                        str = *iter1;
                        if (str.toDouble() == -1)
                        {
                            vecb.push_back(mymodule);
                        }
                        else
                        {
                            pair<Module, double> PAIR;
                            PAIR.first = mymodule;
                            PAIR.second = str.toDouble();
                            veca.push_back(PAIR);
                        }
                    }
                }
            }

        }
    }
    scorefile.close();
}

void StudentModule::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    _resize();
}

void StudentModule::slot1()
{
    /* 根据当前学分和课程性质选择相应的课程 */
    vector<Module> vec;
    QFile file(modulepath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream(&file);
    while (!textstream.atEnd())
    {
        QStringList list = textstream.readLine().split(' ');
        QStringList::iterator iter1 = list.begin();
        QString str = *iter1;
        bool bFlag = false;
        for (vector< pair<Module, double> >::iterator iter2 = veca.begin(); iter2 != veca.end(); iter2++)
        {
            pair<Module, double> PAIR = *iter2;
            if (str == PAIR.first.name)
            {
                bFlag = true;
            }
        }
        for (vector<Module>::iterator iter3 = vecb.begin(); iter3 != vecb.end(); iter3++)
        {
            Module MODULE = *iter3;
            if (str == MODULE.name)
            {
                bFlag = true;
            }
        }
        if (!bFlag)
        {
            Module newModule;
            newModule.name = str;
            iter1++;
            str = *iter1;
            newModule.staff = str;
            iter1++;
            str = *iter1;
            newModule.credit = str.toDouble();
            iter1++;
            str = *iter1;
            newModule.period = str.toDouble();
            iter1++;
            str = *iter1;
            if (str.toInt() == 1)
            {
                newModule.flag = true;
            }
            else
            {
                newModule.flag = false;
            }
            vec.push_back(newModule);
        }
    }
    file.close();
    strtext.clear();
    QString str;
    for (vector<Module>::iterator iter4 = vec.begin(); iter4 != vec.end(); iter4++)
    {
        Module module = *iter4;
        str += "姓名：" + module.name + " ";
        str += "教师：" + module.staff + " ";
        str += "学时：" + QString::number(module.period) + " ";
        str += "学分：" + QString::number(module.credit) + " ";
        if (module.flag)
        {
            str += "性质：必修";
        }
        else
        {
            str += "性质：选修";
        }
        strtext << str;
        str.clear();
    }
    _resize();
    QString text = QInputDialog::getText(this, tr("输入界面"), tr("输入课程"));
    for (vector<Module>::iterator iter5 = vec.begin(); iter5 != vec.end(); iter5++)
    {
        Module module = *iter5;
        if (text == module.name)
        {
            vecb.push_back(module);
            vec.erase(iter5);
            iter5--;
        }
    }
    strtext.clear();
    str.clear();
    for (vector<Module>::iterator iter6 = vec.begin(); iter6 != vec.end(); iter6++)
    {
        Module module = *iter6;
        str += "姓名：" + module.name + " ";
        str += "教师：" + module.staff + " ";
        str += "学时：" + QString::number(module.period) + " ";
        str += "学分：" + QString::number(module.credit) + " ";
        if (module.flag)
        {
            str += "性质：必修";
        }
        else
        {
            str += "性质：选修";
        }
        strtext << str;
        str.clear();
    }
    reset(scorepath);
    _resize();
}

void StudentModule::slot2()
{
    /* 退选某些课程的学习 */
    strtext.clear();
    QString str;
    for (vector<Module>::iterator iter1 = vecb.begin(); iter1 != vecb.end(); iter1++)
    {
        Module module = *iter1;
        str += "姓名：" + module.name + " ";
        str += "教师：" + module.staff + " ";
        str += "学时：" + QString::number(module.period) + " ";
        str += "学分：" + QString::number(module.credit) + " ";
        if (module.flag)
        {
            str += "性质：必修";
        }
        else
        {
            str += "性质：选修";
        }
        strtext << str;
        str.clear();
    }
    _resize();
    QString text = QInputDialog::getText(this, tr("输入界面"), tr("输入课程"));
    for (vector<Module>::iterator iter2 = vecb.begin(); iter2 != vecb.end(); iter2++)
    {
        Module myscore = *iter2;
        if (myscore.name == text)
        {
            vecb.erase(iter2);
            iter2--;
        }
    }
    strtext.clear();
    str.clear();
    for (vector<Module>::iterator iter1 = vecb.begin(); iter1 != vecb.end(); iter1++)
    {
        Module module = *iter1;
        str += "姓名：" + module.name + " ";
        str += "教师：" + module.staff + " ";
        str += "学时：" + QString::number(module.period) + " ";
        str += "学分：" + QString::number(module.credit) + " ";
        if (module.flag)
        {
            str += "性质：必修";
        }
        else
        {
            str += "性质：选修";
        }
        strtext << str;
        str.clear();
    }
    reset(scorepath);
    _resize();
}

void StudentModule::slot3()
{
    /* 查看所选修课程的成绩和当前选修总学分 */
    strtext.clear();
    QString str;
    for (vector< pair<Module, double> >::iterator iter = veca.begin(); iter != veca.end(); iter++)
    {
        pair<Module, double> PAIR = *iter;
        str += "姓名：" + PAIR.first.name + " ";
        str += "教师：" + PAIR.first.staff + " ";
        str += "学时：" + QString::number(PAIR.first.period) + " ";
        str += "学分：" + QString::number(PAIR.first.credit) + " ";
        str += "成绩：" + QString::number(PAIR.second) + " ";
        if (PAIR.first.flag)
        {
            str += "性质：必修";
        }
        else
        {
            str += "性质：选修";
        }
        strtext << str;
        str.clear();
    }
    double sum = 0;
    for (vector< pair<Module, double> >::iterator iter = veca.begin(); iter != veca.end(); iter++)
    {
        pair<Module, double> PAIR = *iter;
        sum += PAIR.first.credit;
    }
    QMessageBox::information(this, tr("当前选修总学分为"), QString::number(sum));
    _resize();
}

void StudentModule::_resize()
{
    model->setStringList(strtext);
    view->setModel(model);
    view->resize(this->width(), this->height() - 50);
    view->move(0, 50);
    view->show();
}

void StudentModule::reset(QString path)
{
    unsigned count = 0;
    vector<QString> vec1;
    vector<QString> vec2;
    vector<QString> vec3;
    vector<double> vec4;
    QFile file1(path);
    file1.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream textstream1(&file1);
    while (!textstream1.atEnd())
    {
        QStringList list = textstream1.readLine().split(' ');
        QStringList::iterator iter = list.begin();
        QString str = *iter;
        if (str != studentname)
        {
            vec1.push_back(str);
            iter++;
            str = *iter;
            vec2.push_back(str);
            iter++;
            str = *iter;
            vec3.push_back(str);
            iter++;
            str = *iter;
            vec4.push_back(str.toDouble());
            count++;
        }
    }
    file1.close();
    QFile file2(path);
    file2.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);
    QTextStream textstream2(&file2);
    for (int i = 0; i < count; i++)
    {
        vector<QString>::iterator itera = vec1.begin();
        vector<QString>::iterator iterb = vec2.begin();
        vector<QString>::iterator iterc = vec3.begin();
        vector<double>::iterator iterd = vec4.begin();
        QString bufferstr = *itera;
        textstream2 << bufferstr << " ";
        bufferstr = *iterb;
        textstream2 << bufferstr << " ";
        bufferstr = *iterc;
        textstream2 << bufferstr << " ";
        double bufferd = *iterd;
        bufferstr = QString::number(bufferd);
        textstream2 << bufferstr << "\n";
        itera++;
        iterb++;
        iterc++;
        iterd++;
    }
    for (vector< pair<Module, double> >::iterator iter = veca.begin(); iter != veca.end(); iter++)
    {
        pair<Module, double> PAIR = *iter;
        textstream2 << studentname << " " << PAIR.first.name << " " << PAIR.first.staff << " " << QString::number(PAIR.second) << "\n";
    }
    for (vector<Module>::iterator iter = vecb.begin(); iter != vecb.end(); iter++)
    {
        Module MODULE = *iter;
        textstream2 << studentname << " " << MODULE.name << " " << MODULE.staff << " -1\n"; 
    }
    file2.close();
}
