#include <QContextMenuEvent>
#include <QMenu>
#include <QtWinExtras>
#include "myplaylist.h"

MyPlayList::MyPlayList(QWidget *parent):
    QTableWidget(parent)
{
    setWindowTitle("播放列表");
    // 设置窗口标志，表明它是一个独立窗口且有一个只带有关闭按钮的标题栏
    setWindowFlags(Qt::Window | Qt::WindowTitleHint);

    // 设置初始大小，并且锁定部件宽度
    resize(320,400);
    setMaximumWidth(320);
    setMinimumWidth(320);

    // 设置行列数目数
    setRowCount(0);
    setColumnCount(3);

    // 设置表头便签
    QStringList list;
    list << "标题" << "艺术家" << "长度";
    setHorizontalHeaderLabels(list);

    // 设置只能选择单行
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);

    // 设置不显示网格
    setShowGrid(false);

    stylize();
    show();
}

// 上下文菜单事件处理函数，当点击鼠标右键时运行一个菜单
void MyPlayList::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction("清空列表",this,SLOT(clearPlaylist()));
    menu.exec(event->globalPos());
}

// 关闭事件处理函数，如果部件处于显示状态，则使其隐藏
void MyPlayList::closeEvent(QCloseEvent *event)
{
    if (isVisible()) {
        hide();
        event->ignore();
    }
}

void MyPlayList::clearPlaylist()
{
    while (rowCount()) {
        removeRow(0);
    }
    // 发射播放列表以清空信号
    emit playlistClean();
}

void MyPlayList::stylize()
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
}

