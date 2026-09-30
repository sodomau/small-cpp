#include <QApplication>
#include <QIcon>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Small C++");
    QCoreApplication::setApplicationVersion("0.65");
    app.setWindowIcon(QIcon(":/small/app/smallcpp.png"));
    QCoreApplication::setOrganizationName("SmallCpp");
    MainWindow window;
    window.show();
    return app.exec();
}
