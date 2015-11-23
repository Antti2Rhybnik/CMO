#include "QsThreadCore.hpp"

#include <QDebug>

#include "QsTime.hpp"
#include "QsSettings.hpp"
#include "QsRes.hpp"



QsThreadCore::QsThreadCore()
:
  clientScope(QsSettings::C),
  queueScope(QsSettings::Q),
  serverScope(QsSettings::S)
{
    if (eventScope.getScope().size() != 0) { qCritical() << "event scope must be clear";  }
    eventScope.addInScope<QsClient>(clientScope.getScope());
    eventScope.addInScope<QsQueueCell>(queueScope.getScope());
    eventScope.addInScope<QsServer>(serverScope.getScope());

}



bool QsThreadCore::step() {


    while (1) {
        // 1. найти текущее событие
        eventScope.findCurrentEvent();
        // 2. скорректировать системное время
        eventScope.correctCurrentTime();
        // 3. определить тип события
        event_type typeEvent = eventScope.getCurrentEventType();
        // 4. выбрать соответствующую реакцию
        switch (typeEvent)
        {
            case CLIENT_IN: { // заявка пришла с клиента
                /* достать заявку, сгенерировать след., поставить в очередь */
                QsClient* client = (QsClient*) eventScope.getCurrentObj();

                QsQuery* query = client->getQuery();

                client->initializeNextQuery();

                queueScope.nextInsertingCell();
                queueScope.insertQuery(query);

                if (QsSettings::byStep) {
                    if (QsRes::CURR_ACCEPTED >= QsSettings::maxN) return true;
                    else return false;
                }
                break;
            }
            case ON_QUEUE_FROM_CLIENT: { // заявка переместилась в очередь
                /* попробовать поставить на сервер (а вдруг есть свободные сервера!) */
                QsQueueCell* cell = (QsQueueCell*) eventScope.getCurrentObj();

                if (serverScope.findFree() && queueScope.nextExtractingCell()) { serverScope.insertQuery(queueScope.extractQuery()); }
                else { cell->setEvent(QsTime::currentTime , WAITING); }

                break;
            }
            case ON_SERVER_FROM_QUEUE:  { // заявка переместилась на сервер
                /* обработать её */
                QsServer* server = (QsServer*) eventScope.getCurrentObj();
                server->processIt();

                break;
            }
            case SERVER_OUT: { // заявка ушла с сервера
                /* попробовать забрать из очереди (а вдруг есть заявки в очереди!) */
                QsServer* server = (QsServer*) eventScope.getCurrentObj();
                server->finalizePrevQuery();

                if (queueScope.nextExtractingCell() && serverScope.findFree()) { serverScope.insertQuery(queueScope.extractQuery()); }
                else { server->setEvent(QsTime::currentTime, WAITING); }

                if (QsSettings::byStep) {
                    if (QsRes::CURR_ACCEPTED >= QsSettings::maxN) return true;
                    else return false;
                }
                break;
            }
            case WAITING:{
                break;
            }

        }

        if (!QsSettings::byStep) {
            if (QsRes::CURR_ACCEPTED >= QsSettings::maxN) return true;
            else return false;
        }
    }

}



void QsThreadCore::start_auto()
{
    while(!step());
}


