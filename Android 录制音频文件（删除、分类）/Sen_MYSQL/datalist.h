#ifndef DATALIST_H
#define DATALIST_H

#include <QString>
#include <QDebug>
#include <QtNetwork>
#include <QtWidgets>


#include <QAudioDeviceInfo>
#include <QAudioFormat>
#include <QAudioInput>
#include <QAudioOutput>

struct WAVFILEHEADER
{
    // RIFF 头
    char RiffName[4];
    unsigned long nRiffLength;

    // 数据类型标识符
    char WavName[4];

    // 格式块中的块头
    char FmtName[4];
    unsigned long nFmtLength;

    // 格式块中的块数据
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 数据块中的块头
    char    DATANAME[4];
    unsigned long   nDataLength;
};

extern QString route;
extern QString serverIP;
extern QString urltext;
extern QString fileType;
extern int count_Number_Origin;  //计时处理
extern QString PreEmotion;
extern QStringList FileName;
class datalist
{
public:
    datalist();

};

#endif // DATALIST_H
