#ifndef CSSDATAWIDGET_H
#define CSSDATAWIDGET_H

#include <QWidget>
#include <QFontDatabase>

#include <QComboBox>
#include <QSpinBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QLayout>
#include <QLineEdit>

#include "datalist.h"

namespace Ui {
class CssDataWidget;
}

class CssDataWidget : public QWidget
{
    Q_OBJECT
    enum WidgetType
    {
        ComboBox,
        SpinBox,
        LineEdit
    };

public:
    explicit CssDataWidget(QWidget *parent = 0,QString path = 0);
    ~CssDataWidget();
    QString GetFontData();//发送数据

private:
    void InitStyle();//界面初始化
    void AddItemWidget(QString name);//添加选项
    void SetProp_Name(QString FireName);//读取文本信息
    void ChangeSet(QTextStream *in);//改变数据
    int getDataIndex(QString name);//得到属性的序号
    QStringList getDataSource(int s);

private slots:
    void DataChange(const QString &);//数据改变

private:
    Ui::CssDataWidget *ui;
    QStringList DataList;//发送的数据报

    QString DataPath;
    QStringList FontProperyC;//属性
    QStringList FontProperyE;//名称
    QStringList FontProperyT;//类型
    QStringList FontProperyS;//数据来源
    QStringList FontProperyOri;//初始值
    QStringList FontProperyU;//单位
};

#endif // CSSDATAWIDGET_H
