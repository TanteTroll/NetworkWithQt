#include "network.h"
#include "message.h"

#include <QDataStream>


Network::Network(QWidget *parent) : QMainWindow(parent)
{

}

void Network::writeOut(Message message, QTcpSocket *socket)
{
    QByteArray block;
    QDataStream sendStream(&block, QIODevice::ReadWrite);
    sendStream.setVersion(QDataStream::Qt_4_0);
    sendStream << quint16(0) << message;

    sendStream.device()->seek(0);
    sendStream << (quint16)(block.size() - sizeof(quint16));

    socket->write(block);
    socket->waitForBytesWritten(1000);
}

void Network::receiveIncomingMessage()
{
    QTcpSocket* tcpSocket = qobject_cast<QTcpSocket*>( sender() );
    _blockSize=0;
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);
    Message msg;

    while (true){
        if (_blockSize == 0) {
            if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
                break;

            in >> _blockSize;
        }

        if (tcpSocket->bytesAvailable() < _blockSize)
            break;

        in >> msg;
    }

    emit sendIncomingMessage(msg);
}


