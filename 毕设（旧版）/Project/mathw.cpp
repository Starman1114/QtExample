#include "mathw.h"
#include "ui_mathw.h"

MathW::MathW(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MathW)
{
    ui->setupUi(this);
    setWindowTitle("公式计算器");
}

MathW::~MathW()
{
    delete ui;
}

void MathW::show_MATH(QStringList fo)  //双击公式时编辑框显示出所双击的公式
{
    formula = fo;
    updataShow();
}



void MathW::on_accX_clicked()
{
    rightShow();
    formula.append(ui->accX->text());
    updataShow();
}

void MathW::on_accY_clicked()
{
    rightShow();
    formula.append(ui->accY->text());
    updataShow();
}

void MathW::on_accZ_clicked()
{
    rightShow();
    formula.append(ui->accZ->text());
    updataShow();
}

void MathW::on_Acc_clicked()
{
    rightShow();
    formula.append(ui->Acc->text());
    updataShow();
}

void MathW::on_gyroX_clicked()
{
    rightShow();
    formula.append(ui->gyroX->text());
    updataShow();
}

void MathW::on_gyroY_clicked()
{
    rightShow();
    formula.append(ui->gyroY->text());
    updataShow();
}

void MathW::on_gyroZ_clicked()
{
    rightShow();
    formula.append(ui->gyroZ->text());
    updataShow();
}

void MathW::on_Gyro_clicked()
{
    rightShow();
    formula.append(ui->Gyro->text());
    updataShow();
}

void MathW::on_magX_clicked()
{
    rightShow();
    formula.append(ui->magX->text());
    updataShow();
}

void MathW::on_magY_clicked()
{
    rightShow();
    formula.append(ui->magY->text());
    updataShow();
}

void MathW::on_magZ_clicked()
{
    rightShow();
    formula.append(ui->magZ->text());
    updataShow();
}

void MathW::on_Mag_clicked()
{
    rightShow();
    formula.append(ui->Mag->text());
    updataShow();
}

void MathW::on_angleX_clicked()
{
    rightShow();
    formula.append(ui->angleX->text());
    updataShow();
}

void MathW::on_angleY_clicked()
{
    rightShow();
    formula.append(ui->angleY->text());
    updataShow();
}

void MathW::on_angleZ_clicked()
{
    rightShow();
    formula.append(ui->angleZ->text());
    updataShow();
}

void MathW::on_Angle_clicked()
{
    rightShow();
    formula.append(ui->Angle->text());
    updataShow();
}

void MathW::on_zero_clicked()
{
    rightShow_Number(ui->zero->text());
    updataShow();
}

void MathW::on_one_clicked()
{
    rightShow_Number(ui->one->text());
    updataShow();
}

void MathW::on_two_clicked()
{
    rightShow_Number(ui->two->text());
    updataShow();
}

void MathW::on_three_clicked()
{
    rightShow_Number(ui->three->text());
    updataShow();
}

void MathW::on_four_clicked()
{
    rightShow_Number(ui->four->text());
    updataShow();
}

void MathW::on_five_clicked()
{
    rightShow_Number(ui->five->text());
    updataShow();
}

void MathW::on_six_clicked()
{
    rightShow_Number(ui->six->text());
    updataShow();
}

void MathW::on_seven_clicked()
{
    rightShow_Number(ui->seven->text());
    updataShow();
}

void MathW::on_eight_clicked()
{
    rightShow_Number(ui->eight->text());
    updataShow();
}

void MathW::on_nine_clicked()
{
    rightShow_Number(ui->nine->text());
    updataShow();
}

void MathW::on_add_clicked()
{
    rightShow_Symbol();
    formula.append(ui->add->text());
    updataShow();
}

void MathW::on_sub_clicked()
{
    rightShow_Symbol();
    formula.append(ui->sub->text());
    updataShow();
}

void MathW::on_mul_clicked()
{
    rightShow_Symbol();
    formula.append(ui->mul->text());
    updataShow();
}

void MathW::on_div_clicked()
{
    rightShow_Symbol();
    formula.append(ui->div->text());
    updataShow();
}

