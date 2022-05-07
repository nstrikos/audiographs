#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include "requests.h"

class RequestReceiver
{
public:
    virtual void accept(Request *request) = 0;
    void setLog(bool log);

protected:
    bool m_log = false;
};

class RequestHandler
{
public:
    static RequestHandler& getInstance()
    {
        static RequestHandler instance;
        return instance;
    }

    void add(RequestReceiver *getter, request_type type);
    void handleRequest(Request *request);
    void setLog(bool log);

    bool log() const;

private:
    RequestHandler() { }
    RequestHandler(RequestHandler const&);     // Don't Implement
    void operator=(RequestHandler const&); // Don't implement
    QVector<RequestReceiver*> receivers[100];
    int request_id = 0;
private:
    bool m_log = false;
};

#endif // REQUESTHANDLER_H
