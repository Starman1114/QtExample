#include "choosendialog.h"
#include "ui_choosendialog.h"

ChoosenDialog::ChoosenDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChoosenDialog)
{
    ui->setupUi(this);
    InitSetup();


}

ChoosenDialog::~ChoosenDialog()
{
    delete ui;
}

void ChoosenDialog::InitSetup()
{
    // 设置表头
    studentModel = new QStandardItemModel();
    studentModel->setHorizontalHeaderItem(0, new QStandardItem(tr("单元格")));
    studentModel->setHorizontalHeaderItem(1, new QStandardItem(tr("书签")));
    ui->excelTable->setModel(studentModel);

    // 设置表头格式
    // studentModel->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    // 设置表格宽度
    // ui->excelTable->setColumnWidth(0, 100);
    // 隐藏行头
   // ui->excelTable->verticalHeader()->hide();
    // 整行选中
    //ui->excelTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 不可编辑
    //ui->excelTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 添加行
  //  studentModel->setItem(0, 0, new QStandardItem("张三"));
  //  studentModel->setItem(0, 1, new QStandardItem("10023"));
  //  studentModel->setItem(0, 2, new QStandardItem("男"));
  //  studentModel->setItem(0, 3, new QStandardItem("20"));
  //
  //  studentModel->setItem(1, 0, new QStandardItem("李四"));
  //  studentModel->setItem(1, 1, new QStandardItem("10022"));
  //  studentModel->setItem(1, 2, new QStandardItem("男"));
  //  studentModel->setItem(1, 3, new QStandardItem("21"));

    // 居中
  //  studentModel->item(0, 0)->setTextAlignment(Qt::AlignCenter);
    // 颜色
  //  studentModel->item(0, 0)->setForeground(QBrush(QColor(255, 0, 0)));
    // 加粗
 //   studentModel->item(0, 1)->setFont(QFont("Times", 10, QFont::Black));
    // 排序
   // studentModel->sort(3, Qt::DescendingOrder);//降序  按第3列，下标从0开始
  //  studentModel->sort(1, Qt::AscendingOrder);//升序

 //  QStandardItem* itemProject = new QStandardItem(QIcon(QStringLiteral(":/image/excel_Image.jpg")),QStringLiteral("项目"));
 //  studentModel->appendRow(itemProject);
 //  studentModel->setItem(studentModel->indexFromItem(itemProject).row(),1,new QStandardItem(QString("项目信息说明")));
 //  QStandardItem* itemChild = new QStandardItem(QIcon(QStringLiteral(":/image/Cell.png")),QStringLiteral("文件夹1"));
 //  itemProject->appendRow(itemChild);
 //  itemProject->setChild(0/*itemChild->index().row()*/,1,new QStandardItem(QStringLiteral("信息说明")));
}


void ChoosenDialog::on_addButton_clicked()
{

    int row = studentModel->rowCount();
    studentModel->insertRows(row, 1);
    QModelIndex index = studentModel->index(row,0); //图表下标
    studentModel->setData(index, "");

}

void ChoosenDialog::on_deleteButton_clicked()
{
    studentModel->removeRow(ui->excelTable->currentIndex().row());
}

void ChoosenDialog::on_upButton_clicked()
{
    int row = ui->excelTable->currentIndex().row();
    studentModel->insertRow(row-1,studentModel->takeRow(row));
    ui->excelTable->setCurrentIndex(QModelIndex(studentModel->index(row-1,0)));
}

void ChoosenDialog::on_downButton_clicked()
{
    int row = ui->excelTable->currentIndex().row();
    studentModel->insertRow(row+1,studentModel->takeRow(row));
    ui->excelTable->setCurrentIndex(QModelIndex(studentModel->index(row+1,0)));
}

void ChoosenDialog::on_cancelButton_clicked()
{
    reject();
}

void ChoosenDialog::on_okButton_clicked()
{
    Cells.clear();
    Bookmarks.clear();
    int row = studentModel->rowCount();
    for(int i=0;i<row;i++){
        Cells.append(studentModel->data(QModelIndex(studentModel->index(i,0))).toString());
        Bookmarks.append(studentModel->data(QModelIndex(studentModel->index(i,1))).toString());
    }
    accept();
}

void ChoosenDialog::getData(QStringList Cells_Origin,QStringList Bookmarks_Origin){
    studentModel->clear();
    InitSetup();
    int row = Cells_Origin.length();
    for(int i=0;i<row;i++){
      //  studentModel->insertRows(i, 1);
      //  QModelIndex index0 = studentModel->index(row,0);
      //  studentModel->setData(index0, "Cells_Origin[i]");
      //  QModelIndex index1 = studentModel->index(row,1);
      //  studentModel->setData(index1, Bookmarks_Origin[i]);
        studentModel->setItem(i,0,new QStandardItem(Cells_Origin[i]));
        studentModel->setItem(i,1,new QStandardItem(Bookmarks_Origin[i]));
    }
}


