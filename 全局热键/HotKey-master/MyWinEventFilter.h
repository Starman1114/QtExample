#ifndef MYWINEVENTFILTER_H
#define MYWINEVENTFILTER_H


#pragma once
#include <QAbstractNativeEventFilter>
class MyGlobalShortCut;
class MyWinEventFilter : public QAbstractNativeEventFilter
{
public:
    MyWinEventFilter(MyGlobalShortCut *shortcut);
    ~MyWinEventFilter();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *);
private:
    MyGlobalShortCut *m_shortcut;
};

#endif // MYWINEVENTFILTER_H
