#include "sportsmenform.h"
#include "ui_sportsmenform.h"


SportsmenForm::SportsmenForm(QWidget *parent, Sportsmen *sportsmen)
    : QDialog(parent)
    , ui(new Ui::SportsmenForm)
{
    ui->setupUi(this);
    m_sportsmen = sportsmen;

    if(m_sportsmen != nullptr){
        ui->line_surname->setText(m_sportsmen->surname());
        ui->line_name->setText(m_sportsmen->name());
        ui->line_midllename->setText(m_sportsmen->midllename());
        ui->line_bornDate->setText(m_sportsmen->bornDate().toString("dd.MM.yyyy"));
        ui->text_comments->setPlainText(m_sportsmen->comments());
    }
}

SportsmenForm::~SportsmenForm()
{
    delete ui;
}

Sportsmen *SportsmenForm::getSportsmen()
{
    if(m_sportsmen == nullptr) m_sportsmen = new Sportsmen();

    m_sportsmen->setSurname(ui->line_surname->text());
    m_sportsmen->setName(ui->line_name->text());
    m_sportsmen->setMidllename(ui->line_midllename->text());
    m_sportsmen->setBornDate(QDate::fromString(ui->line_bornDate->text(), "dd.MM.yyyy"));
    m_sportsmen->setComments(ui->text_comments->toPlainText());

    return m_sportsmen;
}
