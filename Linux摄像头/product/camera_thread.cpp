#include "camera_thread.h"
#include <QByteArray>
#include <QBuffer>
#include <QImage>
#include <QDebug>

video_thread::video_thread():QThread()
{
    quit_flag = false;
}

video_thread::~video_thread()
{
    this->quit();
    quit_flag = true;
    this->wait();
}

void video_thread::run()
{
    m_video.init_video();//打开视频设备
    while(!quit_flag)
    {
    m_video.get_data();//获取视频数据
    unsigned char *rgb;
    rgb = new unsigned char [m_video.buf.length*2];//根据yuyv像素点和rgb像素所站内存比分配rgb
    m_video.yuvtorgbO(rgb,640,480);//yuyv转换成RGB
    img = QImage(rgb,640,480,QImage::Format_RGB888);
    emit image_data(img);
    msleep(150);
    delete[] rgb;//不能在sleep前释放掉否则显示的图片会出现问题
   }
    m_video.release_video();//在线程释放前释放设备
}

QImage video_thread::getimg()
{
    return img;
}


