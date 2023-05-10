#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "listofchatswindow.h"
#include "client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_signUpButton_clicked();
    void on_logInButton_clicked();

signals:
    void signalsLogIn(QString username, QString password);
    void signalsSignUp(QString username, QString password);

private:
    Ui::MainWindow *ui;
    ListOfChatsWindow* listOfChatsWindow;
    Client* client;
};
#endif // MAINWINDOW_H
