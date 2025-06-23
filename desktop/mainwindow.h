#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Sportsmen;
class Category;

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

private:
    Ui::MainWindow *ui;

    void loadSportsmens();
    void editSportsmen(Sportsmen *s);
    void clearSportsmens();

    void loadCategory();
    void editCategory(Category *s);
    void clearCategory();

};
#endif // MAINWINDOW_H
