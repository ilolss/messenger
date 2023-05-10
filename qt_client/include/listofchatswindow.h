#ifndef LISTOFCHATSWINDOW_H
#define LISTOFCHATSWINDOW_H

#include <QDialog>
#include "chatwindow.h"

namespace Ui {
class ListOfChatsWindow;
}

class ListOfChatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ListOfChatsWindow(QWidget *parent = nullptr);
    ~ListOfChatsWindow();

private slots:
    void on_pushButton_clicked();
    void reject() override;

private:
    Ui::ListOfChatsWindow *ui;
    ChatWindow* chatWindow;

signals:
    void windowCloseSignal();
};

#endif // LISTOFCHATSWINDOW_H
