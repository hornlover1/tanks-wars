#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <string>
#include "unittests.h"
#include "interface.h"

using namespace std;

int main(int argc, char *argv[]) {

    QApplication a(argc, argv);
    MainWindow w;

    vector<string> args(&argv[0], &argv[argc]);
    for (string s: args) {
        if (s == "-test") {
            runUnitTests();
        }
    }

    Interface::getInstance().blankUI();

    w.show();

    return a.exec();
}
