#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include<QVariant>
#include <QDebug>

#include "sportsmenform.h"
#include "../base/database.h"
#include "trainingform.h"
#include "resultsform.h"
#include "../base/sportsmen.h"
#include "../base/training.h"
#include "../base/result.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSportsmens();
    loadCategory();
    loadExercise();

    ui->btn_editResult->setVisible(false);
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
    sport->deleteLater();
    loadSportsmens();
}


void MainWindow::on_btn_addTraning_clicked()
{
    if(ui->cb_sportsmen->currentIndex() == 0)
        return;

    int sId = ui->cb_sportsmen->currentData(Qt::UserRole).toInt();
    auto *t = new TrainingForm(this);
    t->setSportsmenId(sId);
    if(t->exec() == QDialog::Rejected)
        return;

    auto tr = t->getTraining();

    Database::get()->addTraining(tr);
    tr->deleteLater();
    loadTrainings(sId);
}


void MainWindow::on_btn_addResult_clicked()
{
    if(ui->lw_tranings->currentItem() == nullptr)
        return;

    int tId = ui->lw_tranings->currentItem()->data(Qt::UserRole).value<Training*>()->baseId();
    auto *r = new ResultsForm(this);
    r->setTrainingId(tId);
    if(r->exec() == QDialog::Rejected)
        return;

    auto rr = r->getResult();

    Database::get()->addResult(rr);
    rr->deleteLater();
    loadResult(tId);
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

        ui->cb_sportsmen->addItem(name, sm->getBaseId());
    }
}

void MainWindow::editSportsmen(Sportsmen *s)
{
    SportsmenForm *sf = new SportsmenForm(this, s);
    if(sf->exec() == QDialog::Rejected)
        return;

    auto sport = sf->getSportsmen();

    Database::get()->editSportsmen(sport);
    sport->deleteLater();
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
    clearCategory();
    auto cl = Database::get()->allCategory();
    for(int i = 0; i < cl.count(); ++i){
        Category *c = cl.at(i);
        ui->tw_category->insertRow(i);
        QString name = QString("%1").arg(c->name());
        QVariant val = QVariant::fromValue<int>(c->baseId());

        auto item = new QTableWidgetItem (name);
        item->setData(Qt::UserRole, val);
        ui->tw_category->setItem(i, 0, item);
    }
}

void MainWindow::editCategory(Category *c)
{
    QString category = QInputDialog::getText(this, tr("Редактирование"), tr("Новое название категории"), QLineEdit::Normal, c->name());
    if(!category.isEmpty()){
        c->setName(category);
        Database::get()->editCategory(c);
    }

    c->deleteLater();
    loadCategory();
}

void MainWindow::clearCategory()
{
    ui->tw_category->setRowCount(0);
}

void MainWindow::loadExercise()
{
    clearExercise();
    auto el = Database::get()->allExercise();
    for(int i = 0; i < el.count(); ++i){
        Exercise *e = el.at(i);
        ui->tw_exercise->insertRow(i);
        QString name = QString("%1").arg(e->name());
        QVariant val = QVariant::fromValue<int>(e->baseId());

        auto item = new QTableWidgetItem (name);
        item->setData(Qt::UserRole, val);
        ui->tw_exercise->setItem(i, 0, item);
    }
}

void MainWindow::editExercise(Exercise *e)
{
    QString exercise = QInputDialog::getText(this, tr("Редактирование"), tr("Новое название упражнения"), QLineEdit::Normal, e->name());
    if(!exercise.isEmpty()){
        e->setName(exercise);
        Database::get()->editExercise(e);
    }

    e->deleteLater();
    loadExercise();
}

void MainWindow::clearExercise()
{
    ui->tw_exercise->setRowCount(0);
}

void MainWindow::loadTrainings(int sportsmenId)
{
    clearTrainings();
    auto tl = Database::get()->trainings(sportsmenId);
    for(int i = 0; i < tl.count(); ++i){
        Training *t = tl.at(i);
        QString name = QString("%1: %2").arg(t->date().toString("dd.MM.yyyy"), t->name());
        QVariant val = QVariant::fromValue<Training*>(t);

        QListWidgetItem *item = new QListWidgetItem(name);
        item->setData(Qt::UserRole, val);
        ui->lw_tranings->addItem(item);
    }
}

void MainWindow::editTraining(Training *e)
{
    TrainingForm *tf = new TrainingForm(this, e);
    if(tf->exec() == QDialog::Rejected)
        return;

    auto training = tf->getTraining();

    Database::get()->editTraining(training);
    loadTrainings(training->sportsmenId());
    training->deleteLater();
}

void MainWindow::clearTrainings()
{
    ui->lw_tranings->clear();
}

void MainWindow::loadResult(int trainingId)
{
    clearResult();
    auto rl = Database::get()->results(trainingId);
    for(int i = 0; i < rl.count(); ++i){
        ui->tw_results->insertRow(i);
        Result *r = rl.at(i);
        QString name = QString("%1: %2, состояние: %3").arg(r->exerciseName(), r->result()).arg(r->status());
        QVariant val = QVariant::fromValue<Result*>(r);

        QTableWidgetItem *item = new QTableWidgetItem(name);
        item->setData(Qt::UserRole, val);
        ui->tw_results->setItem(i, 0, item);
    }
}

void MainWindow::editResult(Result *e)
{

}

