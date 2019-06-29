#include "monitor.h"

void Monitor::run()
{
    while(1)
    {
        pause.lock();
        if(flag_Monitor == MONITOR_FINISH){
            if(MonitorName.length()>10){
                QFile::remove(MonitorName.front()+".raw");
                QFile::remove(MonitorName.front()+".wav");
                MonitorName.pop_front();
            }
        }
        pause.unlock();
    }
}
