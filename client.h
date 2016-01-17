#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>

#include "network.h"

namespace Ui {
class Client;
}

class Client : public Network
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket;

private slots:
    void slotConnected();
    void slotDisconnected();
    void slotError(QAbstractSocket::SocketError error);
    void on_buttonConnect_clicked();
    void on_buttonSend_clicked();

private:
    void analyzeIncomingMessage(Message msg);

};

#endif // CLIENT_H
