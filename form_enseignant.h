#ifndef FORM_ENSEIGNANT_H
#define FORM_ENSEIGNANT_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class form_enseignant;
}

class form_enseignant : public QDialog
{
    Q_OBJECT

public:
    explicit form_enseignant(QWidget *parent = nullptr);
    ~form_enseignant();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::form_enseignant *ui;
    QSqlDatabase db;
};

#endif // FORM_ENSEIGNANT_H
