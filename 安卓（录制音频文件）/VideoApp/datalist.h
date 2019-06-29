#ifndef DATALIST_H
#define DATALIST_H
#include <QAudio>
#include <QMultimedia>
#include <QFile>
#include <QDebug>
#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>
#include <QTimer>
#include <QDateTime>
#include <QFileDialog>
#include <QStringListModel>
#include <QMessageBox>

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QtAndroid>

#include <QBuffer>

#include <QLCDNumber>
#include <QStatusBar>
extern const int monitorTime;

#define SampleRate 44100
#define ChannelCount 1
#define SampleSize 16

extern int time_Length;

extern QString route;

typedef enum{MONITOR_START, MONITOR_FINISH} MonitorFlag;
extern MonitorFlag flag_Monitor;
extern QFile *file_Monitor;
extern QAudioFormat format_Monitor;
extern QAudioDeviceInfo info_Monitor;
extern QAudioInput *input_Monitor;
extern QAudioOutput *output_Monitor;
extern QStringList MonitorName;

extern int test;

class dataList
{
public:
    dataList();
};

#endif // DATALIST_H
