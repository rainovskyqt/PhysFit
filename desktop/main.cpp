#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QMessageBox>

#include "../base/database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!Database::get()->init("10.0.2.18", 3306)){
        QMessageBox::critical(nullptr, "Ошибка базы", "При открытии базы данных произошла ошибка:\n" +
                                                          Database::get()->lastError());
        return 0;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "desktop_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.show();
    return a.exec();
}
