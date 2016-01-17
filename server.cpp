#include "server.h"
#include "ui_server.h"

#include <QtNetwork>
#include <QMessageBox>
#include <QTcpSocket>
#include <QDebug>

Server::Server(QWidget *parent) :
    Network(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);


    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection , this, &Server::newConnection);

    tcpServer->listen(ip_adress,port_number);
    ui->labelServerStatus->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n")
                             .arg(tcpServer->serverAddress().toString()).arg(tcpServer->serverPort()));


}

Server::~Server()
{
    delete ui;
    delete tcpServer;
}

void Server::newConnection()
{
    QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
    connect(clientConnection, &QTcpSocket::disconnected,
            clientConnection, &QTcpSocket::deleteLater);
    //connect(clientConnection, &QTcpSocket::disconnected,
    //        this, &QTcpSocket::connection_lost);
    connect(clientConnection, &QTcpSocket::readyRead,
            this, &Server::receiveIncomingMessage);
    connect(this, &Server::sendIncomingMessage,
            this, &Server::analyzeIncomingMessage);

    writeOut(tr("Welcome to this little Server mate."),clientConnection);

    clientList.push_back(clientConnection);
    printConnections();
}

void Server::printConnections()
{
    //tcpServer->dumpObjectTree();
    QTcpSocket *connection;
    QString output ="";
    foreach (connection, clientList)
    {
        if (!(connection->state() == QTcpSocket::ConnectedState)  )break;
        output += "Client-IP: ";
        output += connection->peerAddress().toString();
        output += "       auf Port: ";
        output += QString::number(connection->peerPort() );
        output += "\n";
    }
    ui->labelStatusConnections->setText(output);
}

void Server::analyzeIncomingMessage(Message msg)
{
    switch (msg.type)
    {
    case Message::Nachricht:
        ui->labelMessage->setText(msg.str);
        break;
    case Message::Order:
    default:
        qDebug("TODO");
    }
}
