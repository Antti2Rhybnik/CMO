#ifndef QS_QUEUE_SCOPE_HPP
#define QS_QUEUE_SCOPE_HPP


#include "QsEvent.hpp"
#include "QsQuery.hpp"
#include "QsScope"


class QsQueueCell : public QsEvent {

public:

    // -- CTORS --
    QsQueueCell(int);
    // -- DTORS --
    ~QsQueueCell();

    // -- METHODS --
    bool hasQuery() const;
    void rejectPrevQuery();
    QsQuery* popQuery();
    void pushQuery(QsQuery*);

    // -- GETTERS --
    int getId() const;
    QsQuery* getQuery() const;


private:

    int id;
    QsQuery* query;
    bool empty_flag;

};


class QsQueueScope : public QsScope<QsQueueCell> {

public:

    // -- CTORS --
    QsQueueScope(int);
    // -- DTORS --
    ~QsQueueScope();

    // -- METHODS --
    bool nextInsertingCell();
    bool nextExtractingCell();
    void insertQuery(QsQuery*);
    QsQuery* extractQuery();

private:

    std::vector<QsQueueCell*>::iterator insertingCell;
    std::vector<QsQueueCell*>::iterator extractingCell;


    void cycle_increment(std::vector<QsQueueCell*>::iterator&);

};





#endif // QS_QUEUE_SCOPE_HPP
