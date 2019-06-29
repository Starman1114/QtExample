#ifndef SETPATH_H
#define SETPATH_H

#include <QDialog>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStorageInfo>
#include <QPixmap>
#include <QMessageBox>
#include <QStringListModel>
#include "datalist.h"
namespace Ui {
class SetPath;
}

class SetPath : public QDialog
{
    Q_OBJECT

public:
    explicit SetPath(QWidget *parent = 0);
    ~SetPath();
/**************************************************************************
    * 界面窗口操作
    */
    bool eventFilter(QObject *obj, QEvent *event);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *);
    void InitStyle();

private slots:
    void showFiles();
    void showFiles(QDir dir);  //除初始化后的路径及文件显示
    //显示文件信息列表
    void showFileInfoList(QFileInfoList list);
    void showDir(const QModelIndex &index); //打开文件夹

    void on_reloadButton_clicked();

    void on_saveButton_clicked();

    void on_closeButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_newButton_clicked();

    void createDir();

    void keyReleaseEvent(QKeyEvent  *);
/**************************************************************************
    * 界面窗口操作
    */
    void on_btnMenu_Close_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Min_clicked();

private:
    Ui::SetPath *ui;
    QString temPath;
    QStringListModel *model;
    bool isCreatDir=false;
    QString name;

    QPoint mousePoint;
    bool mousePressed;
    bool max;
    QRect location;
};

#endif // SETPATH_H
