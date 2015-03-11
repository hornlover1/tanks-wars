#include "mainwindow.h"
#include <QApplication>
#include <vector>
#include <string>
#include "unittests.h"
using namespace std;

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    vector<string> args(&argv[0], &argv[argc]);
    for (string s: args) {
        if (s == "-test") {
            runUnitTests();
        }
    }

    return a.exec();
}
