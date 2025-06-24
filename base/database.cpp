#include "database.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QEventLoop>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVector>

Q_GLOBAL_STATIC(Database, globalInst)

Database *Database::get()
{
    return globalInst();
}

bool Database::init(QString host, int port)
{
    QSqlDatabase base = QSqlDatabase::addDatabase("QMYSQL");
    base.setHostName(host);
    base.setPort(port);
    base.setDatabaseName("corusant");
    base.setUserName("ordo");
    base.setPassword("ordo7532159");
    if(!base.open()){
        // m_lastError = base.lastError().text();
        qDebug() << base.lastError().text();
        return false;
    }
    return true;
}

int Database::addSportsmen(Sportsmen *s)
{
    QString queryString = "INSERT INTO `PhysFit_sportsmens` "
                          "(`surname`, `name`, `midllename`, `born_date`, `comments`) "
                          "VALUES (:surname, :name, :midllename, :date, :comments)";
    Values vals;
    vals.insert(":surname", s->surname());
    vals.insert(":name", s->name());
    vals.insert(":midllename", s->midllename());
    vals.insert(":date", s->bornDate());
    vals.insert(":comments", s->comments());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    s->setBaseId(id);

    delete query;
    return id;
}

void Database::editSportsmen(Sportsmen *s)
{
    QString queryString = "UPDATE `PhysFit_sportsmens` "
                          "SET `surname` = :surname, `name` = :name, `midllename` = :midllename, "
                          "`born_date` = :born_date, `comments` = :comments "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", s->getBaseId());
    vals.insert(":surname", s->surname());
    vals.insert(":name", s->name());
    vals.insert(":midllename", s->midllename());
    vals.insert(":date", s->bornDate());
    vals.insert(":comments", s->comments());

    delete executeQuery(queryString, vals);
}

void Database::deleteSportsmen(Sportsmen *s)
{
    QString queryString = "DELETE FROM `PhysFit_sportsmens` "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", s->getBaseId());

    delete executeQuery(queryString, vals);
}

const QString &Database::lastError() const
{
    return m_lastError;
}

QVector<Sportsmen*> Database::allSportsmens()
{
    QString queryString = "SELECT id, surname, `name`, midllename, born_date, comments "
                          "FROM PhysFit_sportsmens";


    QVector<Sportsmen*> s;
    auto answer = executeQuery(queryString);
    while (answer->next()) {
        s.append(new Sportsmen(answer->value("surname").toString(),
                               answer->value("name").toString(),
                               answer->value("midllename").toString(),
                               answer->value("born_date").toDate(),
                               answer->value("comments").toString(),
                               answer->value("id").toInt(),
                               this));          //Привязываем спорсмена к базе
    }

    return s;
}

QVector<Category *> Database::allCategory()
{
    QString queryString = "SELECT id, name "
                          "FROM PhysFit_category";

    QVector<Category*> c;
    auto answer = executeQuery(queryString);
    while (answer->next()) {
        c.append(new Category(answer->value("name").toString(),
                              answer->value("id").toInt(),
                              this));
    }

    return c;
}

int Database::addCategory(Category *c)
{
    QString queryString = "INSERT INTO `PhysFit_category`(`name`) "
                          "VALUES (:name)";
    Values vals;
    vals.insert(":name", c->name());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    c->setBaseId(id);

    delete query;
    return id;
}

void Database::editCategory(Category *c)
{
    QString queryString = "UPDATE `PhysFit_category` "
                          "SET `name` = :name "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", c->baseId());
    vals.insert(":name", c->name());

    delete executeQuery(queryString, vals);
}

void Database::deleteCategory(Category *c)
{
    QString queryString = "DELETE FROM `PhysFit_category` "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", c->baseId());

    delete executeQuery(queryString, vals);
}

QVector<Exercise *> Database::allExercise()
{
    QString queryString = "SELECT id, name "
                          "FROM PhysFit_exercise";

    QVector<Exercise*> e;
    auto answer = executeQuery(queryString);
    while (answer->next()) {
        e.append(new Exercise(answer->value("name").toString(),
                              answer->value("id").toInt(),
                              this));
    }

    return e;
}

int Database::addExercise(Exercise *e)
{
    QString queryString = "INSERT INTO `PhysFit_exercise`(`name`) "
                          "VALUES (:name)";
    Values vals;
    vals.insert(":name", e->name());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    e->setBaseId(id);

    delete query;
    return id;
}

