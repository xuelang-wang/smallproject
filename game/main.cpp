#include <QApplication>
#include <QSplashScreen>
#include <QTime>
#include "myview.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QPixmap pix(":/images/logo.png");
    QSplashScreen splash(pix);
    splash.resize(pix.size());
    splash.show();
    app.processEvents();
    MyView view;
    view.show();
    splash.finish(&view);

    return app.exec();
}
