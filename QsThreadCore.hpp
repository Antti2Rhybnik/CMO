#ifndef THREAD_CORE_H
#define THREAD_CORE_H

#include <QtCore>
#include <QDebug>

#include "QsClientScope.hpp"
#include "QsServerScope.hpp"
#include "QsQueueScope.hpp"
#include "QsEventScope.hpp"

class QsThreadCore {

public:

    // -- CTORS --
    QsThreadCore();


    // -- METHODS --
    bool step();
    void start_auto();


public:

    QsClientScope clientScope;
    QsQueueScope  queueScope;
    QsServerScope serverScope;

    QsEventScope eventScope;


};




#endif // THREAD_CORE_H