void MathW::on_left_clicked()
{
    rightShow();
    formula.append(ui->left->text());
    updataShow();
}

void MathW::on_right_clicked()
{
    rightShow_Symbol();
    formula.append(ui->right->text());
    updataShow();
}

void MathW::on_copy_clicked()
{
    tem=formula;
}

void MathW::on_paste_clicked()
{
   // formula.append(tem);
    formula.clear();
    formula=tem;
    updataShow();
}

void MathW::on_back_clicked()
{
    formula.pop_back();
    updataShow();
}

void MathW::on_clear_clicked()
{
    formula.clear();
    updataShow();
}

void MathW::on_enter_clicked()
{
   emit resultReady(formula);
   formula.clear();
   ui->textEdit->clear();
   hide();
}

void MathW::updataShow()
{
    QString line;

    for(int i=0;i<formula.length();i++){
        line+=formula[i];
    }
    ui->textEdit->setText(line);
}

void MathW::rightShow()
{
    if(formula.length()>0){
        QString line=formula.back();
        if(findSymbol(line)==-1||findSymbol(line)==-2){
            formula.pop_back();
        }
    }
}

void MathW::rightShow_Symbol()
{
    if(formula.length()>0){
        QString line=formula.back();
        if(findSymbol(line)!=-1&&findSymbol(line)!=-2){
            formula.pop_back();
        }
    }
}

void MathW::rightShow_Number(QString text)
{
    if(formula.length()>0){
        QString line=formula.back();
        if(findSymbol(line)==-2){
            int a = line.toInt()*10+text.toInt();
            formula.pop_back();
            formula.append(QString::number(a));
        }else if(findSymbol(line)==-1){
            formula.pop_back();
            formula.append(text);
        }else{
            formula.append(text);
        }
    }
}

int MathW::findSymbol(QString line){

    int add=QString::compare( line, "+" );
    int sub=QString::compare( line, "-" );
    int mul=QString::compare( line, "*" );
    int div=QString::compare( line, "/" );
    int left=QString::compare( line, "(" );
    int right=QString::compare( line, ")" );
    int n=line.toInt();
  //  int n=num%10;
    if(add==0)
        return 1;
    if(sub==0)
        return 2;
    if(mul==0)
        return 3;
    if(div==0)
        return 4;
    if(left==0)
        return 5;
    if(right==0)
        return -1;
    if(n>=0&&n<=9)
        return -2;
    return -1;
}

int MathW::findP(QString line){

    int accX=QString::compare( line, "accX" );
    int accY=QString::compare( line, "accY" );
    int accZ=QString::compare( line, "accZ" );

    int gyroX=QString::compare( line, "gyroX" );
    int gyroY=QString::compare( line, "gyroY" );
    int gyroZ=QString::compare( line, "gyroZ" );

    int magX=QString::compare( line, "magX" );
    int magY=QString::compare( line, "magY" );
    int magZ=QString::compare( line, "magZ" );

    int angleX=QString::compare( line, "angleX" );
    int angleY=QString::compare( line, "angleY" );
    int angleZ=QString::compare( line, "angleZ" );

    int Acc=QString::compare( line, "Acc" );
    int Gyro=QString::compare( line, "Gyro" );
    int Mag=QString::compare( line, "Mag" );
    int Angle=QString::compare( line, "Angle" );

    if(accX==0)
        return 11;
    if(accY==0)
        return 12;
    if(accZ==0)
        return 13;
    if(Acc==0)
        return 10;
    if(gyroX==0)
        return 21;
    if(gyroY==0)
        return 22;
    if(gyroZ==0)
        return 23;
    if(Gyro==0)
        return 20;
    if(magX==0)
        return 31;
    if(magY==0)
        return 32;
    if(magZ==0)
        return 33;
    if(Mag==0)
        return 30;
    if(angleX==0)
        return 41;
    if(angleY==0)
        return 42;
    if(angleZ==0)
        return 43;
    if(Angle==0)
        return 40;
    return -2;

}

