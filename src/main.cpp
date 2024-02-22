#include <QApplication>
#include "./ui/mainWindow.h"
#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return a.exec();
}
