#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QDialog>


namespace Ui {
class TrainingForm;
}

class Training;

class TrainingForm : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = nullptr, Training *training = nullptr);
    ~TrainingForm();

    Training *getTraining();

    void setSportsmenId(int newSportsmenId);

private:
    Ui::TrainingForm *ui;

    Training *m_training;
    int m_sportsmenId;
};

#endif // TRAININGFORM_H
