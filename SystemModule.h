#ifndef SYSTEMMODULE_H
#define SYSTEMMODULE_H

#include <QMainWindow>
#include <vector>
using namespace std;

struct STUDENT
{
    STUDENT() {}
    QString name;
    QString ID;
    QString _class;
};

struct STAFF
{
    STAFF() {}
    QString name;
    QString id;
};

struct SCORE
{
    SCORE() {}
    QString stuname;
    QString modname;
    QString stfname;
    QString score;
};

struct MODULE
{
    MODULE() {}
    QString modname;
    QString stfname;
    QString n1;
    QString n2;
    QString n3;
};

template <typename T>
struct LinkNode
{
    LinkNode()
    {
        p = NULL;
    }
    T value;
    LinkNode<T>* p;
};

class SystemModule : public QMainWindow
{
    Q_OBJECT
public:
    explicit SystemModule(QWidget *parent = nullptr);
private slots:
    void slot1a();
    void slot1b();
    void slot2a();
    void slot2b();
    void slot3a();
    void slot3b();
private:
    QString studentpath;
    QString staffpath;
    QString scorepath;
    QString modulepath;
    vector<SCORE> vecscore;
    vector<MODULE> vecmodule;
    LinkNode<STUDENT>* studentnode;
    LinkNode<STAFF>* staffnode;
};

#endif // SYSTEMMODULE_H
