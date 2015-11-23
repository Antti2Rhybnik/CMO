#include "QsQueueScope.hpp"

#include "QsRes.hpp"
#include "QsTime.hpp"
#include <QDebug>

QsQueueCell::QsQueueCell(int id_arg)  :  QsEvent(0, WAITING) {

    qDebug() << "ctor 'QsQueueCell' has called";
    id = id_arg;
    query = nullptr;
    empty_flag = true;
}

QsQueueCell::~QsQueueCell()
{
    qDebug() << "dtor 'QsQueueCell' has called";
}


bool QsQueueCell::hasQuery() const {

    return !empty_flag;
}


int QsQueueCell::getId() const {
    return id;
}

QsQuery *QsQueueCell::getQuery() const
{
    return query;
}


void QsQueueCell::rejectPrevQuery() {

    Q_CHECK_PTR(query);
    query->setWOutTime(QsTime::currentTime);
    QsRes::addToRejected(query);
    empty_flag = true;

}

void QsQueueCell::pushQuery(QsQuery* query) {

    (this->query = query)
            -> setWInTime(QsTime::currentTime);

    empty_flag = false;
    this->setEvent(QsTime::currentTime, ON_QUEUE_FROM_CLIENT);
}

QsQuery* QsQueueCell::popQuery() {

    this->setEvent(QsTime::currentTime, WAITING);
    empty_flag = true;

    return query;
}

//================================================================

QsQueueScope::QsQueueScope(int N_arg) : QsScope<QsQueueCell>(N_arg) {

    qDebug() << "ctor 'QsQueueScope' has called";

    insertingCell = scope.begin();
    extractingCell = scope.begin();
}

QsQueueScope::~QsQueueScope()
{
    for (auto& obj : scope) { delete obj; }
    scope.clear();
    qDebug() << "dtor 'QsQueueScope' has called";
}

void QsQueueScope::cycle_increment(std::vector<QsQueueCell*>::iterator& iter) {
    auto last = --scope.end();
    if (iter != last) {
        ++iter;
    }
    else {
        iter = scope.begin();
    }
};


bool QsQueueScope::nextInsertingCell() {
/*
 * Этот метод ищет по кольцу место, куда можно разместить запрос, до первого свободного.
 * Если не находит, то оставляет итератор 'placeToInsert' без изменений, и выбивается запрос под итератором.
 */

    auto find_iter = this->insertingCell;
    auto stop_iter = this->insertingCell;

    do
    {
        if (!(*find_iter)->hasQuery()) {

            insertingCell = find_iter;
            return true; // this means that place without query is found
        }
        cycle_increment(find_iter);
    }
    while(find_iter != stop_iter);

    return false; // this means that place without query is't found

};


bool QsQueueScope::nextExtractingCell() {
/*
 * Этот метод ищет по кольцу место, куда можно разместить запрос, до первого свободного.
 * Если не находит, то оставляет итератор 'placeToExtract' без изменений, и выбивается запрос под итератором.
 */

    auto find_iter = this->extractingCell;
    auto stop_iter = this->extractingCell;

    do
    {
        if ((*find_iter)->hasQuery()) {

            extractingCell = find_iter;
            return true; // this means that place with query is found
        }
        cycle_increment(find_iter);
    }
    while(find_iter != stop_iter);

    return false; // this means that place with query is't found
};


void QsQueueScope::insertQuery(QsQuery* query) {

    Q_CHECK_PTR(query);
    // 2. если оно содержит prevQuery, то rejectPrevQuery
    if ((*insertingCell)->hasQuery()) { (*insertingCell)->rejectPrevQuery(); }

    // 3. заппушить запрос
    (*insertingCell)->pushQuery(query);

    // 4. сдвинуть итератор на следующее
    cycle_increment(insertingCell);

}


QsQuery* QsQueueScope::extractQuery() {

    // 2. сохраняем запрос
    QsQuery* returningQuery = (*extractingCell)->popQuery();

    // 3. сдвигаем итератор на следующее
     cycle_increment(extractingCell);

    // 4. возвращаем запрос
    return returningQuery;
}
