#include "resultsform.h"
#include "ui_resultsform.h"

#include "../base/database.h"

ResultsForm::ResultsForm(QWidget *parent, Result *result)
    : QDialog(parent)
    , ui(new Ui::ResultsForm)
    , m_result(result)

{
    ui->setupUi(this);
    loadDiscts();
}

ResultsForm::~ResultsForm()
{
    delete ui;
}

Result *ResultsForm::getResult()
{
    if(m_result == nullptr) m_result = new Result();

    m_result->setCategory(ui->cb_category->currentData(Qt::UserRole).toInt());
    m_result->setExercise(ui->cb_exercise->currentData(Qt::UserRole).toInt());
    m_result->setResult(ui->line_result->text());
    m_result->setStatus(ui->cb_status->currentText().toInt());
    m_result->setTrainingId(m_trainingId);

    return m_result;
}

void ResultsForm::loadDiscts()
{
    ui->cb_category->addItem("-");
    ui->cb_exercise->addItem("-");

    auto categorys = Database::get()->allCategory();
    for(const auto &c : categorys){
        ui->cb_category->addItem(c->name(), c->baseId());
    }

    auto exercise = Database::get()->allExercise();
    for(const auto &e : exercise){
        ui->cb_exercise->addItem(e->name(), e->baseId());
    }
}

void ResultsForm::setTrainingId(int newTrainingId)
{
    m_trainingId = newTrainingId;
}
