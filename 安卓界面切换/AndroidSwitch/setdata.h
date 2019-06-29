#ifndef SETDATA_H
#define SETDATA_H

#include <QWidget>
#include "datalist.h"

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QtAndroid>
namespace Ui {
class SetData;
}

class SetData : public QWidget
{
    Q_OBJECT

public:
    explicit SetData(QWidget *parent = 0);
    ~SetData();

private:
    Ui::SetData *ui;
};

#endif // SETDATA_H
