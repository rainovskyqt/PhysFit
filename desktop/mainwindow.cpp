#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>
#include<QVariant>

#include "sportsmenform.h"
#include "../base/database.h"
#include "trainingform.h"
#include "resultsform.h"
#include "../base/sportsmen.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSportsmens();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_s_add_clicked()
{
    SportsmenForm *sf = new SportsmenForm(this);
    if(sf->exec() == QDialog::Rejected)
        return;

    auto sport = sf->getSportsmen();

    Database::get()->addSportsmen(sport);
    sf->deleteLater();
    loadSportsmens();
}


void MainWindow::on_btn_addTraning_clicked()
{
    auto *t = new TrainingForm(this);
    if(t->exec() == QDialog::Rejected)
        return;
}


void MainWindow::on_btn_addResult_clicked()
{
    auto *t = new ResultsForm(this);
    if(t->exec() == QDialog::Rejected)
        return;
}

void MainWindow::loadSportsmens()
{
    clearSportsmens();
    auto s = Database::get()->allSportsmens();
    for(int i = 0; i < s.count(); ++i){
        Sportsmen *sm = s.at(i);
        ui->tw_users->insertRow(i);
        QString name = QString("%1 %2 %3").arg(sm->surname(), sm->name(), sm->midllename());
        QVariant val = QVariant::fromValue<Sportsmen*>(sm);

        auto item = new QTableWidgetItem (name);
        item->setData(Qt::UserRole, val);
        ui->tw_users->setItem(i, 0, item);

        ui->cb_sportsmen->addItem(name, val);
    }
}

void MainWindow::editSportsmen(Sportsmen *s)
{
    SportsmenForm *sf = new SportsmenForm(this, s);
    if(sf->exec() == QDialog::Rejected)
        return;

    auto sport = sf->getSportsmen();

    Database::get()->editSportsmen(sport);
    loadSportsmens();
}

void MainWindow::clearSportsmens()
{
    for(int i = 0; i < ui->tw_users->rowCount(); ++i){
        QVariant variant = ui->tw_users->item(i, 0)->data(Qt::UserRole);
        Sportsmen *s = variant.value<Sportsmen*>();
        s->deleteLater();
    }
    ui->tw_users->setRowCount(0);

    ui->cb_sportsmen->clear();
    ui->cb_sportsmen->addItem("-");
}

void MainWindow::loadCategory()
{

}

void MainWindow::editCategory(Category *s)
{

}

void MainWindow::clearCategory()
{

}

void MainWindow::on_tw_users_cellDoubleClicked(int row, int column)
{
    QVariant variant = ui->tw_users->item(row, column)->data(Qt::UserRole);
    Sportsmen *s = variant.value<Sportsmen*>();
    editSportsmen(s);
}

void MainWindow::on_btn_s_edit_clicked()
{
    if(ui->tw_users->selectedItems().isEmpty())
        return;
    auto item = ui->tw_users->selectedItems().at(0);
    QVariant variant = item->data(Qt::UserRole);
    Sportsmen *s = variant.value<Sportsmen*>();
    editSportsmen(s);
}

void MainWindow::on_btn_s_delete_clicked()
{
    if(ui->tw_users->selectedItems().isEmpty())
        return;

    auto item = ui->tw_users->selectedItems().at(0);

    if(QMessageBox::question(this, tr("Удаление спортсмена"), QString(tr("Удалить %1")).arg(item->text()))
        == QMessageBox::No)
        return;

    QVariant variant = item->data(Qt::UserRole);
    Sportsmen *s = variant.value<Sportsmen*>();
    Database::get()->deleteSportsmen(s);
    loadSportsmens();
}

void MainWindow::on_btn_c_add_clicked()
{

}


void MainWindow::on_btn_c_edit_clicked()
{

}


void MainWindow::on_btn_c_delete_clicked()
{

}

