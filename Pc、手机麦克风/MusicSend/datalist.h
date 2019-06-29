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

#include <QAndroidJniObject>
#include <QAndroidJniEnvironment>
#include <QAndroidActivityResultReceiver>
#include <QDebug>
#include <QtAndroid>


#include <QBuffer>

#define monitorTime 5

#define SampleRate 44100
#define ChannelCount 1
#define SampleSize 8

extern QString route;

typedef enum{MONITOR_START, MONITOR_FINISH} MonitorFlag;
extern MonitorFlag flag_Monitor;
extern QFile *file_Monitor;
extern QAudioFormat format_Monitor;
extern QAudioDeviceInfo info_Monitor;
extern QAudioInput *input_Monitor;
extern QAudioOutput *output_Monitor;
extern QStringList MonitorName;

class dataList
{
public:
    dataList();
};

#endif // DATALIST_H