QStringList MathW::mid_to_back(QStringList f)
{
    f.pop_back();//最后一位为空
    QStringList output;
    QStringList stack;
    if(f.length()==3)
          qDebug()<<f[0]<<" "<<f[1]<<" "<<f[2]<<endl;
    for(int i=0;i<f.length();i++){
        if(findSymbol(f[i])==-1||findSymbol(f[i])==-2){
            if(QString::compare( f[i], ")" )==0){
                while(QString::compare( stack.back(), "(" )!=0){
                    output.append(stack.back());
                    stack.pop_back();
                }
                stack.pop_back();
            }else{
                output.append(f[i]);
            }
        }else{

            while(stack.length()>0&&findSymbol(stack.back())>=findSymbol(f[i])){
                output.append(stack.back());
                stack.pop_back();
            }
            stack.append(f[i]);
        }
    }
    while(stack.length()>0){
        output.append(stack.back());
        stack.pop_back();
    }
    return output;
}

float MathW::getResult(QStringList last,float *Acc1, float *Gyro1, float *Mag1, float *Angle1)
{
    if(last.length()==1){
        float v1 =getP(last[0],Acc1,Gyro1,Mag1,Angle1);
        return v1;
    }
    QStringList output;
    for(int i=0;i<last.length();i++){
        if(findSymbol(last[i])==-1||findSymbol(last[i])==-2){
            output.append(last[i]);

        }else{
            QString a2= output.back();
            output.pop_back();
            QString a1= output.back();
            output.pop_back();
            float ss=getValue(a1, a2, last[i],Acc1,Gyro1,Mag1,Angle1);
            output.append(QString("%1").arg((float)ss));
           // output.append(QString("%1").arg((float)getValue(a1, a2, last[i],Acc1,Gyro1,Mag1,Angle1)));

        }
    }
    QString l=output.back();

    return l.toFloat();
}

float MathW::getValue(QString a1, QString a2, QString sym,float *Acc1, float *Gyro1, float *Mag1, float *Angle1)
{
    float v1 =getP(a1,Acc1,Gyro1,Mag1,Angle1);
    float v2 =getP(a2,Acc1,Gyro1,Mag1,Angle1);
    int s=findSymbol(sym);
    switch(s){
    case 1:
        return v1+v2;
        break;
    case 2:
        return v1-v2;
        break;
    case 3:
        return v1*v2;
        break;
    case 4:
        return v1/v2;
        break;
    }
    return 0;
}

float MathW::getP(QString a1,float *Acc1, float *Gyro1, float *Mag1, float *Angle1)
{
    float *abs=returnAbs(Acc1,Gyro1,Mag1,Angle1);
    int a = findP(a1);
    switch(a){
    case 11:
        return Acc1[0];
        break;
    case 12:
        return Acc1[1];
        break;
    case 13:
        return Acc1[2];
        break;
    case 10:
        return abs[0];
        break;
    case 21:
        return Gyro1[0];
        break;
    case 22:
        return Gyro1[1];
        break;
    case 23:
        return Gyro1[2];
        break;
    case 20:
        return abs[1];
        break;
    case 31:
        return Mag1[0];
        break;
    case 32:
        return Mag1[1];
        break;
    case 33:
        return Mag1[2];
        break;
    case 30:
        return abs[2];
        break;
    case 41:
        return Angle1[0];
        break;
    case 42:
        return Angle1[1];
        break;
    case 43:
        return Angle1[2];
        break;
    case 40:
        return abs[3];
        break;
    default:
        return a1.toInt();
        break;
    }
}


float* MathW::returnAbs(float *Acc1,float *Gyro1,float *Mag1,float *Angle1)
{
    float abs[4];
    QList<float> list;
    for(int i = 0 ;i<3;i++){
        list.clear();
        list.append(Acc1[i]);
        list.append(Gyro1[i]);
        list.append(Mag1[i]);
        list.append(Angle1[i]);
        for(int k = 0 ;k<4;k++){
            float l=list[k];
            abs[k] += qPow(l,2);
        }
    }
    float data[4];
    for(int k = 0 ;k<4;k++){
        abs[k] = qSqrt(abs[k]);
        data[k]=abs[k];
    }

    return data;
}
