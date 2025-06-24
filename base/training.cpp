#include "training.h"

Training::Training(QObject *parent)
    : QObject{parent}
{}

Training::Training(const QDate date, const QString &name, const QString &comments, int sportsmenId, int baseId, QObject *parent) : QObject{parent}
{
    setName(name);
    setDate(date);
    setComments(comments);
    setBaseId(baseId);
    setSportsmenId(sportsmenId);
}

int Training::baseId() const
{
    return m_baseId;
}

void Training::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

QDate Training::date() const
{
    return m_date;
}

void Training::setDate(const QDate &newDate)
{
    m_date = newDate;
}

QString Training::name() const
{
    return m_name;
}

void Training::setName(const QString &newName)
{
    m_name = newName;
}

QString Training::comments() const
{
    return m_comments;
}

void Training::setComments(const QString &newComments)
{
    m_comments = newComments;
}

int Training::sportsmenId() const
{
    return m_sportsmenId;
}

void Training::setSportsmenId(int newSportsmenId)
{
    m_sportsmenId = newSportsmenId;
}
