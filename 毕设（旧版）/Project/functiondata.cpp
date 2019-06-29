#include "functiondata.h"

FunctionData::FunctionData()
{

}

void FunctionData::clear(FunctionD *fun)
{
    fun->f.clear();
    fun->name.clear();
    fun->N=0;
}

void FunctionData::clearf(func *f)
{
    f->variaName.clear();
    f->s.clear();
    f->c.clear();
    f->ymax.clear();
    f->ymin.clear();
    f->units.clear();
    f->n=0;
}

void FunctionData::readData(FunctionD *fun,QTextStream *in)
{
    QString line = in->readLine();
    QStringList data =  line.split(QRegExp("[;]"));
    QString l1 = data[1]; //图表数N
    fun->N=l1.toInt();
    for(int i=0;i<fun->N;i++){
        line = in->readLine();
        data = line.split(QRegExp("[;]"));
        fun->name.append(data[0]);
        QString nn=data[1];
        func ff;
        fun->f.append(ff);
        fun->f[i].n=nn.toInt();
        for(int j=0;j<fun->f[i].n;j++){
            line = in->readLine();
            data = line.split(QRegExp("[;]"));
            fun->f[i].variaName.append(data[0]);
            fun->f[i].s.append(data[1]);
            fun->f[i].ymax.append(data[2]);
            fun->f[i].ymin.append(data[3]);
            fun->f[i].units.append(data[4]);
            fun->f[i].c.append(data[5]);
        }
    }
}


int FunctionData::findColor(QString cc)
{
    QStringList C={"color0","color1","black","white","darkGray","gray",
                      "lightGray","red","green","blue","cyan","magenta",
                      "yellow","darkRed","darkGreen","darkBlue","darkCyan",
                      "darkMagenta","darkYellow","transparent"};
    int a;
    for(int i=0;i<C.length();i++){
        a = QString::compare( cc, C[i] );
        if(a==0)
            return i;
    }
    return -1;
}

QColor FunctionData::returnColor(int index)
{
    switch(index){
    case 0:
        return Qt::color0;
        break;
    case 1:
        return Qt::color1;
        break;
    case 2:
        return Qt::black;
        break;
    case 3:
        return Qt::white;
        break;
    case 4:
        return Qt::darkGray;
        break;
    case 5:
        return Qt::gray;
        break;
    case 6:
        return Qt::lightGray;
        break;
    case 7:
        return Qt::red;
        break;
    case 8:
        return Qt::green;
        break;
    case 9:
        return Qt::blue;
        break;
    case 10:
        return Qt::cyan;
        break;
    case 11:
        return Qt::magenta;
        break;
    case 12:
        return Qt::yellow;
        break;
    case 13:
        return Qt::darkRed;
        break;
    case 14:
        return Qt::darkGreen;
        break;
    case 15:
        return Qt::darkBlue;
        break;
    case 16:
        return Qt::darkCyan;
        break;
    case 17:
        return Qt::darkMagenta;
        break;
    case 18:
        return Qt::darkYellow;
        break;
    case 19:
        return Qt::transparent;
        break;
    }
}

