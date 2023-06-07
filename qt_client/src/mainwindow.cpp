#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/listofchatswindow.h"
#include <QCryptographicHash>
#include "../include/globalclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GlobalClient::client = new Client();
    listOfChatsWindow = new ListOfChatsWindow();
//    qDebug() << "MainWindow constructor";
    connect(this, &MainWindow::signalsLogIn, GlobalClient::client, &Client::slotSendLogInRequest);
    connect(this, &MainWindow::signalsSignUp, GlobalClient::client, &Client::slotSendSignUpRequest);
    connect(GlobalClient::client, &Client::signalOpenListOfchatWindow, this, &MainWindow::slotOpenListOfChatsWindow);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete listOfChatsWindow;
}
void MainWindow::on_logInButton_clicked()
{
    QString username = ui->loginLogInLineEdit->text();
    QString password = ui->passwordLogInLineEdit->text();
    password = QString(QCryptographicHash::hash((QByteArray::fromStdString(password.toStdString())),QCryptographicHash::Md5).toHex());
    emit signalsLogIn(username, password);
//    qDebug() << username << "\n" << password << "\n";
}

void MainWindow::slotOpenListOfChatsWindow()
{
    if (listOfChatsWindow != nullptr) {
        delete listOfChatsWindow;
    }
    listOfChatsWindow = new ListOfChatsWindow(this);
    listOfChatsWindow->setModal(true);
    listOfChatsWindow->show();
}


void MainWindow::on_signUpButton_clicked()
{
    QString username = ui->loginSignUpLineEdit->text();
    QString password = ui->passwordSignUpLineEdit->text();
    password = QString(QCryptographicHash::hash((QByteArray::fromStdString(password.toStdString())),QCryptographicHash::Md5).toHex());
    emit signalsSignUp(username, password);
//    qDebug() << username << "\n" << password << "\n";
}

