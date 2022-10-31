#include <QIntValidator>
#include <QIntValidator>
#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->lineEdit_Resistance        ->setValidator( new QIntValidator   (    0, 1000,    this) );
    ui->lineEdit_MinimumCurrent    ->setValidator( new QIntValidator   (    0,  100,    this) );
    ui->lineEdit_MaximumCurrent    ->setValidator( new QIntValidator   (    0,  100,    this) );
    ui->lineEdit_MinimumSensorValue->setValidator( new QDoubleValidator(-1000, 1000, 2, this) );
    ui->lineEdit_MaximumSensorValue->setValidator( new QDoubleValidator(-1000, 1000, 2, this) );


    ui->lineEdit_Resistance        ->setText("120");
    ui->lineEdit_MinimumCurrent    ->setText(  "4");
    ui->lineEdit_MaximumCurrent    ->setText( "20");
    ui->lineEdit_MinimumSensorValue->setText(  "0");
    ui->lineEdit_MaximumSensorValue->setText( "10");
}

MainWindow::~MainWindow()
{
    delete ui;
}


static double sensorCurrentToVoltage(const double I, const double vRef, const double R1, const double R2) {
    return R2*(vRef + I*R1)/(R1 + R2);
}

static double voltageToAdc(const double v) {
    return v*4096.0/3.3;
}

static double adcToSensorInputValue(const double adc) {
    const double magicNumber1 =   8.83;
    const double magicNumber2 = 496.33;
    return (adc - magicNumber1)/magicNumber2;
}

static double sensorCurrentToInputValue(const double I, const double vRef, const double R1, const double R2) {
    const double V     = sensorCurrentToVoltage(I, vRef, R1, R2);
    const double ADC   = voltageToAdc(V);
    const double input = adcToSensorInputValue(ADC);
    return input;
}

void MainWindow::on_pushButton_clicked()
{
    const double R2     = ui->lineEdit_Resistance        ->text().toInt();
    const double I1     = ui->lineEdit_MinimumCurrent    ->text().toInt()/1000.0;
    const double I2     = ui->lineEdit_MaximumCurrent    ->text().toInt()/1000.0;
    const double value1 = ui->lineEdit_MinimumSensorValue->text().toInt();
    const double value2 = ui->lineEdit_MaximumSensorValue->text().toInt();


    const int x1 = value1 * 10.0;
    const int x2 = value2 * 10.0;
    const double R1 = 1000.0;
    const double vRef = 3.3;

    const double input1 = sensorCurrentToInputValue(I1, vRef, R1, R2);
    const double input2 = sensorCurrentToInputValue(I2, vRef, R1, R2);


    const double k =               (input1 - input2)/(value1 - value2);
    const double b = (value1*input2 - value2*input1)/(value1 - value2)*100.0;

    const int Y1 = x1*k + b;
    const int Y2 = x2*k + b;

    QString resultX1(QString::number(x1));
    QString resultX2(QString::number(x2));
    QString resultY1(QString::number(Y1));
    QString resultY2(QString::number(Y2));

    ui->plainTextEdit_Result->setPlainText("Тип: давление\n"
                                           "Тип датчика: 254\n"
                                           "X1: " + resultX1 + '\n' +
                                           "Y1: " + resultY1 + '\n' +
                                           "X2: " + resultX2 + '\n' +
                                           "Y2: " + resultY2 + '\n'
                                           );
}
