#ifndef QS_SERVER_HPP
#define QS_SERVER_HPP


#include "QsEvent.hpp"
#include "QsQuery.hpp"
#include "QsScope"

class QsServer : public QsEvent {

public:

    // -- CTORS --
    QsServer(int);
    // -- DTORS --
    ~QsServer();

    // -- METHODS --
    void pushQuery(QsQuery*);
    void processIt();
    void finalizePrevQuery();
    bool hasQuery();

    // -- GETTERS --
    int getId() const;

private:

    int id;
    bool empty_flag;
    QsQuery* query;

    double genTime();
};



class QsServerScope : public QsScope<QsServer> {

public:

    // -- CTORS --
    QsServerScope(int);
    // -- DTORS --
    ~QsServerScope();

    // -- METHODS --
    bool findFree();
    void insertQuery(QsQuery*);

private:

    std::vector<QsServer*>::iterator freeServer;

};


#endif // QS_SERVER_HPP
