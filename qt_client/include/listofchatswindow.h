#ifndef LISTOFCHATSWINDOW_H
#define LISTOFCHATSWINDOW_H

#include <QDialog>
#include "chatwindow.h"
#include "globalclient.h"

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
    void reject() override;
    void slotOpenChatWindow(qint32 partner_user_id);

    void on_openChatButton_clicked();

private:
    Ui::ListOfChatsWindow *ui;
    ChatWindow* chatWindow;
//    qint32 user_id;

signals:
    void windowCloseSignal();
    void disconnectSignal();
    void getUserIdSignal(QString username);
};

#endif // LISTOFCHATSWINDOW_H
