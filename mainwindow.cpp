#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    }
    else
    {
        ui->statusbar->showMessage("An error occurred when opening the phone book: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
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
}

