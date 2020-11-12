#ifndef LOGINDLG_H
#define LOGINDLG_H

#include "TeacherModule.h"
#include "StudentModule.h"
#include "SystemModule.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class LoginDlg : public QWidget
{
    Q_OBJECT
public:
    LoginDlg(QWidget *parent = 0);
    ~LoginDlg();
private slots:
    void module1();
    void module2();
    void module3();
private:
    TeacherModule* TeacherModule;
    StudentModule* StudentModule;
    SystemModule* SysMgtModule;
    QPushButton* Btn1;
    QPushButton* Btn2;
    QPushButton* Btn3;
    QVBoxLayout* Layout;
};

#endif // LOGINDLG_H
