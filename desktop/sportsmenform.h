#ifndef SPORTSMENFORM_H
#define SPORTSMENFORM_H

#include <QDialog>

#include "../base/sportsmen.h"

namespace Ui {
class SportsmenForm;
}

class SportsmenForm : public QDialog
{
    Q_OBJECT

public:
    explicit SportsmenForm(QWidget *parent = nullptr, Sportsmen *sportsmen = nullptr);
    ~SportsmenForm();

    Sportsmen* getSportsmen();

private:
    Ui::SportsmenForm *ui;

    Sportsmen *m_sportsmen;
};

#endif // SPORTSMENFORM_H
