#include "../include/listofchatswindow.h"
#include "./ui_listofchatswindow.h"
#include <QDebug>

ListOfChatsWindow::ListOfChatsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListOfChatsWindow)
{
    ui->setupUi(this);
}

ListOfChatsWindow::~ListOfChatsWindow()
{
    delete ui;
    delete chatWindow;
}

void ListOfChatsWindow::on_pushButton_clicked()
{
    chatWindow = new ChatWindow(this);
    connect(this, &ListOfChatsWindow::windowCloseSignal, chatWindow, &ChatWindow::reject);
    chatWindow->show();
}

void ListOfChatsWindow::reject() {
    qDebug() << "Close list of chats window\n";
    emit windowCloseSignal();
    QDialog::reject();
}
