#ifndef DATALIST_H
#define DATALIST_H

#include <QAxWidget>
#include <QAxObject>
#include <QFileDialog>
#include <QStringListModel>
#include <QDebug>

extern QStringList Name_Class;
extern QStringList Place;
extern QStringList Pre_Time;
extern QStringList End_Time;
extern QStringList Major;
extern QStringList Minor;
extern int intRow;//行数

typedef enum{EXECL_START, WORD_START} STATE;
extern STATE current_STATE;


class dataList
{
public:
    dataList();
};

#endif // DATALIST_H
