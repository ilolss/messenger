#include "../include/mainwindow.h"
#include "./ui_mainwindow.h"
#include "../include/listofchatswindow.h"
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client();
    connect(this, &MainWindow::signalsLogIn, client, &Client::slotSendLogInRequest);
    connect(this, &MainWindow::signalsSignUp, client, &Client::slotSendSignUpRequest);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete listOfChatsWindow;
    delete client;
}
void MainWindow::on_logInButton_clicked()
{
    listOfChatsWindow = new ListOfChatsWindow;
    listOfChatsWindow->setModal(true);
    listOfChatsWindow->show();
}


void MainWindow::on_signUpButton_clicked()
{
    QString username = ui->loginSignUpLineEdit->text();
    QString password = QString(QCryptographicHash::hash(("myPassword"),QCryptographicHash::Md5).toHex());
    emit signalsSignUp(username, password);
    qDebug() << username << "\n" << password << "\n";
}

