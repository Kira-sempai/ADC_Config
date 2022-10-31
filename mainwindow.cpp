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


void MainWindow::on_pushButton_clicked()
{

    QString result(QString::number((ui->lineEdit_Resistance->text().toInt() +
                   ui->lineEdit_MinimumCurrent->text().toInt())));

    ui->plainTextEdit_Result->setPlainText(result);
}
