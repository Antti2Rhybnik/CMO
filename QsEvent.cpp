#include "QsEvent.hpp"
#include <QDebug>

QsEvent::QsEvent() {}


QsEvent::QsEvent(double time, event_type type) {

    qDebug() << "ctor 'QsEvent' has called";

    this->time = time;
    this->type = type;
}

QsEvent::~QsEvent()
{
    qDebug() << "dtor 'QsEvent' has called";
}


event_type QsEvent::getType() const {
    return type;
}


double QsEvent::getTime() const {
    return time;
}


void QsEvent::setEvent(double time, event_type type) {
    this->time = time;
    this->type = type;
}
