##Query System Simulator##

This is Qt based application which simulates a query system.

possible event types: 
* WAITING 
* CLIENT_IN 
* ON_QUEUE_FROM_CLIENT 
* ON_SERVER_FROM_QUEUE 
* SERVER_OUT

**Classes inheritance:**

**QsEvent** (_describes the time and type of event_)

* QsClient
* QsQueueCell
* QsServer

**QsScope** (_just aggregates a vector of..._)

* QsClientScope (...vector of 'QsClient' class)
* QsQueueScope (...vector of 'QsQueueCell' class)
* QsServerScope (...vector of 'QsServer' class)

