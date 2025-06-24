#include "category.h"

Category::Category(QObject *parent) : QObject(parent)
{}

Category::Category(QString name, int baseId, QObject *parent) : QObject(parent)
{
    setName(name);
    setBaseId(baseId);
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
