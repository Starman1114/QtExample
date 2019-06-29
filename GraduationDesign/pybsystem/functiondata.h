#ifndef FUNCTIONDATA_H
#define FUNCTIONDATA_H
#include <QList>
#include <QLabel>
#include <QDebug>
#include <QDateTime>
#include <qmath.h>
#include <QStringListModel>
#include <QListView>
#include <QTabWidget>
#include <QTextStream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include "datalist.h"


struct ColorIndex
{
    int fn=0;
    int row=0;
    int index=7;
};

class FunctionData :public QWidget
{
public:
    FunctionData();
    void clear(FunctionD *fun); //清除总数据
    void clearf(func *f); //清楚图标数据
    void readData(FunctionD *fun,QTextStream *in); //将数据读取入结构体
    int findColor(QString cc);
    QColor returnColor(int index);
signals:
    void changeType(int type);

};

#endif // FUNCTIONDATA_H
