#ifndef SPORTSMEN_H
#define SPORTSMEN_H

#include <QDate>
#include <QObject>

class Sportsmen : public QObject
{
    Q_OBJECT
public:
    explicit Sportsmen(QObject *parent = nullptr);
    Sportsmen(const QString &surname, const QString &name, const QString &midllename, const QDate bornDate,
              const QString &comments, int baseId = 0, QObject *parent = nullptr);

    ~Sportsmen(){}

    QString surname() const;
    void setSurname(const QString &newSurname);
    QString name() const;
    void setName(const QString &newName);
    QString midllename() const;
    void setMidllename(const QString &newMidllename);
    QDate bornDate() const;
    void setBornDate(const QDate &newBornDate);
    QString comments() const;
    void setComments(const QString &newComments);
    int getBaseId() const;
    void setBaseId(int newBaseId);

signals:

private:
    int baseId;
    QString m_surname;
    QString m_name;
    QString m_midllename;
    QDate m_bornDate;
    QString m_comments;

};

#endif // SPORTSMEN_H
