#include "musicplayer.h"

#include <QApplication>
#include <QFileInfo>
#include <QSettings>
#include <QIcon>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MusicPlayer");

    MusicPlayer player;
    const QStringList arguments = QCoreApplication::arguments();
    if (arguments.size() > 1)
        player.playFile(arguments.at(1));
    player.resize(320, 60);
    player.show();

    return app.exec();
}
