#ifndef MEETING_H
#define MEETING_H

#include <QDateTime>
#include <QMap>

class meeting
{
public:
    meeting();
    meeting(QDateTime);

    void addPerson(QString name);

    void addDate(QDate date);
    void addStartTm(QTime time);
    void addEndTm(QTime time);
    void addWords(int section, QStringList words);

    QStringList discusList() const;

    QStringList progList() const;

    QStringList todoList() const;

    int duration() const;

    int getInstances(QString kWord);

    QDate getDate() const;

private:
    QDate m_date;
    QTime m_STime;
    QTime m_ETime;
    int m_duration = 0;
    QStringList m_discusList;
    QStringList m_progList;
    QStringList m_todoList;
    QVector<QString> m_people;
    bool m_processed = false;
    QMap<QString, int> m_uniqueWords;
};

#endif // MEETING_H
