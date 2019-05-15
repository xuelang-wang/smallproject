#ifndef MDICHILD_H
#define MDICHILD_H
#include <QTextEdit>
#include <QWidget>

class MdiChild : public QTextEdit
{
    Q_OBJECT
public:
    explicit MdiChild(QWidget *parent = 0);
    void newFile();
    bool loadFile(const QString &fileName);
    bool save();
    bool saveAs();
    bool saveFile(const QString &fileName);
    QString userFriendlyCurrentFile();
    QString currentFile()
    {
        return curFile;
    }

protected:
    void closeEvent(QCloseEvent *event);
    void contextMenuEvent(QContextMenuEvent *e);//右键菜单事件

private slots:
    void documetWasModified();              //文档被改时，窗口显示更改状态标志

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    QString curFile;                        //保存当前文件路径
    bool isUntitled;                        //作为当前文件是否被保存到硬盘上的标志
};

#endif // MDICHILD_H
