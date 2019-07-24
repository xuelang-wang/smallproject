#ifndef MYPLAYLIST_H
#define MYPLAYLIST_H

#include <QTableWidget>

class MyPlayList : public QTableWidget
{
    Q_OBJECT
public:
    explicit MyPlayList(QWidget *parent = 0);
protected:
    void contextMenuEvent(QContextMenuEvent *event);
    void closeEvent(QCloseEvent *event);
signals:
    void playlistClean();
private slots:
    void clearPlaylist();
private:
    void stylize();
};

#endif // MYPLAYLIST_H
