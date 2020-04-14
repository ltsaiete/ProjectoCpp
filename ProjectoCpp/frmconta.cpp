#include "frmconta.h"
#include "ui_frmconta.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

FrmConta::FrmConta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FrmConta)
{
    ui->setupUi(this);

}

FrmConta::~FrmConta()
{
    delete ui;
}

void FrmConta::on_btSalvar_clicked()
{
    ContaEstudante contaEst;
    QString BI = ui->txtBI->text();
    QString numConta = ui->txtNumConta->text();
    QString senha = ui->txtSenha->text();
    QString saldo = ui->txtSaldo->text();

    bool res = existeBI(BI);

    if(res==true){

        contaEst = *new ContaEstudante(BI.toStdString(), numConta.toLong(), senha.toInt(), saldo.toFloat());

        saveToFile(BI, numConta, senha, saldo);

        QMessageBox::information(this, "Dados da Conta", "Titular: " + BI + "\nNumero de Conta: " +
                                 numConta + "\nSenha: " + senha + "\nSaldo: " + saldo);

        on_btLimpar_clicked();

    }else{
        QMessageBox::warning(this, "Dados da Conta", "Estudante nao Encontrado, tente novamente!");
    }
}

void FrmConta::on_btLimpar_clicked()
{
    ui->txtBI->clear();
    ui->txtNumConta->clear();
    ui->txtSenha->clear();
    ui->txtSaldo->clear();

    ui->txtBI->setFocus();
}

void FrmConta::saveToFile(QString BI, QString numConta, QString senha, QString saldo){

    QString local = "D:/Escolaridade/FENG/2_Ano/LP/C++/ProjectoFinal/ProjectoCpp/ProjectoCpp/files/";
    QString arq = "listaConta.txt";
    QFile file(local + arq);

    if(!file.open(QFile::Append|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "Erro ao abrir arquivo");
    }else{
        QTextStream saida(&file);

        saida << BI + "\n"
                 + numConta + "\n"
                 + senha + "\n"
                 + saldo  +"\n";
        file.flush();
        file.close();
    }

}



//Verifica se existe o titular da conta que tentamos abrir
bool FrmConta::existeBI(QString BI){
    QString local = "D:/Escolaridade/FENG/2_Ano/LP/C++/ProjectoFinal/ProjectoCpp/ProjectoCpp/files/";
    QString arq = "listaEstudante.txt";
    QFile file(local + arq);
    QString estBI;
    bool res = false;

    int cont=0, k1=2, k2=3;

    if(!file.open(QFile::ReadOnly|QFile::Text)){
        QMessageBox::warning(this, "ERRO", "Erro ao abrir arquivo");
    }else{
        QTextStream entrada(&file);
        while(!entrada.atEnd() && res!=true){

            QString texto = entrada.readLine();
            if((cont%k1==0 && cont%k2==0) || cont==1){
                if(BI==texto){
                    res=true;
                    QMessageBox::warning(this, "BI", texto);
                }
            }
        }
        file.close();
    }

    return res;
}



