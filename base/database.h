#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QVariant>
#include <QVector>

#include <QSqlQuery>
#include "sportsmen.h"
#include "category.h"

using Values = QMap<QString, QVariant>;

class EducationalWork;
class GenericWorkForm;

class Database : public QObject
{
    Q_OBJECT

public:

    // enum DictName{
    //     Department,
    //     Post,
    //     Rang,
    //     Discipline,
    //     Course,
    //     WorkForm
    // };

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

    // void addPosts(QList<UserPost> posts, int userId);
    // int addPost(UserPost post, int userId);
    // User *login(QString login, QString password, int id = 0);
    // QVector<Dictionary> getDictionary(DictName name);
    // QList<StudyYear> getYears();
    // TeacherPlan *requestPlan(UserPost post, int yearId);
    // int updateTeacherPlan(TeacherPlan *plan);
    // QString getTeacherPlanComments(int planId);
    // void updateTeacherPlanComments(int planId, const QString &comments);
    // QString encodePassword(QString password);
    // QVector<EducationalWork *> educationWork(int planId);
    // QVector<GenericWork *> genericWork(int planId, WorkType type);
    // int saveWork(TeacherWork *work);
    // void deleteWork(TeacherWork *work);
    // QList<EducationalHour*> getEdcationalHours(int workId);
    // int saveEdcationalHour(EducationalHour* hour);
    // QList<GenericWorkForm *> getWorks(WorkType type);
    // QMap<int, CommentsUpdate> updateComments(bool all, int userId);
    // void setViewed(int userId, int commentId);
    // QMultiHash<QString, QPair<QString, int> > staffList(int facultyId = 0);

public slots:

signals:

private slots:

private:
    // int baseId;
    QString m_lastError;
    QSqlQuery *executeQuery(QString queryString, Values vals = {});
    // int getId(QString json);
    // int saveEducationalWork(TeacherWork *work);
    // int saveGenericWork(TeacherWork *work);
};

#endif // DATABASE_H
