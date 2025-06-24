#include "exercise.h"

Exercise::Exercise(QObject *parent)
    : QObject{parent}
{}

Exercise::Exercise(QString name, int baseId, QObject *parent) : QObject{parent}
{
    setName(name);
    setBaseId(baseId);
}

int Exercise::baseId() const
{
    return m_baseId;
}

void Exercise::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

QString Exercise::name() const
{
    return m_name;
}

void Exercise::setName(const QString &newName)
{
    m_name = newName;
}
