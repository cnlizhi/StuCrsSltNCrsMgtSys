#ifndef TEACHERMODULE_H
#define TEACHERMODULE_H

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>
#include <QStringList>
#include <vector>
using namespace std;

struct StuScore
{
    StuScore() {}
    QString stuname;
    QString modulename;
    double score;
};

class TeacherModule : public QMainWindow
{
    Q_OBJECT
public:
    explicit TeacherModule(QWidget *parent = nullptr);
protected:
    void resizeEvent(QResizeEvent *event);
private slots:
    void slot1();
    void slot2();
    void slot3a();
    void slot3b();
    void slot4();
    void slot5();
private:
    void _resize();
    static bool StuScoreSort(const StuScore &s1, const StuScore &s2)
    {
        return s1.score > s2.score;
    }
    void print(vector<StuScore> VEC);
    void reset(QString path);
    QString studentpath;
    QString staffpath;
    QString scorepath;
    QString modulepath;
    QListView* view;
    QStringListModel* model;
    QStringList strtext;
    QString teachername;
    QString teacherID;
    vector<StuScore> vec;
};

#endif // TEACHERMODULE_H
