#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileInfo>
#include <QApplication>
#include <QFileDialog>
#include <QCloseEvent>
#include <QPushButton>
#include <QMenu>
#include "mdichild.h"

MdiChild::MdiChild(QWidget *parent)
{
    //设置在子窗口关闭时销毁这个类的对象
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}

void MdiChild::newFile()
{
    static int sequenceNumber = 1;
    isUntitled = true;
    curFile = "未命名文档"+QString::number(sequenceNumber++) + ".txt";

    //如果被更改了，就要在设置了[*]号的地方显示“*”号
    setWindowTitle(curFile + "[*]" + " - 多文档编辑器");

    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documetWasModified()));
}

bool MdiChild::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
//        QMessageBox::warning(this,QString("多文档编辑器无法读取文件 "+fileName+":\n"+file.errorString()+"."));
        return false;
    }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    connect(document(),SIGNAL(contentsChanged()),this,SLOT(documetWasModified()));
    return true;
}

bool MdiChild::save()
{
    if(isUntitled){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool MdiChild::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"另存为",curFile);
    if(fileName.isEmpty()){
        return false;
    }
    return saveFile(fileName);
}

bool MdiChild::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
//        QMessageBox::warning(this,"多文档编辑器无法写入文件 %1：\n%2".arg(fileName,file.errorString()));
        return false;
    }
    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    return true;
}

QString MdiChild::userFriendlyCurrentFile()
{
    return QFileInfo(curFile).fileName();
}

void MdiChild::closeEvent(QCloseEvent *event)
{
    if(maybeSave()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MdiChild::contextMenuEvent(QContextMenuEvent *e)
{
    //创建菜单，并向其中添加动作
    QMenu *menu = new QMenu;
    QAction *undo = menu->addAction("撤销(&U)",this,SLOT(undo()),QKeySequence::Undo);
    undo->setEnabled(document()->isUndoAvailable());

    QAction *redo = menu->addAction("恢复(&R)",this,SLOT(redo()),QKeySequence::Redo);
    redo->setEnabled(document()->isRedoAvailable());
    menu->addSeparator();

    QAction *cut = menu->addAction("剪切(&T)",this,SLOT(cut()),QKeySequence::Cut);
    cut->setEnabled(textCursor().hasSelection());

    QAction *copy = menu->addAction("复制(&C)",this,SLOT(copy()),QKeySequence::Copy);
    copy->setEnabled(textCursor().hasSelection());

    menu->addAction("粘贴(&P)",this,SLOT(paste()),QKeySequence::Paste);

    QAction *clear = menu->addAction("清空",this,SLOT(clear()));
    clear->setEnabled(!document()->isEmpty());
    menu->addSeparator();

    QAction *select = menu->addAction("全选",this,SLOT(selectAll()),QKeySequence::SelectAll);
    select->setEnabled(!document()->isEmpty());

    //获取鼠标位置，然后在这个位置显示菜单
    menu->exec(e->globalPos());
    //销毁这个菜单
    delete menu;
}

void MdiChild::documetWasModified()
{
    setWindowModified(document()->isModified());
}

bool MdiChild::maybeSave()
{
    if(document()->isModified()){
        QMessageBox box;
        box.setWindowTitle("多文档编辑器");
//        box.setText("是否保存对”%1“的更改？".arg(userFriendlyCurrentFile()));
        box.setIcon(QMessageBox::Warning);
        QPushButton *yesBtn = box.addButton("是(&Y)",QMessageBox::YesRole);
        box.addButton("否(&N)",QMessageBox::NoRole);
        QPushButton *cancelBtn = box.addButton("取消",QMessageBox::RejectRole);
        box.exec();
        if(box.clickedButton() == yesBtn){
            return save();
        }else if(box.clickedButton() == cancelBtn){
            return false;
        }
    }
    return true;
}

void MdiChild::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}
