#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDate>
#include <QVector2D>
#include "meetinghandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addData(meetingHandler *allMeetings);

private slots:
    void on_tableView_doubleClicked(const QModelIndex &index);

    void addWord(int num);

    void on_push1_released();

    void on_push2_released();

    void on_push3_released();

    void on_push4_released();

    void on_push5_released();

    void processWord(QString word);

private:
    Ui::MainWindow *ui;

    meetingHandler *m_allMeetings;
    QStandardItemModel *m_tableModel = nullptr;

    QHash<QString, int> m_words;
    QMap<int, QString> m_pos;
    QVector<QVector2D> m_positions;
    QString m_currentWord = nullptr;
    int m_instances = 0;
    QDate m_start;
    QDate m_end;

    bool m_big = false;
};
#endif // MAINWINDOW_H
