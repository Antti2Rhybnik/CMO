#include "QsForm_Settings.hpp"
#include "ui_QsForm_Settings.h"

#include "QsSettings.hpp"



QsForm_Settings::QsForm_Settings(QWidget* parent) : QDialog(parent), ui(new Ui::QsForm_Settings)
{
    ui->setupUi(this);

    ui->sbxCl->setValue(QsSettings::C);
    ui->sbxSrv->setValue(QsSettings::S);
    ui->sbxQue->setValue(QsSettings::Q);
    ui->sbxLamCl->setValue(QsSettings::lambda_Cl);
    ui->sbxLamSrv->setValue(QsSettings::lambda_Srv);
    ui->sbxMaxQueries->setValue(QsSettings::maxN);


    connect(ui->btApply, SIGNAL(clicked()), this, SIGNAL(settings_changed_signal()));
    connect(ui->btOk, SIGNAL(clicked()), this, SIGNAL(settings_changed_signal()));

}

QsForm_Settings::~QsForm_Settings()
{
    delete ui;
}

void QsForm_Settings::on_btApply_clicked()
{

    QsSettings::C = ui->sbxCl->value();
    QsSettings::S = ui->sbxSrv->value();
    QsSettings::Q = ui->sbxQue->value();
    QsSettings::lambda_Cl = ui->sbxLamCl->value();
    QsSettings::lambda_Srv = ui->sbxLamSrv->value();
    QsSettings::maxN = ui->sbxMaxQueries->value();

}

void QsForm_Settings::on_btCancel_clicked()
{
    this->hide();

    ui->sbxCl->setValue(QsSettings::C);
    ui->sbxSrv->setValue(QsSettings::S);
    ui->sbxQue->setValue(QsSettings::Q);
    ui->sbxLamCl->setValue(QsSettings::lambda_Cl);
    ui->sbxLamSrv->setValue(QsSettings::lambda_Srv);
    ui->sbxMaxQueries->setValue(QsSettings::maxN);


}

void QsForm_Settings::on_btOk_clicked()
{
    this->hide();

    QsSettings::C = ui->sbxCl->value();
    QsSettings::S = ui->sbxSrv->value();
    QsSettings::Q = ui->sbxQue->value();
    QsSettings::lambda_Cl = ui->sbxLamCl->value();
    QsSettings::lambda_Srv = ui->sbxLamSrv->value();
    QsSettings::maxN = ui->sbxMaxQueries->value();


}


