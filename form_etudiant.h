#ifndef FORM_ETUDIANT_H
#define FORM_ETUDIANT_H

#include <QDialog>
#include "connexionbd.h"
#include <QSqlDatabase>


namespace Ui {
class form_etudiant;
}

class form_etudiant : public QDialog
{
    Q_OBJECT

public:
    explicit form_etudiant(QWidget *parent = nullptr);
    ~form_etudiant();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::form_etudiant *ui;
    QSqlDatabase db;

};
#endif // FORM_ETUDIANT_H
