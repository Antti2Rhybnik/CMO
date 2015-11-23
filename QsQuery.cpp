#include "QsQuery.hpp"


QsQuery::QsQuery() {

    count = 0;
    id_client = 0;
    id_server = 0;
    initializingTime = -1;
    timeWaitingIn = -1;
    timeWaitingOut = -1;
    finalizingTime = -1;
}

QsQuery* QsQuery::setCount(int count)
{
    this->count = count;
    return this;
}

QsQuery* QsQuery::setIdCl(int id_client)
{
    this->id_client = id_client;
    return this;
}

QsQuery* QsQuery::setIdSrv(int id_server)
{
    this->id_server = id_server;
    return this;
}

QsQuery* QsQuery::setInitTime(double initializingTime)
{
    this->initializingTime = initializingTime;
    return this;
}

QsQuery* QsQuery::setWInTime(double timeWaitingIn)
{
    this->timeWaitingIn = timeWaitingIn;
    return this;
}

QsQuery* QsQuery::setWOutTime(double timeWaitingOut)
{
    this->timeWaitingOut = timeWaitingOut;
    return this;
}

QsQuery* QsQuery::setFinTime(double finalizingTime)
{
    this->finalizingTime = finalizingTime;
    return this;
}

int QsQuery::getCount() const
{
    return count;
}

int QsQuery::getIdCl() const
{
    return id_client;
};
