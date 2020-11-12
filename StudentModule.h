#ifndef STUDENTMODULE_H
#define STUDENTMODULE_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <vector>
using namespace std;

struct Module
{
    Module() {}
    QString name;
    QString staff;
    double credit;
    double period;
    bool flag;
};

class StudentModule : public QMainWindow
{
    Q_OBJECT
public:
    explicit StudentModule(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void slot1();
    void slot2();
    void slot3();
private:
    void _resize();
    void reset(QString path);
    QString studentpath;
    QString staffpath;
    QString scorepath;
    QString modulepath;
    QListView* view;
    QStringListModel* model;
    QStringList strtext;
    QString studentname;
    QString studentID;
    QString studentclass;
    vector< pair<Module, double> > veca;
    vector<Module> vecb;
};

#endif // STUDENTMODULE_H
