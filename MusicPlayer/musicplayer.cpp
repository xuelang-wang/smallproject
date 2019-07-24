#include <QtWidgets>
#include <QtWinExtras>
#include <QTextCodec>
#include <QFileDialog>
#include <QDesktopServices>
#include "musicplayer.h"
#include "volumebutton.h"
#include "mylrc.h"
#include "myplaylist.h"

MusicPlayer::MusicPlayer(QWidget *parent) : QWidget(parent),
    mediaPlayer(0), playButton(0)
{
    createWidgets();

    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
    connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &MusicPlayer::updateInfo);
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, this, &MusicPlayer::updateState);

    stylize();
}

void MusicPlayer::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("Open File"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("MP3 files (*.mp3);;All files (*.*)"));
    if (!filePath.isEmpty())
        playFile(filePath);
}

void MusicPlayer::playFile(const QString &filePath)
{
    // 加载歌词
    resolveLrc(filePath);

    infoLabel->setText(QFileInfo(filePath).fileName());
    mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer.play();
}

void MusicPlayer::togglePlayback()
{
    if (mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
        openFile();
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
        mediaPlayer.pause();
    else
        mediaPlayer.play();
}

void MusicPlayer::setLrcShown()
{
    if(lrc->isHidden()) {
        lrc->move(QApplication::desktop()->screenGeometry().width()/2-400,QApplication::desktop()->screenGeometry().height()-90);
        lrc->show();
    } else {
        lrc->hide();
    }
}

void MusicPlayer::setPlayListShown()
{
    if (playList->isHidden()) {
        playList->show();
    } else {
        playList->hide();
    }
}

void MusicPlayer::mousePressEvent(QMouseEvent *event)
{
    offset = event->globalPos() - pos();
    event->accept();
}

void MusicPlayer::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset);
    playList->move(event->globalPos() - offset + QPoint(0,100));
    event->accept();
}

void MusicPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    offset = QPoint();
    event->accept();
}

void MusicPlayer::updateDuration(qint64 duration)
{
    positionSlider->setRange(0,duration);
    positionSlider->setEnabled(duration>0);
    positionSlider->setPageStep(duration/10);
}

void MusicPlayer::updatePosition(qint64 position)
{
    positionSlider->setValue(position);

    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    positionLabel->setText(duration.toString(tr("mm:ss")));

    if(!lrcMap.isEmpty()) {
        // 获取当前时间在歌词中的前后两个时间点
        qint64 previous = 0;
        qint64 later = 0;
        foreach(qint64 value,lrcMap.keys()) {
            if(position >= value) {
                previous = value;
            } else {
                later = value;
                break;
            }
        }
        // 达到最后一行，将later设置为歌曲总时间的值
        if(later == 0) {
            later = positionSlider->maximum();
        }

        // 获取当前时间所对应得歌词内容
        QString currentLrc = lrcMap.value(previous);

        // 没有内容时
        if(currentLrc.length() < 1) {
            currentLrc = "…………";
        }
            // 如果是新的一行歌词，那么重新开始显示歌词遮罩
        if(currentLrc != lrc->text()) {
            lrc->setText(currentLrc);
            qint64 intervalTime = later - previous;
            lrc->startLrcMask(intervalTime);
        }
        }else {
            // 如果没有歌词文件，则在顶部标签中显示歌曲标题

        }
}

void MusicPlayer::updateInfo()
{
    QStringList info;
    QString author = mediaPlayer.metaData("Author").toString();
    if (!author.isEmpty())
        info += author;
    QString title = mediaPlayer.metaData("Title").toString();
    if (!title.isEmpty())
        info += title;
    if (!info.isEmpty())
        infoLabel->setText(info.join(tr(" - ")));
}

void MusicPlayer::stylize()
{
    if (QtWin::isCompositionEnabled()) {
        QtWin::extendFrameIntoClientArea(this, -1, -1, -1, -1);
        setAttribute(Qt::WA_TranslucentBackground, true);
        setAttribute(Qt::WA_NoSystemBackground, false);
        setStyleSheet("MusicPlayer { background: transparent; }");
    } else {
        QtWin::resetExtendedFrame(this);
        setAttribute(Qt::WA_TranslucentBackground, false);
        setStyleSheet(QString("MusicPlayer { background: %1; }").arg(QtWin::realColorizationColor().name()));
    }
    volumeButton->stylize();
}

