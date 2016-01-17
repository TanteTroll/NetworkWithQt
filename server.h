#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QTcpServer>

#include "network.h"
#include "message.h"

namespace Ui {
class Server;
}

class Server :  public Network
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

private:
    Ui::Server *ui;
    QTcpServer *tcpServer;

    std::vector <QTcpSocket*> clientList;

    void printConnections();
    void analyzeIncomingMessage(Message msg);

private slots:
    void newConnection();


};

#endif // SERVER_H
