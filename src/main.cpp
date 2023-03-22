#include <QApplication>
#include "shutdown.h"
#pragma comment(lib, "user32.lib")

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    shutdown sdWidow;
    sdWidow.show();
    return a.exec();
}
