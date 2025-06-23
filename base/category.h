#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

class Category : public QObject
{
    Q_OBJECT
public:
    Category(QObject *parent = nullptr);
    Category(int baseId, QString name, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    QString name() const;
    void setName(const QString &newName);

private:
    int m_baseId;
    QString m_name;
};

#endif // CATEGORY_H
