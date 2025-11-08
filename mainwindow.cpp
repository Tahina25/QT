#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form_etudiant.h"
#include "form_groupe.h"
#include "form_enseignant.h"
#include "form_theme.h"
#include "connexionbd.h"
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlError>

// Définition de la variable globale déclarée dans mainwindow.h
QSqlDatabase db;

// fonction reinitialisation des boutons
void MainWindow::reset_buttons()
{
    // Réinitialisation checked des bouton etendu et compact
    //etendu
    ui->btn_dashboard->setChecked(false);
    ui->btn_etudiants->setChecked(false);
    ui->btn_groupes->setChecked(false);
    ui->btn_enseignants->setChecked(false);
    ui->btn_themes->setChecked(false);
    ui->btn_evaluation->setChecked(false);

    //compact
    ui->btn_icone_dashboard->setChecked(false);
    ui->btn_icone_etudiants->setChecked(false);
    ui->btn_icone_groupes->setChecked(false);
    ui->btn_icone_enseignants->setChecked(false);
    ui->btn_icone_themes->setChecked(false);
    ui->btn_icone_evaluation->setChecked(false);
}

// Constructeur de la classe MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
        ui->setupUi(this);

    // qDebug() << "Driver list :" << QSqlDatabase::drivers();
    this->showMaximized(); // Forcer la taille

        // Connexion à la base
    db = connexionBd::connectBase();

    /*QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("gestion_stage");
    db.setUserName("root");
    db.setPassword("");

    if (db.open()) {
        qDebug() << "Connexion réussie à la base de données !";
    } else {
        qDebug() << "Erreur de connexion :" << db.lastError().text();
    }*/

    // Connexion des boutons icônes aux boutons étendus
    connect(ui->btn_icone_dashboard, &QPushButton::clicked, this, &MainWindow::on_btn_dashboard_clicked);
    connect(ui->btn_icone_etudiants, &QPushButton::clicked, this, &MainWindow::on_btn_etudiants_clicked);
    connect(ui->btn_icone_groupes, &QPushButton::clicked, this, &MainWindow::on_btn_groupes_clicked);
    connect(ui->btn_icone_enseignants, &QPushButton::clicked, this, &MainWindow::on_btn_enseignants_clicked);
    connect(ui->btn_icone_themes, &QPushButton::clicked, this, &MainWindow::on_btn_themes_clicked);
    connect(ui->btn_icone_evaluation, &QPushButton::clicked, this, &MainWindow::on_btn_evaluation_clicked);

    // Initialisation de l'application au démarrage
    // Affichage de la page dashboard (index 0) et activation de son bouton
    ui->containers_widget->setCurrentIndex(0);
    ui->btn_dashboard->setChecked(true);
    ui->btn_icone_dashboard->setChecked(true);

      loadEtudiants();
      loadEnseignants();
      loadThemes();
      afficherStatEtudiants();
      afficherStatGroupes();
      afficherStatEnseignants();
      afficherStatThemes();

}

// Destructeur
MainWindow::~MainWindow()
{
    delete ui;
}

//(SLOTS)
void MainWindow::on_btn_dashboard_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(0);
    ui->btn_dashboard->setChecked(true);
    ui->btn_icone_dashboard->setChecked(true);
}

void MainWindow::on_btn_etudiants_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(1);
    ui->btn_etudiants->setChecked(true);
    ui->btn_icone_etudiants->setChecked(true);
}
void MainWindow::on_btn_groupes_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(2);
    ui->btn_groupes->setChecked(true);
    ui->btn_icone_groupes->setChecked(true);
}

void MainWindow::on_btn_enseignants_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(3);
    ui->btn_enseignants->setChecked(true);
    ui->btn_icone_enseignants->setChecked(true);
}

void MainWindow::on_btn_themes_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(4);
    ui->btn_themes->setChecked(true);
    ui->btn_icone_themes->setChecked(true);
}

void MainWindow::on_btn_evaluation_clicked()
{
    reset_buttons();
    ui->containers_widget->setCurrentIndex(5);
    ui->btn_evaluation->setChecked(true);
    ui->btn_icone_evaluation->setChecked(true);
}

