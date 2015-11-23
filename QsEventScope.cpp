#include "QsEventScope.hpp"

#include <QDebug>
#include "QsTime.hpp"


QsEventScope::QsEventScope() : QsScope<QsEvent>() {

    qDebug() << "ctor 'QsEventScope' has called";
}

QsEventScope::~QsEventScope()
{
    scope.clear();
    qDebug() << "ctor 'QsEventScope' has called";
}


void QsEventScope::findCurrentEvent() {

    // we just finding first event without WAITING status
    for (auto event = scope.begin(); event != scope.end(); ++event) {

        if ((*event)->getType() != WAITING) {
            currentEvent = event;
            break;
        }
    }

    // now we finding min event
    for (auto event = scope.begin(); event != scope.end(); ++event) {

        if ((*event)->getType() != WAITING) {

            if ((*event)->getTime() < (*currentEvent)->getTime()) {

                currentEvent = event;
            }

        }

    }


}



event_type QsEventScope::getCurrentEventType() const {

    return (*currentEvent)->getType();
}


void QsEventScope::correctCurrentTime() {
    QsTime::currentTime = (*currentEvent)->getTime();
}



QsEvent* QsEventScope::getCurrentObj() const {

    return (*currentEvent);
}
