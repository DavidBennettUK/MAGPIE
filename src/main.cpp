#include <QtGui/QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QStyle>
#include "windows/WorkspaceWindow.h"
#include "gp/Generation.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("David Bennett");
    QCoreApplication::setOrganizationDomain("http://www.codevate.com");
    QCoreApplication::setApplicationName("MAGPIE");

    QApplication::setStyle("Cleanlooks");
    a.setPalette(QApplication::style()->standardPalette());

    qRegisterMetaType<QSharedPointer<Generation> >("QSharedPointer<Generation>");

    QPixmap imgSplash(":/resources/splash.png");
    QSplashScreen splash(imgSplash);
    splash.show();

    WorkspaceWindow workspaceWindow;

    QTimer::singleShot(2000, &splash, SLOT(close()));
    QTimer::singleShot(2000, &workspaceWindow, SLOT(showMaximized()));
    QTimer::singleShot(3000, &workspaceWindow, SLOT(lessonSelect()));

    return a.exec();
}
