#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>
#include <QDebug>
#include <QRegularExpression>
#include "meeting.h"
#include "meetinghandler.h"


int monthParser(QString month)
{
    if (month=="jan"||month=="Jan"||month=="january"||month=="January")
        return 1;
    else if (month=="feb"||month=="Feb"||month=="february"||month=="February")
        return 2;
    else if (month=="mar"||month=="Mar"||month=="March"||month=="march")
        return 3;
    else if (month=="apr"||month=="Apr"||month=="april"||month=="April")
        return 4;
    else if (month=="may"||month=="May")
        return 5;
    else if (month=="jun"||month=="Jun"||month=="june"||month=="June")
        return 6;
    else if (month=="jul"||month=="Jul"||month=="july"||month=="July")
        return 7;
    else if (month=="aug"||month=="Aug"||month=="august"||month=="August")
        return 8;
    else if (month=="sep"||month=="Sep"||month=="september"||month=="September")
        return 9;
    else if (month=="oct"||month=="Oct"||month=="october"||month=="October")
        return 10;
    else if (month=="nov"||month=="Nov"||month=="november"||month=="November")
        return 11;
    else if (month=="dec"||month=="Dec"||month=="december"||month=="December")
        return 12;
    else
        return 0;
}

void loadFile(meetingHandler *allMeetings)
{
    QVector<meeting> meetings;
    QHash<QString, int> uniquePpl;
    int noMeets = 143;
    QString fileName = "/home/dylan/Desktop/Minutes/Minutes";
    for (int nu=1;nu<noMeets+1;nu++)
    {
        QString numb = QString("%1").arg(nu);
        QFile loadFile(QString(fileName+numb+".txt"));
        if (!loadFile.open(QIODevice::ReadOnly))
        {
            qDebug() << "File not open";
            return;
        }
    //    QByteArray saveData = loadFile.readAll();
        QTextStream instream(&loadFile);
        meeting meet;
    //    QString line = instream.readLine();
        int lineNo =0;
        int section = 0;
        while(!instream.atEnd())
        {
            QString line = instream.readLine();
            QStringList lst = line.split(":");
            if (lst.size()>1)
            {
                QStringList names = lst.value(1).split(QRegularExpression("\\W+"), QString::SkipEmptyParts);
                if (lineNo ==0)
                {
                    for (int i=0;i<names.size();i++)
                    {
                        QString name = names.value(i);
                        if (name!="Skype"&&name!="skype"&&name!="via")
                        {
                            if (name=="Richard")
                                name = "Rich";
                            meet.addPerson(name);
                            if (uniquePpl.contains(name))
                                uniquePpl[name]++;
                            else
                                uniquePpl.insert(name,1);
                        }
                    }
                }
                if (lineNo ==2)
                {
                    int day = names.value(0).toInt();
                    int month = monthParser(names.value(1));
                    int year = names.value(2).toInt();
                    QDate date(year,month,day);
                    meet.addDate(date);
                }
                if (lineNo ==3)
                {
                    int hour = lst.value(1).toInt();
                    int min = lst.value(2).toInt();
                    QTime startTm(hour,min);
                    meet.addStartTm(startTm);
                }
                if (lineNo ==4)
                {
                    int hour = lst.value(1).toInt();
                    int min = lst.value(2).toInt();
                    QTime endTm(hour,min);
                    meet.addEndTm(endTm);
                }
            }
            if (line =="Topics Discussed:")
                section = 1;
            else if (line =="Progress:"||line =="Progress since last meeting:")
                section = 2;
            else if (line =="To do:"||line=="Todo"||line=="Todo:")
                section = 3;
            else
            {
                if(section>0)
                {
                    QStringList words = line.split(QRegularExpression("\\W+"), QString::SkipEmptyParts);
                    meet.addWords(section, words);
                }
            }
            lineNo++;
        }
    //    qDebug() << "first line: " << line;
        loadFile.close();
        meetings.append(meet);
    }
    QStringList people;
    QHashIterator<QString, int> iter(uniquePpl);
    while(iter.hasNext())
    {
        iter.next();
        people.append(iter.key());
        qDebug() << iter.key() << " : " << iter.value();
    }
    allMeetings->addNames(uniquePpl);
    allMeetings->addMeetings(meetings);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    meetingHandler allMeetings;
    loadFile(&allMeetings);
    w.addData(&allMeetings);
    w.show();
    w.showMaximized();
    w.setWindowTitle("Minute Analysis");
    return a.exec();
}
