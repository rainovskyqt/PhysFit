#ifndef RESULT_H
#define RESULT_H

#include <QObject>

class Result : public QObject
{
    Q_OBJECT
public:
    explicit Result(QObject *parent = nullptr);
     Result(int category, int exercise, const QString &result, int status, int trainingId, const QString &exerciseName,
           int baseId = 0, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    int category() const;
    void setCategory(int newCategory);
    int exercise() const;
    void setExercise(int newExercise);
    QString result() const;
    void setResult(const QString &newResult);
    int status() const;
    void setStatus(int newStatus);
    int trainingId() const;
    void setTrainingId(int newTrainingId);

    QString exerciseName() const;
    void setExerciseName(const QString &newExerciseName);

signals:

private:
    int m_baseId;
    int m_category;
    int m_exercise;
    QString m_result;
    int m_status;
    int m_trainingId;

    QString m_exerciseName;
};

#endif // RESULT_H
