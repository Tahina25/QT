#include "form_theme.h"
#include "ui_form_theme.h"
#include "connexionbd.h"
#include "mainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QCompleter>
#include <QSqlQueryModel>


form_theme::form_theme(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_theme)
{
    ui->setupUi(this);

    // Connexion à la base
    if (!db.open()){
        db = connexionBd::connectBase();
    }

    ui->comboBox->setEditable(true);
    ui->comboBox_3->setEditable(true);

    // ✅ Créer un modèle SQL pour la complétion
    QSqlQueryModel *modelEnseignant = new QSqlQueryModel(this);
    modelEnseignant->setQuery("SELECT trilogie_ens FROM enseignant", db);

    QSqlQueryModel *modelParcours = new QSqlQueryModel(this);
    modelParcours->setQuery("SELECT code_parcours FROM parcours", db);

    // ✅ Attacher les modèles aux comboBox
    ui->comboBox->setModel(modelEnseignant);
    ui->comboBox_3->setModel(modelParcours);

    // ✅ Créer les compléteurs
    QCompleter *completerEns = new QCompleter(modelEnseignant, this);
    completerEns->setCompletionColumn(0);
    completerEns->setCaseSensitivity(Qt::CaseInsensitive);
    completerEns->setFilterMode(Qt::MatchContains);

    QCompleter *completerPar = new QCompleter(modelParcours, this);
    completerPar->setCompletionColumn(0);
    completerPar->setCaseSensitivity(Qt::CaseInsensitive);
    completerPar->setFilterMode(Qt::MatchContains);

    // ✅ Associer le completer à chaque comboBox
    ui->comboBox->setCompleter(completerEns);
    ui->comboBox_3->setCompleter(completerPar);
}

form_theme::~form_theme()
{
    delete ui;
}

void form_theme::on_buttonBox_accepted()
{
    int num = ui->lineEdit->text().toInt();
    QString libelle = ui->lineEdit_2->text();
    QString description = ui->textEdit->toPlainText();
    QString enseignant = ui->comboBox->currentText();
    QString parcour = ui->comboBox_3->currentText();

    QSqlQuery theme;
    theme.prepare("INSERT INTO theme (num_theme, libelle, description, ENSEIGNANT_trilogie_ens, PARCOURS_code_parcours) "
                  "VALUES (:num, :libelle, :description, :enseignant, :parcour)");
    theme.bindValue(":num", num);
    theme.bindValue(":libelle", libelle);
    theme.bindValue(":description", description);
    theme.bindValue(":enseignant", enseignant);
    theme.bindValue(":parcour", parcour);


    if(!theme.exec()){
        QMessageBox::warning(this, "Theme", "Erreur lors de l'enregistrement du theme");
        qDebug()<<"Erreur de la requette theme : "<<theme.lastError().text();
    }else{
        QMessageBox::information(this, "Theme", "L'ajout du thème réussi.");

        // Rafraîchit automatiquement la liste sur la fenêtre principale
        MainWindow *mw = qobject_cast<MainWindow*>(this->parentWidget());
        if (mw) {
            mw->loadThemes();
        }

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->textEdit->clear();
        ui->comboBox->setEditText("");
        ui->comboBox_3->setEditText("");
    }

}


void form_theme::on_buttonBox_rejected()
{

    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->textEdit->clear();
    ui->comboBox->setEditText("");
    ui->comboBox_3->setEditText("");

    this->close();
}

