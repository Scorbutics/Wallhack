#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "UniSenderIPC.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0, ISenderIPC *ipc = NULL);
    void setShortcut(int key1, int key2);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
    ISenderIPC* ipc;
    int shortcutKey1;
    int shortcutKey2;
};

#endif // MAINWINDOW_H