void MainWindow::on_btn_add_etudiants_clicked()
{

    form_etudiant *form = new form_etudiant(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_groupes_clicked()
{
    form_groupe *form = new form_groupe(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_enseignants_clicked()
{
    form_enseignant *form = new form_enseignant(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_themes_clicked()
{
    // Ouvre le formulaire Thème
    form_theme *form = new form_theme(this);
    form->exec();
    delete form;
}

void MainWindow::on_btn_add_etudiant_clicked()
{
    on_btn_add_etudiants_clicked();
}

void MainWindow::on_btn_add_groupe_clicked()
{
    on_btn_add_groupes_clicked();
}

void MainWindow::on_btn_add_enseignant_clicked()
{
    on_btn_add_enseignants_clicked();
}

void MainWindow::on_btn_add_theme_clicked()
{
    on_btn_add_themes_clicked();
}

void MainWindow::loadEtudiants()
{
    QSqlQueryModel *model = new QSqlQueryModel(this);
    model->setQuery("SELECT Matricule, Nom_etudiant, Prenom_etudiant, Telephone_etudiant, mail_etudiant FROM etudiant");

    if (model->lastError().isValid()) {
        qDebug() << "Erreur SQL :" << model->lastError().text();
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Matricule");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");

    ui->table_etudiants->setModel(model);
    ui->table_etudiants->resizeColumnsToContents();
    ui->table_etudiants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::loadEnseignants()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT Trilogie_ens, Nom_enseignant, Prenom_enseignant, Telephone_enseignant, Mail_enseignant FROM enseignant");

    if(model->lastError().isValid()){
        QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Trilogie");
    model->setHeaderData(1, Qt::Horizontal, "Nom");
    model->setHeaderData(2, Qt::Horizontal, "Prénom");
    model->setHeaderData(3, Qt::Horizontal, "Téléphone");
    model->setHeaderData(4, Qt::Horizontal, "Email");

    ui->table_enseignants->setModel(model);
    ui->table_enseignants->resizeColumnsToContents();
    ui->table_enseignants->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void MainWindow::loadThemes()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT num_theme, libelle, description FROM theme");

    if (model->lastError().isValid()){
        QMessageBox::critical(this, "Erreur SQL", model->lastError().text());
        return;
    }

    model->setHeaderData(0, Qt::Horizontal, "Numéro");
    model->setHeaderData(1, Qt::Horizontal, "Libelle");
    model->setHeaderData(2, Qt::Horizontal, "Description");

    ui->table_themes->setModel(model);
    ui->table_themes->resizeColumnsToContents();
    ui->table_themes->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
 //le 128
void MainWindow::afficherStatEtudiants()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM etudiant"))
    {
        if (query.next()) {
            int totalEtudiants = query.value(0).toInt(); // d'abord on récupère la valeur
            ui->label_3->setText(QString::number(totalEtudiants)); // puis on l'affiche
        }
    }
    else {
        qDebug() << "Erreur de la requête étudiants :" << query.lastError().text();
    }
}

void MainWindow::afficherStatGroupes()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM groupe"))
    {
        if (query.next()){
             int totalGroupe = query.value(0).toInt();
            ui->lbl_total_groupes->setText(QString::number(totalGroupe));
        }
    }
    else {
        qDebug() <<"Erreur de la requête groupes :" << query.lastError().text();
    }
}

void MainWindow::afficherStatEnseignants()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM groupe"))
    {
        if (query.next()){
            int totalEnseignant = query.value(0).toInt();
            ui->lbl_total_enseignants->setText(QString::number (totalEnseignant));
        }
    }
    else {
        qDebug() <<"Erreur de la requête enseignants :" << query.lastError().text();
    }
}

void MainWindow::afficherStatThemes()
{
    QSqlQuery query;
    if (query.exec("SELECT COUNT(*) FROM theme"))
    {
        if (query.next()){
            int totalTheme = query.value(0).toInt();
            ui->lbl_total_themes->setText(QString::number (totalTheme));
        }
    }
    else {
        qDebug() <<"Erreur de la requête themes :" << query.lastError().text();
    }
}




