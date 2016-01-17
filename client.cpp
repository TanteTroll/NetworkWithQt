#include "client.h"
#include "ui_client.h"

#include <QtNetwork>
#include <QTcpSocket>
#include <QString>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>

Client::Client(QWidget *parent) :
    Network(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::readyRead,
            this, &Client::receiveIncomingMessage);
    connect(this, &Client::sendIncomingMessage,
            this, &Client::analyzeIncomingMessage);
}

Client::~Client()
{
    delete ui;
}

void Client::slotConnected()
{
    ui->statusbar->showMessage(ui->statusbar->currentMessage()+" connected ",500);

}

void Client::slotDisconnected()
{

}

void Client::slotError(QAbstractSocket::SocketError error)
{
    switch (error) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }
}

void Client::on_buttonConnect_clicked()
{
    tcpSocket->connectToHost(ip_adress, port_number );
}

void Client::on_buttonSend_clicked()
{
    QString input = ui->inputMessage->toPlainText();
    if (input.isEmpty()) {
        ui->statusbar->showMessage("no Message set! ", 500);
        return;
    }
    if (!(tcpSocket->state() == QTcpSocket::ConnectedState)  ) {
        ui->statusbar->showMessage("not connected to server! ", 500);
        return;
    }
    writeOut(input, tcpSocket);
}

void Client::analyzeIncomingMessage(Message msg)
{
    switch (msg.type)
    {
    case Message::Nachricht:
        ui->inputMessage->setText(msg.str);
        break;
    case Message::Order:
    default:
        qDebug("TODO");
    }
}
