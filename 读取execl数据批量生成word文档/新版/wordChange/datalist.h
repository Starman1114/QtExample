#ifndef DATALIST_H
#define DATALIST_H

#include <QAxWidget>
#include <QAxObject>
#include <QFileDialog>
#include <QStringListModel>
#include <QDebug>


extern bool allRead;//全选单元格
extern int intRow;//行数
extern int Begin_Row;//起始行
extern int End_Row;//终止行

typedef enum{EXECL_START, WORD_START} STATE;
extern STATE current_STATE;

extern QString execl_Name;
extern QString word_Name;
extern QString new_Route;
extern QString Path;

struct Cells_template
{
    QStringList name;
    QList<bool> state;
};

struct Bookmarks_template
{
    QStringList name;
};

extern Cells_template Cells;
extern Bookmarks_template Bookmarks;

class dataList
{
public:
    dataList();
};

#endif // DATALIST_H
