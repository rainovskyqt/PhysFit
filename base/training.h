#ifndef TRAINING_H
#define TRAINING_H

#include <QDate>
#include <QObject>

class Training : public QObject
{
    Q_OBJECT
public:
    explicit Training(QObject *parent = nullptr);
    Training(const QDate bornDate, const QString &name, const QString &comments, int sportsmenId, int baseId = 0, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    QDate date() const;
    void setDate(const QDate &newDate);
    QString name() const;
    void setName(const QString &newName);
    QString comments() const;
    void setComments(const QString &newComments);
    int sportsmenId() const;
    void setSportsmenId(int newSportsmenId);

signals:

private:
    int m_baseId;
    QDate m_date;
    QString m_name;
    QString m_comments;
    int m_sportsmenId;
};

#endif // TRAINING_H
