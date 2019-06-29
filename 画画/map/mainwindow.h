#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QComboBox>
#include <QVBoxLayout>
#include <QDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    int getmapX(int x);
    int getmapY(int y);

private slots:
    void on_cleanButton_clicked();

    void on_saveButton_clicked();

    void saveRoute();
    
    void on_pathBox_activated(int index);

private:
    Ui::MainWindow *ui;
    int iwidth;
    int iheight;
    QPixmap *pixMap;
    QPoint lastPoint;
    QPoint endPoint;
    QPainterPath *path; //路径
    QList<QPainterPath> PathList;
    QStringList Pathname;
    QList<QPoint> PathEnd;
    QDialog *saveW; //保存框
    QLineEdit *saveName;


};

#endif // MAINWINDOW_H
