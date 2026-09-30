#include <QApplication>
#include <QIcon>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Small C++");
    QCoreApplication::setApplicationVersion(SMALL_IDE_VERSION);
    app.setWindowIcon(QIcon(":/small/app/smallcpp.png"));
    QCoreApplication::setOrganizationName("SmallCpp");
    MainWindow window;
    window.show();
    return app.exec();
}
