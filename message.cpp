#include "message.h"
#include <type_traits>

Message::Message()
{

}

Message::Message(msgType type, QString str)
{
    this->type = type;
    this->str=str;
}

Message::Message(QString str)
{
    this->type = Message::Nachricht;
    this->str=str;
}

QDataStream& operator <<(QDataStream &out, const Message &m) {
    return m.write(out);
}

QDataStream& operator >>(QDataStream &in, Message &m) {
    return m.read(in);
}

QDataStream& operator <<(QDataStream &out, const Message *m) {
    return m->write(out);
}

QDataStream& operator >>(QDataStream &in, Message *m) {
    return m->read(in);
}

QDataStream& Message::read(QDataStream &dataStream) {
    int i_type;
    dataStream >> str;
    dataStream >> i_type;
    type = static_cast < Message::msgType > (i_type);

    return dataStream;
}

QDataStream& Message::write(QDataStream &dataStream) const {
    dataStream << str;
    dataStream << static_cast < std::underlying_type <Message::msgType>::type >(type);

    return dataStream;
}
