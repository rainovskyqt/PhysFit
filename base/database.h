#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QVariant>
#include <QVector>

#include <QSqlQuery>
#include "sportsmen.h"
#include "category.h"
#include "exercise.h"
#include "training.h"
#include "result.h"

using Values = QMap<QString, QVariant>;

class EducationalWork;
class GenericWorkForm;

class Database : public QObject
{
    Q_OBJECT

public:

    explicit Database();
    static Database *get();
    bool init(QString host, int port);

    int addSportsmen(Sportsmen *s);
    void editSportsmen(Sportsmen *s);
    void deleteSportsmen(Sportsmen *s);
    const QString &lastError() const;
    QVector<Sportsmen*> allSportsmens();

    QVector<Category*> allCategory();
    int addCategory(Category *c);
    void editCategory(Category *c);
    void deleteCategory(Category *c);

    QVector<Exercise*> allExercise();
    int addExercise(Exercise *e);
    void editExercise(Exercise *e);
    void deleteExercise(Exercise *e);

    QVector<Training*> trainings(int sportsmenId);
    int addTraining(Training *t);
    void editTraining(Training *t);
    void deleteTraining(Training *t);

    QVector<Result*> results(int trainingId);
    int addResult(Result *r);
    void editResult(Result *r);
    void deleteResult(Result *r);


public slots:

signals:

private slots:

private:
    QString m_lastError;
    QSqlQuery *executeQuery(QString queryString, Values vals = {});
};

#endif // DATABASE_H
