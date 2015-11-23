#ifndef QS_CLIENT_HPP
#define QS_CLIENT_HPP


#include "QsQuery.hpp"
#include "QsEvent.hpp"
#include "QsScope"

class QsClient : public QsEvent {

public:

    // -- CTORS --
    QsClient(int);
    // -- DTORS --
    ~QsClient();

    // -- METHODS --
    void initializeNextQuery();

    // -- GETTERS --
    QsQuery* getQuery() const;
    int getId() const;

private:

    int id;
    QsQuery* query;
    int count;


    double genTime();


};


class QsClientScope : public QsScope<QsClient> {

public:

    // -- CTORS --
    QsClientScope(int);
    // -- DTORS --
    ~QsClientScope();

};



#endif // QS_CLIENT_HPP
