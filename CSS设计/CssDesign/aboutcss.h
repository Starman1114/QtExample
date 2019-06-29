#ifndef ABOUTCSS_H
#define ABOUTCSS_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QTextBrowser>
#include <QDebug>
namespace Ui {
class AboutCss;
}

class AboutCss : public QDialog
{
    Q_OBJECT

public:
    explicit AboutCss(QWidget *parent = 0);
    ~AboutCss();

private slots:
    void on_pushButton_clicked();

private:
    void ReadTxt(QString FireName);
    void ChangeBox(QTextStream *in);

private:
    Ui::AboutCss *ui;
};

#endif // ABOUTCSS_H
