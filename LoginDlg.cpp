#include "LoginDlg.h"

LoginDlg::LoginDlg(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("登陆界面");
    Btn1 = new QPushButton("教师模块");
    Btn2 = new QPushButton("学生模块");
    Btn3 = new QPushButton("系统管理模块");
    Btn1->resize(this->width(), 60);
    Btn2->resize(this->width(), 60);
    Btn3->resize(this->width(), 60);
    connect(Btn1, SIGNAL(clicked(bool)), this, SLOT(module1()));
    connect(Btn2, SIGNAL(clicked(bool)), this, SLOT(module2()));
    connect(Btn3, SIGNAL(clicked(bool)), this, SLOT(module3()));
    Layout = new QVBoxLayout(this);
    Layout->addWidget(Btn1);
    Layout->addWidget(Btn2);
    Layout->addWidget(Btn3);
    this->resize(640, 640);
}

LoginDlg::~LoginDlg()
{
}

void LoginDlg::module1()
{
    TeacherModule = new TeacherModule;
    TeacherModule->show();
    this->close();
}

void LoginDlg::module2()
{
    StudentModule = new StudentModule;
    StudentModule->show();
    this->close();
}

void LoginDlg::module3()
{
    SysMgtModule = new SystemModule;
    SysMgtModule->show();
    this->close();
}