void MusicPlayer::tableClicked(int row)
{

}

void MusicPlayer::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState) {
        playButton->setToolTip(tr("Pause"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    } else {
        playButton->setToolTip(tr("Play"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MusicPlayer::setPosition(int position)
{
    // avoid seeking when the slider value change is triggered from updatePosition()
    if (qAbs(mediaPlayer.position() - position) > 99)
        mediaPlayer.setPosition(position);
}


void MusicPlayer::createWidgets()
{
    setWindowIcon(QIcon(":/images/icon.png"));

    playButton = new QToolButton(this);
    playButton->setEnabled(true);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &MusicPlayer::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &MusicPlayer::openFile);

    QAbstractButton *lrcButton = new QToolButton(this);
    lrcButton->setStyleSheet("font:8px");
    lrcButton->setText("歌词");
    lrcButton->setToolTip(tr("显示歌词"));
    lrcButton->setFixedSize(playButton->sizeHint());
    connect(lrcButton, &QAbstractButton::clicked, this, &MusicPlayer::setLrcShown);

    QAbstractButton *listButton = new QToolButton(this);
    listButton->setStyleSheet("font:8px");
    listButton->setText("列表");
    listButton->setToolTip(tr("显示列表"));
    listButton->setFixedSize(playButton->sizeHint());
    connect(listButton, &QAbstractButton::clicked, this, &MusicPlayer::setPlayListShown);


    volumeButton = new VolumeButton(this);
    volumeButton->setToolTip(tr("Adjust volume"));
    volumeButton->setVolume(mediaPlayer.volume());
    connect(volumeButton, &VolumeButton::volumeChanged, &mediaPlayer, &QMediaPlayer::setVolume);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
    connect(positionSlider, &QAbstractSlider::valueChanged, this, &MusicPlayer::setPosition);

    infoLabel = new QLabel(this);
    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    // 布局
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(volumeButton);
    controlLayout->addWidget(lrcButton);
    controlLayout->addWidget(listButton);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(controlLayout);

    lrc = new MyLrc(this);

    playList = new MyPlayList(this);
    connect(playList,SIGNAL(cellClicked(int,int)),this,SLOT(tableClicked(int)));


}

void MusicPlayer::resolveLrc(const QString &sourceFileName)
{
    // 先清空
    lrcMap.clear();

    // 获取LRC歌词的文件名
    if(sourceFileName.isEmpty()) {
        return;
    }
    QString fileName = sourceFileName;
    QString lrcFileName = fileName.remove(fileName.right(3)) + "lrc";

    // 打开歌词文件
    QFile file(lrcFileName);
    if(!file.open(QIODevice::ReadOnly)) {
        lrc->setText("未找到歌词文件");
        return;
    }

    // 获取全部歌词信息
    QString allText = QString::fromLocal8Bit(file.readAll());
    // 关闭歌词文件
    file.close();

    // 将歌词按行分解成歌词列表
    QStringList lines = allText.split("\n");
    // 使用正则表达式将时间标签和歌词内容分离
    QRegExp rx("\\[\\d{2}:\\d{2}\\.\\d{2}\\]");
    foreach(QString oneLine,lines) {
        // 先在当前行的歌词的备份中将时间内容清楚，这样就获得了歌词文本
        QString temp = oneLine;
        temp.replace(rx,"");
        int pos = rx.indexIn(oneLine,0);
        while (pos != -1) {
            QString cap = rx.cap(0);
            // 将时间标签转换为时间数值，以毫秒为单位
            QRegExp regexp;
            regexp.setPattern("\\d{2}(?=:)");
            regexp.indexIn(cap);
            int minute = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\.)");
            regexp.indexIn(cap);
            int second = regexp.cap(0).toInt();
            regexp.setPattern("\\d{2}(?=\\])");
            regexp.indexIn(cap);
            int millisecond = regexp.cap(0).toInt();
            qint64 totalTime = minute * 60000 + second * 1000 + millisecond * 10;
            // 插入到lrcMap中
            lrcMap.insert(totalTime, temp);
            pos += rx.matchedLength();
            pos = rx.indexIn(oneLine, pos);
        }
    }
    // 如果lrcMap为空
    if (lrcMap.isEmpty()) {
        lrc->setText(tr("歌词文件内容错误！"));
        return;
    }
}
