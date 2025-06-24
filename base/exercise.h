#ifndef EXERCISE_H
#define EXERCISE_H

#include <QObject>

class Exercise : public QObject
{
    Q_OBJECT
public:
    explicit Exercise(QObject *parent = nullptr);
    Exercise(QString name, int baseId = 0, QObject *parent = nullptr);

    int baseId() const;
    void setBaseId(int newBaseId);
    QString name() const;
    void setName(const QString &newName);

private:
    int m_baseId;
    QString m_name;
};

#endif // EXERCISE_H
