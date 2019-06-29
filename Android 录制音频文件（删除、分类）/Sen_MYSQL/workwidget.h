#ifndef WORKWIDGET_H
#define WORKWIDGET_H

#include <QWidget>
#include "datalist.h"
#include "countshow.h"
#include "choosensen.h"
#include "trashdialog.h"

#define SampleRate 44100
#define ChannelCount 1
#define SampleSize 16

namespace Ui {
class WorkWidget;
}

class WorkWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WorkWidget(QWidget *parent = 0);
    ~WorkWidget();

private slots:
    void on_recordButton_clicked();

    void on_fieldWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_trashButton_clicked();

private:
    void InitStyle();
    qint64 addWavHeader(QString catheFileName , QString wavFileName);
    void File_Gain();
    void File_Start();
    void SetIcon(QPushButton* btn, QString c, QString family,int size, int weight);
    void FrenshList();

private:
    Ui::WorkWidget *ui;
    typedef enum{MONITOR_START, MONITOR_FINISH} MonitorFlag;
    MonitorFlag flag_Monitor = MONITOR_START;
    QFile *file_Monitor;
    QAudioFormat format_Monitor;
    QAudioDeviceInfo info_Monitor;
    QAudioInput *input_Monitor;
    QAudioOutput *output_Monitor;
    int height;
    int weight;

};

#endif // WORKWIDGET_H
