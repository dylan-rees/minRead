#include "meeting.h"

meeting::meeting()
{

}

void meeting::addPerson(QString name)
{
    m_people.append(name);
}

void meeting::addDate(QDate date)
{
    m_date=date;
}

void meeting::addStartTm(QTime time)
{
    m_STime = time;
}

void meeting::addEndTm(QTime time)
{
    m_ETime = time;
    m_duration = m_STime.secsTo(m_ETime)/60;
}

void meeting::addWords(int section, QStringList words)
{
    switch (section)
    {
    case 1:
        m_discusList.append(words);
        break;
    case 2:
        m_progList.append(words);
        break;
    case 3:
        m_todoList.append(words);
    }
}

QStringList meeting::discusList() const
{
    return m_discusList;
}

QStringList meeting::progList() const
{
    return m_progList;
}

QStringList meeting::todoList() const
{
    return m_todoList;
}

int meeting::duration() const
{
    return m_duration;
}

int meeting::getInstances(QString kWord)
{
    int ret = 0;
    if (m_processed)
    {
        if (m_uniqueWords.contains(kWord))
        {
            return m_uniqueWords.value(kWord);
        }
    }
    else
    {
        for (int j=0;j<m_discusList.size();j++)
        {
            QString word = m_discusList.value(j);
            if (word == "color")
                word = "colour";
            if (m_uniqueWords.contains(word))
            {
                m_uniqueWords[word]++;
            }
            else
                m_uniqueWords.insert(word,1);
        }
        for (int j=0;j<m_progList.size();j++)
        {
            QString word = m_progList.value(j);
            if (word == "color")
                word = "colour";
            if (m_uniqueWords.contains(word))
            {
                m_uniqueWords[word]++;
            }
            else
                m_uniqueWords.insert(word,1);
        }
        for (int j=0;j<m_todoList.size();j++)
        {
            QString word = m_todoList.value(j);
            if (word == "color")
                word = "colour";
            if (m_uniqueWords.contains(word))
            {
                m_uniqueWords[word]++;
            }
            else
                m_uniqueWords.insert(word,1);
        }
        m_processed = true;
        ret = this->getInstances(kWord);
    }
    return  ret;
}

QDate meeting::getDate() const
{
    return m_date;
}
