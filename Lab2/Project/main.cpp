
#include <QApplication>

#include  "gui.h"
#include  "calculator.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    CalculatorGUI gui;
    gui.show();
    return app.exec();
}
