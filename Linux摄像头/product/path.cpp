#include "path.h"
#include "ui_path.h"
#include <QFileDialog>

Path::Path(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Path)
{
    ui->setupUi(this);
  // manager = new QNetworkAccessManager(this);
  // connect(manager, SIGNAL(finished(QNetworkReply*)),
  // this,SLOT(replyFinished(QNetworkReply*)));
  // manager->get(QNetworkRequest(QUrl("http://127.0.0.1:8000/vlp/")));

  _uploadManager = new QNetworkAccessManager(this);
  connect(_uploadManager,SIGNAL(finished(QNetworkReply*)),SLOT(replyFinished(QNetworkReply*)));
  m_buf = NULL;

  //原加载文件转数据
// QFile file("../http/temp.jpg");
// file.open(QIODevice::ReadOnly);
// int file_len = file.size();
// QDataStream in(&file);
// m_buf = new char[file_len];
// in.readRawData( m_buf, file_len);
// file.close();




  //_reply = _uploadManager->get(request);
 // connect(_reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(upLoadError(QNetworkReply::NetworkError)));
//  connect(_reply, SIGNAL(uploadProgress ( qint64 ,qint64 )), this, SLOT( OnUploadProgress(qint64 ,qint64 )));

   // 画布大小为200*200，背景为白色
  // pix = QPixmap(200, 200);
   //pix.fill(Qt::white);
   pix.load("../http/room.jpg");
   qreal width = pix.width();
   qreal height = pix.height();
   pix=pix.scaled(width*0.3,height*0.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);
  // endPoint=QPoint(112,99);
   lastPoint = endPoint;

    send = false;

    timer = new QTimer(this);
   // connect(timer, SIGNAL(timeout()), this, SLOT(httpsend()));



}

Path::~Path()
{
    delete ui;
}


void Path::paintEvent(QPaintEvent *)
{
    QPainter pp(&pix);
    QPen pen(Qt::green, 3, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    //颜色，宽度，线条，画笔端点风格，端点连接时的风格
    pp.setPen(pen);
    // 根据鼠标指针前后两个位置绘制直线
    pp.drawLine(lastPoint, endPoint);
    // 让前一个坐标值等于后一个坐标值，
    // 这样就能实现画出连续的线
    lastPoint = endPoint;
    QPainter painter(this);
    painter.drawPixmap(0, 20, pix); //画布位置

}


void Path::replyFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    QString all = codec->toUnicode(reply->readAll());
    ui->textBrowser->setText(all);
    reply->deleteLater();

    //坐标提取
    QStringList port=all.split(" ");
    x=port[0].toDouble();
    y=port[1].toDouble();
    ui->x->setValue(x);
    ui->y->setValue(y);
    endPoint=QPoint(x,y);
    update();
}


void Path::on_x_valueChanged(int arg1)
{
    x=arg1;
    endPoint=QPoint(arg1,y);
    update();
}

void Path::on_y_valueChanged(int arg1)
{
    y=arg1;
    endPoint=QPoint(x,arg1);
    update();
}




void Path::on_send_clicked()
{
    //用image转数据

    QImage* bb=new QImage("../build-v4l21-Desktop-Debug/temp.jpg");
    QImage* image=new QImage;
    *image=bb->scaled(2448, 3264, Qt::IgnoreAspectRatio);

    ui->spinBox->setValue(image->width());
    ui->spinBox_2->setValue(image->height());

    QByteArray arr;
    QBuffer buf(&arr);
    buf.open(QIODevice::WriteOnly);
    image->save(&buf, "JPG");


   // QNetworkRequest request(QUrl("http://127.0.0.1:8000/vlp/"));
    QNetworkRequest request(QUrl("http://192.168.1.183:8000/vlp/"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
   // QByteArray arr = QByteArray(m_buf, file_len);

    QByteArray arr1=arr.toBase64(); //先转成Base64

    QString text;
    text.prepend(arr1);
    QJsonObject json;
    json.insert("img",text);  //数据转成json
    QJsonDocument document;
    document.setObject(json);
    QByteArray arr2 = document.toJson(QJsonDocument::Compact);  //再转成QByteArray


    _reply = _uploadManager->post(request , arr2);
}

void Path::on_clear_clicked()
{
    pix.load("../http/room.jpg");
    //pix.fill(Qt::white);
    qreal width = 0;
    qreal height = 0;
    pix=pix.scaled(width*0.3,height*0.3, Qt::KeepAspectRatio,Qt::SmoothTransformation);

    lastPoint =QPoint(0,0);
    endPoint=QPoint(0,0);
    //lastPoint = endPoint;

    ui->x->setValue(0);
    ui->y->setValue(0);
    ui->textBrowser->setText("");
    ui->spinBox->setValue(0);
    ui->spinBox_2->setValue(0);


}

void Path::xy(int x1, int y1)
{
    x1=x;
    y1=y;

}
