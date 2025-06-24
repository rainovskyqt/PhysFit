#ifndef RESULTSFORM_H
#define RESULTSFORM_H

#include <QDialog>

namespace Ui {
class ResultsForm;
}

class Result;

class ResultsForm : public QDialog
{
    Q_OBJECT

public:
    explicit ResultsForm(QWidget *parent = nullptr, Result *result = nullptr);
    ~ResultsForm();

    Result *getResult();


    void setTrainingId(int newTrainingId);

private:
    Ui::ResultsForm *ui;

    Result *m_result;

    void loadDiscts();
    int m_trainingId;
};

#endif // RESULTSFORM_H
