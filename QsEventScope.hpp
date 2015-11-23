#ifndef QS_EVENT_SCOPE
#define QS_EVENT_SCOPE

#include "QsEvent.hpp"
#include "QsScope"


class QsEventScope : public QsScope<QsEvent> {

    // std::vector<QsEvent*> scope;
    // std::vector<QsEvent*>& getScope();
    // void addInScope(std::vector<QsEvent*>& scope);
    // static double currentTime;


    std::vector<QsEvent*>::iterator currentEvent;

public:

    QsEventScope();
    ~QsEventScope();

    void findCurrentEvent();

    event_type getCurrentEventType() const;
    QsEvent* getCurrentObj() const;

    void correctCurrentTime();

};



#endif // QS_EVENT_SCOPE