void Database::editExercise(Exercise *e)
{
    QString queryString = "UPDATE `PhysFit_exercise` "
                          "SET `name` = :name "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", e->baseId());
    vals.insert(":name", e->name());

    delete executeQuery(queryString, vals);
}

void Database::deleteExercise(Exercise *e)
{
    QString queryString = "DELETE FROM `PhysFit_exercise` "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", e->baseId());
    
    delete executeQuery(queryString, vals);
}

QVector<Training *> Database::trainings(int sportsmenId)
{
    QString queryString = "SELECT id, `date`, `name`, comments, sportsmen "
                          "FROM PhysFit_trainings "
                          "WHERE sportsmen = :sportsmen ";
    Values vals;
    vals.insert(":sportsmen", sportsmenId);

    QVector<Training*> t;
    auto answer = executeQuery(queryString, vals);
    while (answer->next()) {
        t.append(new Training(answer->value("date").toDate(),
                              answer->value("name").toString(),
                              answer->value("comments").toString(),
                              answer->value("sportsmen").toInt(),
                              answer->value("id").toInt(),
                              this));
    }

    return t;
}

int Database::addTraining(Training *t)
{
    QString queryString = "INSERT INTO `PhysFit_trainings` "
                          "(`date`, `name`, `comments`, `sportsmen`) "
                          "VALUES (:date, :name, :comments, :sportsmen)";
    Values vals;
    vals.insert(":date", t->date());
    vals.insert(":name", t->name());
    vals.insert(":comments", t->comments());
    vals.insert(":sportsmen", t->sportsmenId());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    t->setBaseId(id);

    delete query;
    return id;
}

void Database::editTraining(Training *t)
{
    QString queryString = "UPDATE `PhysFit_trainings` "
                          "SET `date` = :date, `name` = :name, `comments` = :comments "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", t->baseId());
    vals.insert(":date", t->date());
    vals.insert(":name", t->name());
    vals.insert(":comments", t->comments());

    delete executeQuery(queryString, vals);
}

void Database::deleteTraining(Training *t)
{
    QString queryString = "DELETE FROM `PhysFit_trainings` "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", t->baseId());

    delete executeQuery(queryString, vals);
}

QVector<Result *> Database::results(int trainingId)
{
    QString queryString = "SELECT R.id, R.category, R.exercise, R.result, R.`status`, E.`name` as eName, R.training "
                          "FROM PhysFit_results R "
                          "INNER JOIN PhysFit_exercise E ON E.id = R.exercise "
                          "WHERE R.training = :training ";
    Values vals;
    vals.insert(":training", trainingId);

    QVector<Result*> r;
    auto answer = executeQuery(queryString, vals);
    while (answer->next()) {
        r.append(new Result(answer->value("category").toInt(),
                            answer->value("exercise").toInt(),
                            answer->value("result").toString(),
                            answer->value("status").toInt(),
                            answer->value("training").toInt(),
                            answer->value("eName").toString(),
                            answer->value("id").toInt(),
                            this));
    }

    return r;
}

int Database::addResult(Result *r)
{
    QString queryString = "INSERT INTO `PhysFit_results` "
                          "(category, exercise, result, status, training) "
                          "VALUES (:category, :exercise, :result, :status, :training)";
    Values vals;
    vals.insert(":category", r->category());
    vals.insert(":exercise", r->exercise());
    vals.insert(":result", r->result());
    vals.insert(":status", r->status());
    vals.insert(":training", r->trainingId());

    auto query = executeQuery(queryString, vals);
    query->next();

    int id = query->lastInsertId().toInt();
    r->setBaseId(id);

    delete query;
    return id;
}

void Database::editResult(Result *r)
{

}

void Database::deleteResult(Result *r)
{
    QString queryString = "DELETE FROM `PhysFit_results` "
                          "WHERE id = :id";
    Values vals;
    vals.insert(":id", r->baseId());

    delete executeQuery(queryString, vals);
}


QSqlQuery* Database::executeQuery(QString queryString, Values vals)
{
    auto base = QSqlDatabase::database();
    if(!base.open())
        base.open();

    QSqlQuery *query = new QSqlQuery(base);
    query->prepare(queryString);
    for(auto val = vals.begin(); val != vals.end(); ++val){
        query->bindValue(val.key(), val.value());
    }
    query->exec();

    if(query->lastError().isValid()){
        m_lastError = query->lastError().text();
        qDebug() << m_lastError;
    }

    base.close();
    return query;
}

Database::Database(){}
