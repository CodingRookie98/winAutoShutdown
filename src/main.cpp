#include <QApplication>
#include <QTranslator>
#include <QMessageBox>
#include <QSettings>
#include "./ui/mainWindow.h"

QString GetLanguageFileName() {
    const QSettings settings("settings.ini", QSettings::IniFormat);
    const QString language = settings.value("language", "en_US").toString();
    QString language_file_name;
    if (language == "en_US") {
        language_file_name = ":/language/translations/en_US.qm";
    } else if (language == "zh_CN") {
        language_file_name = ":/language/translations/zh_CN.qm";
    }
    return language_file_name;
}

int main(int argc, char *argv[]) {
    QTranslator translator;
    QApplication a(argc, argv);
    if (translator.load(GetLanguageFileName())) {
        QApplication::installTranslator(&translator);
    } else {
        QMessageBox::warning(nullptr, "Error", "Failed to load translation file!");
        a.exit(0);
    }
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
