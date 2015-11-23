#ifndef QS_QUERY_HPP
#define QS_QUERY_HPP

class QsQuery
{

public:

    // -- CTORS --
    QsQuery();

    // -- SETTERS --
    QsQuery* setCount(int);
    QsQuery* setIdCl(int);
    QsQuery* setIdSrv(int);
    QsQuery* setInitTime(double);
    QsQuery* setWInTime(double);
    QsQuery* setWOutTime(double);
    QsQuery* setFinTime(double);

    // -- GETTERS --
    int getCount() const;
    int getIdCl() const;


    int count;
    int id_client;
    int id_server;
    double initializingTime;
    double timeWaitingIn;
    double timeWaitingOut;
    double finalizingTime;



};

#endif // QS_QUERY_HPP
