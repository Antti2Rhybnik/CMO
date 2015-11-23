#ifndef QS_EVENT_HPP
#define QS_EVENT_HPP

enum event_type { WAITING, CLIENT_IN, ON_QUEUE_FROM_CLIENT, ON_SERVER_FROM_QUEUE, SERVER_OUT };

class QsEvent {

public:

    double time;
    event_type type;


    QsEvent();
    QsEvent(double, event_type);
    ~QsEvent();

    event_type getType() const;
    double getTime() const;

    void setEvent(double, event_type);

};


#endif // QS_EVENT_HPP
