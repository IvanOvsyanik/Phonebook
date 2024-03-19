#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../Phonebook/Database/Members");
    if(db.open())
    {
        ui->statusbar->showMessage("You have successfully opened the phone book.");

        model = new QSqlTableModel(this,db);
        model->setTable("Members");
        model->select();

        ui->tableView->setModel(model);
        ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setSortingEnabled(true);
    }
    else
    {
        ui->statusbar->showMessage("An error occurred when opening the phone book: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    db.close();
    delete ui;
}


void MainWindow::on_btnAdd_clicked()
{
    model->insertRow(model->rowCount());
}


void MainWindow::on_btnRemove_clicked()
{
    model->removeRow(currentRow);
    model->select();
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
    ui->statusbar->clearMessage();
}


void MainWindow::on_btnRefresh_clicked()
{
    model->setFilter("");
    model->select();
    ui->tableView->selectRow(currentRow);
}


void MainWindow::on_btnSearch_clicked()
{
    QString Data = ui->enterData->toPlainText();
    QString filter = "";
    if(!Data.isEmpty())
    {
        filter = "Firstname LIKE '%" + Data + "' OR "
                 "Lastname LIKE '%" + Data + "' OR "
                 "Number LIKE '%" + Data + "' OR "
                 "\"Male/Fimale\" LIKE '" + Data + "'";
    }
    model->setFilter(filter);
    model->select();
}

