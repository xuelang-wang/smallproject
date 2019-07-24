#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <QContextMenuEvent>
#include <QMenu>
#include "mylrc.h"


MyLrc::MyLrc(QWidget *partent)
{
    // 设置无框 无任务栏 置顶
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    // 设置背景透明
    setAttribute(Qt::WA_TranslucentBackground,true);
    setText("音乐播放器");

    // 固定部件大小
    setMaximumSize(800,60);
    setMinimumSize(800,60);

    // 设置位置
    move(QApplication::desktop()->screenGeometry().width()/2-400,QApplication::desktop()->screenGeometry().height()-90);

    // 歌词的线性渐变填充
    linearGradient.setStart(0,10);
    linearGradient.setFinalStop(0,40);
    linearGradient.setColorAt(0.1,QColor(14,179,255));
    linearGradient.setColorAt(0.5,QColor(114,32,255));
    linearGradient.setColorAt(0.9,QColor(14,179,255));

    // 遮罩的线性渐变填充
    maskLinearGrandient.setStart(0,10);
    maskLinearGrandient.setFinalStop(0,40);
    maskLinearGrandient.setColorAt(0.1,QColor(222,54,4));
    maskLinearGrandient.setColorAt(0.5,QColor(255,72,16));
    maskLinearGrandient.setColorAt(0.9,QColor(222,54,4));

    // 设置字体
    font.setFamily("Times New Roman");
    font.setBold(true);
    font.setPointSize(30);

    // 设置定时器
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&MyLrc::timeout);
    lrcMaskWidth = 0;
    lrcMaskWidthInterval = 0;

    show();
}

void MyLrc::startLrcMask(qint64 intervalTime)
{
    // 这里设置每隔30毫秒更新一个遮罩的宽度，因为如果更新太频繁
    // 会增加CPU占用率，而如果时间间隔太大，则动画效果就不流畅
    qreal count = intervalTime/30;

    // 获取遮罩每次需要增加的宽度，这里的800是部件的固定宽度
    lrcMaskWidthInterval = 800/count;
    lrcMaskWidth = 0;
    timer->start(30);
}

void MyLrc::stopLrcMask()
{
    timer->stop();
    lrcMaskWidth = 0;
    update();
}

void MyLrc::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setFont(font);

    // 先绘制底层文字，作为阴影，这样会使显示效果更清晰，且更有质感
    painter.setPen(QColor(0,0,0,200));
    painter.drawText(1,1,800,60,Qt::AlignCenter,text());

    // 再在上面绘制渐变文字
    painter.setPen(QPen(linearGradient,0));
    painter.drawText(0,0,800,60,Qt::AlignCenter,text());

    // 设置歌词遮罩
    painter.setPen(QPen(maskLinearGrandient,0));
    painter.drawText(0,0,lrcMaskWidth,60,Qt::AlignCenter,text());
}

void MyLrc::mousePressEvent(QMouseEvent *event)
{
    offset = event->globalPos() - pos();
    event->accept();
}

void MyLrc::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset);
    event->accept();
}

// 实现右键菜单来隐藏部件
void MyLrc::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction("隐藏",this,&hide);
    menu.exec(event->globalPos());
}

void MyLrc::timeout()
{
    lrcMaskWidth += lrcMaskWidthInterval;
    update();   // 调用paintEvent
}
