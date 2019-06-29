#include "workerthread.h"

void WorkerThread::run()
{
        while(1)
        {
            pause.lock();

            if(flag_Monitor == MONITOR_FINISH){



                file_Monitor = new QFile();
                file_Monitor->setFileName(route+"/monitor"+QString::number(count)+".raw");



                bool isOpen = file_Monitor->open(QIODevice::WriteOnly | QIODevice::Truncate);
                if(!isOpen)
                {
                    qDebug() << "打开文件失败";
                    return;
                }
                input_Monitor->start(file_Monitor);
                sleep(monitorTime);

                input_Monitor->stop();
                file_Monitor->close();

                // 将生成的.raw文件转成.wav格式文件;
                MonitorName.append(route+"/monitor"+QString::number(count++));
                addWavHeader(MonitorName.back()+".raw", MonitorName.back()+".wav");


            }
         pause.unlock();
        }
}



// 将生成的.raw文件转成.wav格式文件;
qint64 WorkerThread::addWavHeader(QString catheFileName , QString wavFileName)
{
    // 开始准备WAV的文件头
    // 这里具体的数据代表什么含义请看上一篇文章（Qt之WAV文件解析）中对wav文件头的介绍
    WAVFILEHEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");//要加一个空格以满足4个字节

    WavFileHeader.nFmtLength = 16;  //  表示 FMT 的长度
    WavFileHeader.nAudioFormat = 1; //这个表示 PCM 编码;

    qstrcpy(WavFileHeader.DATANAME, "data");

    WavFileHeader.nBitsPerSample =SampleSize;
    WavFileHeader.nBytesPerSample = ChannelCount*SampleSize/8; // 通道数×每次采样得到的样本数据位值／8
    WavFileHeader.nSampleRate = SampleRate;
    WavFileHeader.nBytesPerSecond = SampleRate*ChannelCount*SampleSize/8; //采样频率 × 音频通道数 × 每次采样得到的样本位数 / 8
    WavFileHeader.nChannleNumber = ChannelCount;

    QFile cacheFile(catheFileName);
    QFile wavFile(wavFileName);

    if (!cacheFile.open(QIODevice::ReadWrite))
    {
        return -1;
    }
    if (!wavFile.open(QIODevice::WriteOnly))
    {
        return -2;
    }

    int nSize = sizeof(WavFileHeader);
    qint64 nFileLen = cacheFile.bytesAvailable();

    WavFileHeader.nRiffLength = nFileLen - 8 + nSize;
    WavFileHeader.nDataLength = nFileLen;

    // 先将wav文件头信息写入，再将音频数据写入;
    wavFile.write((char *)&WavFileHeader, nSize);
    wavFile.write(cacheFile.readAll());

    cacheFile.close();
    wavFile.close();

    return nFileLen;
}
