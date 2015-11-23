#include "QsClientScope.hpp"

#include <QDebug>
#include <cstdlib>
#include <cmath>
#include "QsTime.hpp"
#include "QsSettings.hpp"




double QsClient::genTime() {
    return double(rand()%100)/100 * QsSettings::lambda_Cl;
}


QsClient::QsClient(int id) :  QsEvent(0, WAITING) {

    qDebug() << "ctor 'QsClient' has called";

    this->id = id;
    this->count = 1;

    double init_time = genTime();

    (query = new QsQuery())
            -> setIdCl(id)
            -> setInitTime(init_time)
            -> setCount(count);

    this->count++;
    this->setEvent(init_time, CLIENT_IN);
}

QsClient::~QsClient()
{
    qDebug() << "dtor 'QsClient' has called";
}

QsQuery* QsClient::getQuery() const {

    return query;
}

int QsClient::getId() const {

    return id;
}


void QsClient::initializeNextQuery() {

    double init_time = QsTime::currentTime + genTime();

    (query = new QsQuery())
            -> setIdCl(id)
            -> setInitTime(init_time)
            -> setCount(count);

    this->count++;
    this->setEvent(init_time, CLIENT_IN);
}




////////////////////////////////////////////////////////////////

QsClientScope::QsClientScope(int N) : QsScope<QsClient>(N) {

    qDebug() << "ctor 'QsClientScope' has called";
}

QsClientScope::~QsClientScope()
{
    for (auto& obj : scope) { delete obj; }
    scope.clear();
    qDebug() << "dtor 'QsClientScope' has called";
}


