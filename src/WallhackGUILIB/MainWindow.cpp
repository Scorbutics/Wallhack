#include <windows.h>
#include "MainWindow.h"
#include "ui_MainWindow.h"

#define MESSAGE_WALLHACKGUI_DEFAULT_TRANSPARENCY "Wallhack_GUI_Default_Transparency"
#define MESSAGE_WALLHACKGUI_SHORTCUT "Wallhack_GUI_Shortcut"

extern HWND hTarget;

MainWindow::MainWindow(QWidget *parent, ISenderIPC* ipc) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    this->ipc = ipc;
    ui->setupUi(this);

    shortcutKey1 = -1;
    shortcutKey2 = -1;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setShortcut(int key1, int key2) {
    shortcutKey1 = key1;
    shortcutKey2 = key2;
}

void MainWindow::on_pushButton_pressed()
{
    if(ipc != NULL) {
        std::string message = MESSAGE_WALLHACKGUI_SHORTCUT;
        ipc->send(message, (WPARAM)shortcutKey1, (LPARAM)shortcutKey2);
        std::cout << "Shortcut set : " << shortcutKey1 << " + " << shortcutKey2 << std::endl;
        shortcutKey1 = 0;
        shortcutKey2 = 0;

    }
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    if(ipc != NULL) {
        std::string message = MESSAGE_WALLHACKGUI_DEFAULT_TRANSPARENCY;
        ipc->send(message, (WPARAM)value, (LPARAM)NULL);
    }
}
