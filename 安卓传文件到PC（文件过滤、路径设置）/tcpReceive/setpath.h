#ifndef SETPATH_H
#define SETPATH_H

#include <QDialog>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QStorageInfo>
#include <QPixmap>
#include <QMessageBox>
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


private slots:
    void showFiles();
    void showFiles(QDir dir);  //除初始化后的路径及文件显示
    //显示文件信息列表
    void showFileInfoList(QFileInfoList list);
    void showDir(QListWidgetItem * item); //打开文件夹

    void on_reloadButton_clicked();

    void on_saveButton_clicked();

    void on_closeButton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void SetIcon(QPushButton* btn, QString path);

    void on_newButton_clicked();

    void createDir();

private:
    Ui::SetPath *ui;
    QString temPath;
    QLineEdit *name;
};

#endif // SETPATH_H
