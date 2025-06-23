#include "sportsmen.h"

Sportsmen::Sportsmen(QObject *parent)
    : QObject{parent}
{}

Sportsmen::Sportsmen(const QString &surname, const QString &name, const QString &midllename, const QDate bornDate,
                     const QString &comments, int baseId, QObject *parent) : QObject{parent}
{
    setSurname(surname);
    setName(name);
    setMidllename(midllename);
    setBornDate(bornDate);
    setComments(comments);
    setBaseId(baseId);
}

QString Sportsmen::surname() const
{
    return m_surname;
}

void Sportsmen::setSurname(const QString &newSurname)
{
    m_surname = newSurname;
}

QString Sportsmen::name() const
{
    return m_name;
}

void Sportsmen::setName(const QString &newName)
{
    m_name = newName;
}

QString Sportsmen::midllename() const
{
    return m_midllename;
}

void Sportsmen::setMidllename(const QString &newMidllename)
{
    m_midllename = newMidllename;
}

QDate Sportsmen::bornDate() const
{
    return m_bornDate;
}

void Sportsmen::setBornDate(const QDate &newBornDate)
{
    m_bornDate = newBornDate;
}

QString Sportsmen::comments() const
{
    return m_comments;
}

void Sportsmen::setComments(const QString &newComments)
{
    m_comments = newComments;
}

int Sportsmen::getBaseId() const
{
    return baseId;
}

void Sportsmen::setBaseId(int newBaseId)
{
    baseId = newBaseId;
}
