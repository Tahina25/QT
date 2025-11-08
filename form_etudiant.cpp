#include "form_etudiant.h"
#include "connexionbd.h"
#include "ui_form_etudiant.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlRecord>

form_etudiant::form_etudiant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::form_etudiant)
{
    ui->setupUi(this);

    // Connexion à la base
    if (!db.open()) {
        db = connexionBd::connectBase();
    }
}

form_etudiant::~form_etudiant()
{
    delete ui;
}

void form_etudiant::on_buttonBox_accepted()
{
    QString matricule = ui->lineEdit->text();
    QString nom = ui->lineEdit_2->text();
    QString prenom = ui->lineEdit_3->text();
    QString telephone = ui->lineEdit_4->text();
    QString mail = ui->lineEdit_5->text();
    int num = ui->comboBox_groupe->currentIndex() + 1;

    QSqlQuery etudiant(db);
    etudiant.prepare("INSERT INTO etudiant (Matricule, Nom_etudiant, Prenom_etudiant, telephone_etudiant, mail_etudiant, GROUPE_num_groupe) "
                     "VALUES (:matricule, :nom, :prenom, :telephone, :mail, :num)");
    etudiant.bindValue(":matricule", matricule);
    etudiant.bindValue(":nom", nom);
    etudiant.bindValue(":prenom", prenom);
    etudiant.bindValue(":telephone", telephone);
    etudiant.bindValue(":mail", mail);
    etudiant.bindValue(":num", num);

    if (!etudiant.exec()) {
        QMessageBox::warning(this, "Etudiant", "Erreur lors de l'inscription de l'étudiant.");
        qDebug() << "Erreur de la requête de l'étudiant : " << etudiant.lastError().text();
    } else {
        QMessageBox::information(this, "Etudiant", "L'inscription de l'étudiant a réussi.");

        // Rafraîchit automatiquement la liste sur la fenêtre principale
        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadEtudiants();
        }

        // Nettoyage des champs
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->lineEdit_4->clear();
        ui->lineEdit_5->clear();
        ui->comboBox_groupe->setCurrentIndex(0);
    }
}

void form_etudiant::on_buttonBox_rejected()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox_groupe->setCurrentIndex(0);

    this->close();
}
