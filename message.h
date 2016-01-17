#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QDataStream>
#include <ostream>
#include <istream>
#include <string>

class Message
{
public:
    enum msgType {Nachricht, Order};
    Message();
    Message(msgType type, QString str);
    Message(QString str);

    QDataStream &read(QDataStream &dataStream);
    QDataStream &write(QDataStream &dataStream) const;



    msgType type;
    QString str;
private:

};

QDataStream &operator<<(QDataStream &out, const Message &d);
QDataStream &operator>>(QDataStream &in, Message &d);

#endif // MESSAGE_H