void MainWindow::clearResult()
{
    for(int i = 0; i < ui->tw_results->rowCount(); ++i){
        QVariant variant = ui->tw_results->item(i, 0)->data(Qt::UserRole);
        Result *s = variant.value<Result*>();
        s->deleteLater();
    }
    ui->tw_results->setRowCount(0);
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

    if(QMessageBox::question(this, tr("Удаление спортсмена"), QString(tr("Удалить %1?")).arg(item->text()))
        == QMessageBox::No)
        return;

    QVariant variant = item->data(Qt::UserRole);
    Sportsmen *s = variant.value<Sportsmen*>();
    Database::get()->deleteSportsmen(s);
    loadSportsmens();
}

void MainWindow::on_btn_c_add_clicked()
{
    QString category = QInputDialog::getText(this, tr("Новая категория"), tr("Введите название новой категории"));
    if(category.isEmpty())
        return;

    auto c = new Category(category);

    Database::get()->addCategory(c);
    c->deleteLater();
    loadCategory();
}


void MainWindow::on_btn_c_edit_clicked()
{
    if(ui->tw_category->selectedItems().isEmpty())
        return;

    auto item = ui->tw_category->selectedItems().at(0);
    auto c = new Category(item->text(), item->data(Qt::UserRole).toInt());
    editCategory(c);
}


void MainWindow::on_btn_c_delete_clicked()
{
    if(ui->tw_category->selectedItems().isEmpty())
        return;

    auto item = ui->tw_category->selectedItems().at(0);

    if(QMessageBox::question(this, tr("Удаление категории"), QString(tr("Удалить %1?")).arg(item->text()))
        == QMessageBox::No)
        return;

    auto c = new Category(item->text(), item->data(Qt::UserRole).toInt());
    Database::get()->deleteCategory(c);
    c->deleteLater();
    loadCategory();
}


void MainWindow::on_tw_category_cellDoubleClicked(int row, int column)
{
    auto item = ui->tw_category->item(row, column);
    auto c = new Category(item->text(), item->data(Qt::UserRole).toInt());
    editCategory(c);
}


void MainWindow::on_tw_exercise_cellDoubleClicked(int row, int column)
{
    auto item = ui->tw_exercise->item(row, column);
    auto e = new Exercise(item->text(), item->data(Qt::UserRole).toInt());
    editExercise(e);
    e->deleteLater();
}


void MainWindow::on_btn_e_add_clicked()
{
    QString category = QInputDialog::getText(this, tr("Новая категория"), tr("Введите название нового упражнения"));
    if(category.isEmpty())
        return;

    auto e = new Exercise(category);

    Database::get()->addExercise(e);
    e->deleteLater();
    loadExercise();
}


void MainWindow::on_btn_e_edit_clicked()
{
    if(ui->tw_exercise->selectedItems().isEmpty())
        return;

    auto item = ui->tw_exercise->selectedItems().at(0);
    auto e = new Exercise(item->text(), item->data(Qt::UserRole).toInt());
    editExercise(e);
}


void MainWindow::on_btn_e_delete_clicked()
{
    if(ui->tw_exercise->selectedItems().isEmpty())
        return;

    auto item = ui->tw_exercise->selectedItems().at(0);

    if(QMessageBox::question(this, tr("Удаление упражнения"), QString(tr("Удалить %1?")).arg(item->text()))
        == QMessageBox::No)
        return;

    auto e = new Exercise(item->text(), item->data(Qt::UserRole).toInt());
    Database::get()->deleteExercise(e);
    e->deleteLater();
    loadExercise();
}


void MainWindow::on_cb_sportsmen_currentIndexChanged(int index)
{
    auto id = ui->cb_sportsmen->itemData(index, Qt::UserRole).toInt();
    loadTrainings(id);
}


void MainWindow::on_lw_tranings_itemDoubleClicked(QListWidgetItem *item)
{
    QVariant variant = item->data(Qt::UserRole);
    Training *s = variant.value<Training*>();
    editTraining(s);
}


void MainWindow::on_btn_editTraning_clicked()
{
    if(ui->lw_tranings->currentItem() == nullptr)
        return;

    auto item = ui->lw_tranings->currentItem();
    QVariant variant = item->data(Qt::UserRole);
    Training *t = variant.value<Training*>();
    editTraining(t);
}


void MainWindow::on_btn_deleteTraning_clicked()
{
    if(ui->lw_tranings->currentItem() == nullptr)
        return;

    auto item = ui->lw_tranings->currentItem();

    if(QMessageBox::question(this, tr("Удаление тренировки"), QString(tr("Удалить тренировку %1?")).arg(item->text()))
        == QMessageBox::No)
        return;

    QVariant variant = item->data(Qt::UserRole);
    Training *t = variant.value<Training*>();
    Database::get()->deleteTraining(t);
    loadTrainings(t->sportsmenId());
}

void MainWindow::on_btn_editResult_clicked()
{
    
}

void MainWindow::on_btn_deleteResult_clicked()
{
    if(ui->tw_results->selectedItems().isEmpty())
        return;

    auto item = ui->tw_results->selectedItems().at(0);

    if(QMessageBox::question(this, tr("Удаление результата"), QString(tr("Удалить результата упражнения %1?")).arg(item->text()))
        == QMessageBox::No)
        return;

    QVariant variant = item->data(Qt::UserRole);
    Result *r = variant.value<Result*>();
    Database::get()->deleteResult(r);
    loadResult(r->trainingId());
}


void MainWindow::on_lw_tranings_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    Q_UNUSED(previous)
    if(current == nullptr)
        return;

    QVariant variant = current->data(Qt::UserRole);
    Training *t = variant.value<Training*>();
    loadResult(t->baseId());
}
