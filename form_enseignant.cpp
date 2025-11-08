#include "form_enseignant.h"
#include "ui_form_enseignant.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>



form_enseignant::form_enseignant(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_enseignant)
{
    ui->setupUi(this);

    // Connexion à la base
    if (!db.open()){
        db = connexionBd::connectBase();
    }

}

form_enseignant::~form_enseignant()
{
    delete ui;
}

void form_enseignant::on_buttonBox_accepted()
{
    QString trilogie = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString email = ui->lineEdit_4->text();
    QString contact = ui->lineEdit_5->text();

    if(trilogie.isEmpty()||nom.isEmpty()||prenom.isEmpty()||email.isEmpty()||contact.isEmpty()){
        QMessageBox::information(this, "Enseignant", "Veuiller remplir tout les champs.");
        return;
    }

    QSqlQuery enseignant;
    enseignant.prepare("INSERT INTO enseignant (Trilogie_ens, nom_enseignant, prenom_enseignant, telephone_enseignant, mail_enseignant)"
                       " VALUES (:trilogie, :nom, :prenom, :contact, :email)");
    enseignant.bindValue(":trilogie", trilogie);
    enseignant.bindValue(":nom", nom);
    enseignant.bindValue(":prenom", prenom);
    enseignant.bindValue(":email", email);
    enseignant.bindValue(":contact", contact);

    if(!enseignant.exec()){
        QMessageBox::warning(this, "Enseignant", "Erreur lors de l'inscription de l'enseignant.");
        qDebug()<<"Erreur de la requète de l'enseignant : "<<enseignant.lastError().text();
    }else{
        QMessageBox::information(this, "Enseignant","L'inscription de l'enseignant réussie.");

        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadEnseignants();
        }
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
    }
}


void form_enseignant::on_buttonBox_rejected()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();

    this->close();
}

