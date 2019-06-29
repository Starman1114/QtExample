#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"camera_thread.h"
#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include "form.h"

#include <QtNetwork>
#include <QPushButton>
#include <QDialog>
#include "path.h"
#include "qtserial.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
 public slots:
    void show_picture(const QImage &img);
    void start_thread(void);
    void stop_thread(void);
    void mousePressEvent(QMouseEvent *);
    void on_pic_clicked();


private slots:
    void on_add_clicked();

    void on_subtract_clicked();

    void on_pushButton_3_clicked();

    void on_set_Push_clicked();

    void on_path_Push_clicked();

    void on_car_Push_clicked();

private:
    Ui::MainWindow *ui;
    video_thread *video;
    qreal scale;
    QImage temp;
    QImage aa;
    Form *f;


    bool form_Set;

    Path *p;
    bool path1;

    QtSerial *q;
    bool car;

    qreal width;
    qreal height;

};

#endif // MAINWINDOW_H
