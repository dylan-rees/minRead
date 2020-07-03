#include "meetinghandler.h"

meetingHandler::meetingHandler()
{

}

void meetingHandler::addMeetings(QVector<meeting> allMeetings)
{
    m_allMeetings = allMeetings;
    process();
}

void meetingHandler::addNames(QHash<QString, int> uniquePpl)
{
    m_uniquePpl = uniquePpl;
}

void meetingHandler::addNames(QStringList *people)
{
    for (int i=0;i<people->size();i++)
        m_people.append(people->value(i));
}

void meetingHandler::process()
{
    int totalDuration = 0;
    QMap<QString, int> uniqueWords;
    for (int i=0;i<m_allMeetings.size();i++)
    {
        QStringList discus = m_allMeetings[i].discusList();
        QStringList prog = m_allMeetings[i].progList();
        QStringList todo = m_allMeetings[i].todoList();
        for (int j=0;j<discus.size();j++)
        {
            QString word = discus.value(j);
            if (word == "color")
                word = "colour";
            if (uniqueWords.contains(word))
            {
                uniqueWords[word]++;
            }
            else
                uniqueWords.insert(word,1);
        }
        for (int j=0;j<prog.size();j++)
        {
            QString word = prog.value(j);
            if (word == "color")
                word = "colour";
            if (uniqueWords.contains(word))
            {
                uniqueWords[word]++;
            }
            else
                uniqueWords.insert(word,1);
        }
        for (int j=0;j<todo.size();j++)
        {
            QString word = todo.value(j);
            if (word == "color")
                word = "colour";
            if (uniqueWords.contains(word))
            {
                uniqueWords[word]++;
            }
            else
                uniqueWords.insert(word,1);
        }
        totalDuration += m_allMeetings[i].duration();
    }
    QMapIterator<QString, int> iter(uniqueWords);
    while(iter.hasNext())
    {
        iter.next();
        if (!m_stopWords.contains(iter.key(),Qt::CaseSensitive)&&!m_stopWords2.contains(iter.key(),Qt::CaseSensitive)&&!m_uniquePpl.contains(iter.key()))
            m_sorted.insert(iter.value(),iter.key());
    }
    QMapIterator<int, QString> iterr(m_sorted);
//    QString filename = "Data10.txt";
//    QFile file(filename);
//    file.open(QIODevice::WriteOnly | QIODevice::Text);
//    QTextStream stream(&file);
    while(iterr.hasNext())
    {
        iterr.next();
        qDebug() << iterr.value()<<iterr.key();
//        for (int i=0;i<iterr.key();i++)
//            stream << iterr.value() << " ";
//        stream << endl;
    }
//    file.close();
    m_totalTime= totalDuration;
    qDebug() << "Total Meeting Duration: " << totalDuration;
}

QVector<int> meetingHandler::getWord(QString kWord)
{
    QVector<int> words;
    for (int i=0;i<m_allMeetings.size();i++)
    {
        words.append(m_allMeetings.value(i).getInstances(kWord));
    }
    return words;
}

QVector<QDate> meetingHandler::getDates()
{
    QVector<QDate> dates;
    for (int i=0;i<m_allMeetings.size();i++)
    {
        dates.append(m_allMeetings.value(i).getDate());
    }
    return dates;
}

QMultiMap<int, QString> meetingHandler::getSorted() const
{
    return m_sorted;
}

QDate meetingHandler::getStart()
{
    return m_allMeetings.value(0).getDate();
}

QDate meetingHandler::getEnd()
{
    QDate date;
    int indx = m_allMeetings.size()-1;
    if (indx>1)
        return m_allMeetings.value(indx).getDate();
    return date;
}

void meetingHandler::setSorted(const QMultiMap<int, QString> &sorted)
{
    m_sorted = sorted;
}
