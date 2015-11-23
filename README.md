possible types of event: 
  WAITING, CLIENT_IN, ON_QUEUE_FROM_CLIENT, ON_SERVER_FROM_QUEUE, SERVER_OUT;

Classes inheritance:

QsEvent (describes the time and type of event)

-> QsClient

-> QsQueueCell

-> QsServer

QsScope (just aggregates a vector of...)

-> QsClientScope (...vector of 'QsClient' class)

-> QsQueueScope (...vector of 'QsQueueCell' class)

-> QsServerScope (...vector of 'QsServer' class)

