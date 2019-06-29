#include "datalist.h"

QString route;
const int monitorTime = 20;
MonitorFlag flag_Monitor=MONITOR_START;
QFile *file_Monitor;
QAudioFormat format_Monitor;
QAudioDeviceInfo info_Monitor;
QAudioInput *input_Monitor;
QAudioOutput *output_Monitor;
QStringList MonitorName;

int test=1; //0则执行测试，在PC上测试

int time_Length = 5; //5s

dataList::dataList()
{

}
