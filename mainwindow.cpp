#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstring>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("./Kursa4DB.db");

    if(!db.open())qDebug() << "ERROR" << db.lastError().text();
    else qDebug() <<"Connect!" ;
    qry = new QSqlQuery(db);

    qry->exec("CREATE TABLE UMR('ВИД РАБОТ' TEXT, ОПИСАНИЕ TEXT, ПЛАН INT(3), СРОК DATE, СТАТУС TEXT )");
    qry->exec("CREATE TABLE OMR('ВИД РАБОТ' TEXT, ОПИСАНИЕ TEXT, ПЛАН INT(3), СРОК DATE, СТАТУС TEXT)");
    qry->exec("CREATE TABLE NIR('ВИД РАБОТ' TEXT, ОПИСАНИЕ TEXT, ПЛАН INT(3), СРОК DATE, СТАТУС TEXT)");

    model = new QSqlTableModel(this,db);
    model1 = new QSqlTableModel(this,db);
    model2 = new QSqlTableModel(this,db);

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setWordWrap(true);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    ui->tableView_2->setModel(model1);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);

    ui->tableView_3->setModel(model2);
    ui->tableView_3->resizeColumnsToContents();
    ui->tableView_3->horizontalHeader()->setStretchLastSection(true);

    //подтверждение удаления
    connect(yes, &QPushButton::clicked,this, &MainWindow::yes_clicked);
    connect(no, &QPushButton::clicked,this, &MainWindow::no_clicked);
    QHBoxLayout *H_Lt = new QHBoxLayout;
    QVBoxLayout *V_Lt = new QVBoxLayout;
    QLabel *acc_Lbl = new QLabel;
    acc_Lbl->setText("Вы уверены, что хотите удалить запись?");
    yes->setText("Да");
    no->setText("Нет");
    H_Lt->addWidget(yes);
    H_Lt->addWidget(no);
    QWidget *temp_d = new QWidget;
    temp_d->setLayout(H_Lt);
    V_Lt->addWidget(acc_Lbl);
    V_Lt->addWidget(temp_d);
    acc->setLayout(V_Lt);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if (index==1)
    {
        model->setTable("UMR");
        model->select();
    }

    if (index==2)
    {
        model1->setTable("OMR");
        model1->select();
    }

    if (index==3)
    {
        model2->setTable("NIR");
        model2->select();
    }
}

//ПЕРВЫЙ ЛИСТ
void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_pushButton_2_clicked()
{
    c_del = false;
    acc->show();
}

//УДАЛЕНИЕ
void MainWindow::yes_clicked()
{
    model->removeRow(row);
    model1->removeRow(row);
    model2->removeRow(row);
    acc->close();
}

void MainWindow::no_clicked()
{
    acc->close();
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
}

void MainWindow::on_pushButton_3_clicked()
{
    model->setTable("UMR");
    model->select();
}


//ВТОРОЙ ЛИСТ
void MainWindow::on_pushButton_4_clicked()
{
    model1->insertRow(model1->rowCount());
}

void MainWindow::on_pushButton_5_clicked()
{
    c_del = false;
    acc->show();
}

void MainWindow::on_tableView_2_clicked(const QModelIndex &index)
{
    row = index.row();
}

void MainWindow::on_pushButton_6_clicked()
{
    model1->setTable("OMR");
    model1->select();
}

//ТРЕТИЙ ЛИСТ

void MainWindow::on_pushButton_7_clicked()
{
    model2->insertRow(model2->rowCount());
}

void MainWindow::on_pushButton_8_clicked()
{
    c_del = false;
    acc->show();
}

void MainWindow::on_tableView_3_clicked(const QModelIndex &index)
{
    row = index.row();
}

void MainWindow::on_pushButton_9_clicked()
{
    model2->setTable("NIR");
    model2->select();
}

void MainWindow::on_pushButton_10_clicked()
{
    QWidget::close();
}
