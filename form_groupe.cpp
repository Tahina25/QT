#include "form_groupe.h"
#include "ui_form_groupe.h"
#include "connexionbd.h"

form_groupe::form_groupe(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::form_groupe)
{
    ui->setupUi(this);

    // Connexion à la base
    if (!db.open()){
        db = connexionBd::connectBase();
    }
}

form_groupe::~form_groupe()
{
    delete ui;
}
