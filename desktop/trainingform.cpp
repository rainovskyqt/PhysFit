#include "trainingform.h"
#include "ui_trainingform.h"

#include "../base/training.h"

TrainingForm::TrainingForm(QWidget *parent, Training *training)
    : QDialog(parent)
    , ui(new Ui::TrainingForm)
    , m_training(training)
    , m_sportsmenId(0)
{
    ui->setupUi(this);

    ui->date_date->setDate(QDate::currentDate());


    if(m_training != nullptr){
        ui->line_name->setText(m_training->name());
        ui->date_date->setDate(m_training->date());
        ui->text_comments->setPlainText(m_training->comments());
        m_sportsmenId = training->sportsmenId();
    }
}

TrainingForm::~TrainingForm()
{
    delete ui;
}

Training *TrainingForm::getTraining()
{
    if(m_training == nullptr) m_training = new Training();

    m_training->setDate(ui->date_date->date());
    m_training->setName(ui->line_name->text());
    m_training->setComments(ui->text_comments->toPlainText());
    m_training->setSportsmenId(m_sportsmenId);

    return m_training;
}

void TrainingForm::setSportsmenId(int newSportsmenId)
{
    m_sportsmenId = newSportsmenId;
}
