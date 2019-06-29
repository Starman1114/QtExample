#include "datalist.h"

QString route;

MonitorFlag flag_Monitor=MONITOR_START;
QFile *file_Monitor;
QAudioFormat format_Monitor;
QAudioDeviceInfo info_Monitor;
QAudioInput *input_Monitor;
QAudioOutput *output_Monitor;
QStringList MonitorName;

dataList::dataList()
{

}
