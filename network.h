#ifndef NETWORK_H
#define NETWORK_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QNetworkSession>

#include "message.h"

class Network : public QMainWindow
{
    Q_OBJECT

public:
    explicit Network(QWidget *parent = 0);

signals:

    void sendIncomingMessage( Message msg );

protected slots:

    void writeOut(Message message, QTcpSocket *socket);
    void receiveIncomingMessage();

protected:
    QHostAddress ip_adress = "127.0.0.1";
    quint16 port_number = 54554;

    quint16 _blockSize=0;  //for signal incoming message
};

#endif // NETWORK_H
