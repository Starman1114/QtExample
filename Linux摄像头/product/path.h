#ifndef PATH_H
#define PATH_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QtNetwork>
#include <QPainter>


namespace Ui {
class Path;
}

class Path : public QWidget
{
    Q_OBJECT

public:
    explicit Path(QWidget *parent = 0);
    ~Path();

private:
    Ui::Path *ui;
    QNetworkAccessManager *_uploadManager;
    QNetworkReply *_reply;
    char* m_buf;
    double x;
    double y;

    QPixmap pix;
    QPoint lastPoint;
    QPoint endPoint;

    bool send;

    QTimer *timer;

protected:
    void paintEvent(QPaintEvent *);


private slots:

    void replyFinished(QNetworkReply *);

    void on_x_valueChanged(int arg1);

    void on_y_valueChanged(int arg1);

    void on_send_clicked();

    void on_clear_clicked();

    void xy(int x1,int y1);
};

#endif // PATH_H
