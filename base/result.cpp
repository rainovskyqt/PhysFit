#include "result.h"

Result::Result(QObject *parent): QObject{parent}{}

Result::Result(int category, int exercise, const QString &result, int status, int trainingId, const QString &exerciseName,
               int baseId, QObject *parent) : QObject{parent}
{
    setCategory(category);
    setExercise(exercise);
    setResult(result);
    setStatus(status);
    setTrainingId(trainingId);
    setBaseId(baseId);
    setExerciseName(exerciseName);
}

int Result::baseId() const
{
    return m_baseId;
}

void Result::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

int Result::category() const
{
    return m_category;
}

void Result::setCategory(int newCategory)
{
    m_category = newCategory;
}

int Result::exercise() const
{
    return m_exercise;
}

void Result::setExercise(int newExercise)
{
    m_exercise = newExercise;
}

QString Result::result() const
{
    return m_result;
}

void Result::setResult(const QString &newResult)
{
    m_result = newResult;
}

int Result::status() const
{
    return m_status;
}

void Result::setStatus(int newStatus)
{
    m_status = newStatus;
}

int Result::trainingId() const
{
    return m_trainingId;
}

void Result::setTrainingId(int newTrainingId)
{
    m_trainingId = newTrainingId;
}

QString Result::exerciseName() const
{
    return m_exerciseName;
}

void Result::setExerciseName(const QString &newExerciseName)
{
    m_exerciseName = newExerciseName;
}
