//Driver function

#include <QApplication>
#include "../headers/addremtag.h"
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);

    QApplication::setStyle("plastique");
    QApplication *app = new QApplication(argc,argv);
    //app->setWindowIcon(QIcon(":/files/files/ws_creations.png"));

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap(":/files/resources/ws_creations.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."),topRight, Qt::black);
    splash->showMessage(QObject::tr("Loading modules..."),topRight, Qt::black);

    AddRemTag sd;
    sd.show();

    splash->finish(&sd);
    delete splash;

    return app->exec();
}
