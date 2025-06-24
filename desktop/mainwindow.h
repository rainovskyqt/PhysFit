#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QListWidgetItem>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Sportsmen;
class Category;
class Exercise;
class Training;
class Result;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_s_add_clicked();
    void on_btn_addTraning_clicked();
    void on_btn_addResult_clicked();
    void on_tw_users_cellDoubleClicked(int row, int column);
    void on_btn_s_edit_clicked();
    void on_btn_s_delete_clicked();
    void on_btn_c_add_clicked();
    void on_btn_c_edit_clicked();
    void on_btn_c_delete_clicked();
    void on_tw_category_cellDoubleClicked(int row, int column);
    void on_tw_exercise_cellDoubleClicked(int row, int column);
    void on_btn_e_add_clicked();
    void on_btn_e_edit_clicked();
    void on_btn_e_delete_clicked();
    void on_cb_sportsmen_currentIndexChanged(int index);
    void on_lw_tranings_itemDoubleClicked(QListWidgetItem *item);
    void on_btn_editTraning_clicked();
    void on_btn_deleteTraning_clicked();
    void on_btn_editResult_clicked();
    void on_btn_deleteResult_clicked();
    void on_lw_tranings_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

private:
    Ui::MainWindow *ui;

    void loadSportsmens();
    void editSportsmen(Sportsmen *s);
    void clearSportsmens();

    void loadCategory();
    void editCategory(Category *s);
    void clearCategory();

    void loadExercise();
    void editExercise(Exercise *e);
    void clearExercise();

    void loadTrainings(int sportsmenId);
    void editTraining(Training *e);
    void clearTrainings();

    void loadResult(int trainingId);
    void editResult(Result *e);
    void clearResult();

};
#endif // MAINWINDOW_H
