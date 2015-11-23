#include "QsServerScope.hpp"

#include <cstdlib>
#include <cmath>
#include "QsRes.hpp"
#include "QsTime.hpp"
#include "QsSettings.hpp"



double QsServer::genTime() {
    return log( 1 - double(rand()%100)/100 ) / (-QsSettings::lambda_Srv);
}


QsServer::QsServer(int id)  :  QsEvent(0, WAITING) {

    qDebug() << "ctor 'QsServer' has called";

    this->id = id;
    this->query = nullptr;
    this->empty_flag = true;
}

QsServer::~QsServer()
{
    qDebug() << "dtor 'QsServer' has called";
}


void QsServer::pushQuery(QsQuery* query) {

    (this->query = query)
            -> setIdSrv(id)
            -> setWOutTime(QsTime::currentTime);

    this->empty_flag = false;
    this->setEvent(QsTime::currentTime, ON_SERVER_FROM_QUEUE);
}


void QsServer::processIt() {

    double fin_time = QsTime::currentTime + genTime();

    this->query->setFinTime(fin_time);

    this->setEvent(fin_time, SERVER_OUT);
}


void QsServer::finalizePrevQuery() {

    empty_flag = true;
    QsRes::addToAccepted(query);
}


bool QsServer::hasQuery() {
    return !empty_flag;
}


int QsServer::getId() const {

    return id;
}


//=================================================

QsServerScope::QsServerScope(int N) : QsScope<QsServer>(N) {

    qDebug() << "ctor 'QsServerScope' has called";

    freeServer = scope.begin();
}

QsServerScope::~QsServerScope()
{
    for (auto& obj : scope) { delete obj; }
    scope.clear();
    qDebug() << "dtor 'QsServerScope' has called";
}


bool QsServerScope::findFree() { //... server in scope

    for (auto srv = scope.begin(); srv != scope.end(); ++srv) {

        if (!(*srv)->hasQuery()) { freeServer = srv; return true; }
    }

    return false;
}


void QsServerScope::insertQuery(QsQuery* query_arg) { //... to free server in scope

    if ((*freeServer)->hasQuery()) { exit(3); }
    (*freeServer)->pushQuery(query_arg);

}
