#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QSystemTrayIcon>


QT_FORWARD_DECLARE_CLASS(QLabel)
QT_FORWARD_DECLARE_CLASS(QSlider)
QT_FORWARD_DECLARE_CLASS(QAbstractButton)
class VolumeButton;
class MyLrc;
class MyPlayList;

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    explicit MusicPlayer(QWidget *parent = 0);

public slots:
    void openFile();
    void playFile(const QString& filePath);
    void togglePlayback();
    void setLrcShown();
    void setPlayListShown();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void updateState(QMediaPlayer::State state);
    void setPosition(int position);
    void updateDuration(qint64 duration);
    void updatePosition(qint64 position);
    void updateInfo();
    void stylize();
    void tableClicked(int row);

private:
    void createWidgets();

    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    VolumeButton *volumeButton;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *infoLabel;
    QSystemTrayIcon *trayIcon;
    QPoint offset;

    MyLrc *lrc;
    QMap<qint64,QString> lrcMap;
    void resolveLrc(const QString &sourceFileName);

    MyPlayList *playList;
//    QMediaPlayer *mediaListInfo;



};

#endif // MUSICPLAYER_H
