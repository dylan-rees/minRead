#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    ui->widget->setAxis(true);
    if (m_big)
    {
        QFont font1 = ui->push1->font();
        font1.setPointSize(20);
        ui->push1->setFont(font1);
        QFont font2 = ui->push2->font();
        font2.setPointSize(20);
        ui->push2->setFont(font2);
        QFont font3 = ui->push3->font();
        font3.setPointSize(20);
        ui->push3->setFont(font3);
        QFont font4 = ui->push4->font();
        font4.setPointSize(20);
        ui->push4->setFont(font4);
        QFont font5 = ui->push5->font();
        font5.setPointSize(20);
        ui->push5->setFont(font5);
        QFont font = ui->label->font();
        font.setPointSize(20);
        ui->label->setFont(font);
        ui->widget_1->setBig(m_big);
        ui->widget_2->setBig(m_big);
        ui->widget_3->setBig(m_big);
        ui->widget_4->setBig(m_big);
        ui->widget_5->setBig(m_big);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (m_tableModel != nullptr)
    {
        m_tableModel->clear();
        for (int i =m_tableModel->rowCount(); i>=0;i--)
        {
            for (int j =m_tableModel->columnCount(); j>=0;j--)
            {
                delete m_tableModel->item(i,j);
            }
        }
        delete m_tableModel;
    }
}

void MainWindow::addData(meetingHandler *allMeetings)
{
    m_allMeetings = allMeetings;
    m_start = QDate(2016,10,01);//m_allMeetings->getStart();
    m_end = QDate(2020,03,31);//m_allMeetings->getEnd();
    QMultiMap<int,QString> sorted = m_allMeetings->getSorted();
    m_tableModel = new QStandardItemModel;
    QList<QStandardItem*> row;
    QStringList tableHeader;

    QMapIterator<int, QString> iterr(sorted);

    while(iterr.hasNext())
    {
        iterr.next();
        row.append(new QStandardItem(iterr.value()));
        row.append(new QStandardItem(QString("%1").arg(iterr.key(), 3, 10, QChar('0'))));
        m_tableModel->insertRow(m_tableModel->rowCount(),row);
        row.clear();
    }
    tableHeader<<"Word"<<"Numer of\nInstances";

    m_tableModel->setHorizontalHeaderLabels(tableHeader);                             //
    ui->tableView->setModel(m_tableModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionsClickable(true);
    ui->tableView->horizontalHeader()->setSortIndicatorShown(true);
    ui->tableView->sortByColumn(1,Qt::DescendingOrder);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setEditTriggers( QAbstractItemView::NoEditTriggers );
}


void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString word = m_tableModel->index(index.row(),0).data().toString();
    if (!m_words.contains(word)&&m_words.size()<5)
    {
        m_currentWord = word;
        m_instances = m_tableModel->index(index.row(),1).data().toInt();
        QMapIterator<int, QString> iter(m_pos);
        int indx= 1;
        while(iter.hasNext())
        {
            iter.next();
            if (iter.key()==indx)
            {
                indx++;
                continue;
            }
        }
        m_words.insert(m_currentWord,indx);
        m_pos.insert(indx,m_currentWord);
        processWord(word);
        addWord(indx);
    }
}

void MainWindow::addWord(int num)
{
    switch (num)
    {
    case 1:
        ui->push1->setText(m_currentWord + " " + QString::number(m_instances));
//        ui->labelA_1->setText(QString::number(m_instances));
        ui->push1->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        ui->widget_1->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
        ui->widget_1->setPoints(m_positions);
        break;
    case 2:
        ui->push2->setText(m_currentWord + " " + QString::number(m_instances));
//        ui->labelA_2->setText(QString::number(m_instances));
        ui->push2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        ui->widget_2->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
        ui->widget_2->setPoints(m_positions);
        break;
    case 3:
        ui->push3->setText(m_currentWord + " " + QString::number(m_instances));
//        ui->labelA_3->setText(QString::number(m_instances));
        ui->push3->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        ui->widget_3->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
        ui->widget_3->setPoints(m_positions);
        break;
    case 4:
        ui->push4->setText(m_currentWord + " " + QString::number(m_instances));
//        ui->labelA_4->setText(QString::number(m_instances));
        ui->push4->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        ui->widget_4->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
        ui->widget_4->setPoints(m_positions);
        break;
    case 5:
        ui->push5->setText(m_currentWord + " " + QString::number(m_instances));
//        ui->labelA_5->setText(QString::number(m_instances));
        ui->push5->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::MinimumExpanding);
        ui->widget_5->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
        ui->widget_5->setPoints(m_positions);
        break;
    }
}

void MainWindow::on_push1_released()
{
//    ui->labelA_1->setText("");
    QStringList lst = ui->push1->text().split(" ");
    m_words.remove(lst.value(0));
    m_pos.remove(1);
    ui->push1->setText("");
    ui->widget_1->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    ui->push1->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
}

void MainWindow::on_push2_released()
{
//    ui->labelA_2->setText("");
    QStringList lst = ui->push2->text().split(" ");
    m_words.remove(lst.value(0));
    m_pos.remove(2);
    ui->push2->setText("");
    ui->widget_2->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    ui->push2->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);
}

void MainWindow::on_push3_released()
{
//    ui->labelA_3->setText("");
    QStringList lst = ui->push3->text().split(" ");
    m_words.remove(lst.value(0));
    m_pos.remove(3);
    ui->push3->setText("");
    ui->widget_3->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    ui->push3->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);

}

void MainWindow::on_push4_released()
{
//    ui->labelA_4->setText("");
    QStringList lst = ui->push4->text().split(" ");
    m_words.remove(lst.value(0));
    m_pos.remove(4);
    ui->push4->setText("");
    ui->widget_4->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    ui->push4->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);

}

void MainWindow::on_push5_released()
{
//    ui->labelA_5->setText("");
    QStringList lst = ui->push5->text().split(" ");
    m_words.remove(lst.value(0));
    m_pos.remove(5);
    ui->push5->setText("");
    ui->widget_5->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    ui->push5->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Minimum);

}

void MainWindow::processWord(QString word)
{
    QVector<QDate> dates = m_allMeetings->getDates();
    QVector<int> instances = m_allMeetings->getWord(word);
    qint64 range = m_start.daysTo(m_end);
    int maxInst = 0;
    m_positions.clear();
    for (int i=0;i<instances.size();i++)
    {
        float xPos = float(m_start.daysTo( dates.value(i) ))/float(range);
        int inst = instances.value(i);
        if (inst > maxInst)
            maxInst = inst;
        for (int j=1;j<=inst;j++)
        {
            m_positions.append(QVector2D(xPos,0.1*j));
        }
    }
    qDebug() << "Max number of instances: " << maxInst;
}
