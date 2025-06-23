#include "category.h"

Category::Category(QObject *parent) : QObject(parent)
{}

Category::Category(int baseId, QString name, QObject *parent) : QObject(parent)
{
    setBaseId(baseId);
    setName(name);
}

int Category::baseId() const
{
    return m_baseId;
}

void Category::setBaseId(int newBaseId)
{
    m_baseId = newBaseId;
}

QString Category::name() const
{
    return m_name;
}

void Category::setName(const QString &newName)
{
    m_name = newName;
}
