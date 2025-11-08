#ifndef FORM_GROUPE_H
#define FORM_GROUPE_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class form_groupe;
}

class form_groupe : public QDialog
{
    Q_OBJECT

public:
    explicit form_groupe(QWidget *parent = nullptr);
    ~form_groupe();

private:
    Ui::form_groupe *ui;
    QSqlDatabase db;
};

#endif // FORM_GROUPE_H
