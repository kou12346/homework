#include "mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QClipboard>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    connect(actionClose,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(actionSave,SIGNAL(triggered(bool)),this,SLOT(saveFile()));
    connect(actionCopy,SIGNAL(triggered(bool)),this,SLOT(copy()));
}

MainWindow::~MainWindow() {}
void MainWindow::saveFile()
{
    QString text = textEdit->toPlainText();
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (fileName.isEmpty()) {
        return; // 若使用者取消，直接返回
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("Error"), tr("Cannot save file: %1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText(); // 這裡填入實際要儲存的內容
    file.close();

    QMessageBox::information(this, tr("Success"), tr("File saved successfully!"));
}
void MainWindow::copy()
{
    // 取得 QTextEdit 中的內容
    QString text = textEdit->toPlainText();

    // 複製到剪貼簿
    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);

    // 提示訊息
    QMessageBox::information(this, tr("Success"), tr("Content copied to clipboard!"));
}
