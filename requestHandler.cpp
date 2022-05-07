#include "requestHandler.h"

#include <QDebug>

void RequestReceiver::setLog(bool log)
{
    m_log = log;
}

void RequestHandler::add(RequestReceiver *getter, request_type type)
{
    if (type < 100) {

        if (!receivers[type].contains(getter))
            receivers[type].append(getter);
    }
}

void RequestHandler::handleRequest(Request *request)
{
    int type = request->type;

    request->id = request_id;
    request_id++;
    if (request_id > 1000)
        request_id = 0;

    if (type < 100) {
        QVector<RequestReceiver*> tmp_vector = receivers[type];
        for (int i = 0; i < tmp_vector.size(); i++) {
            if (m_log)
                qDebug() << (i+1) << "of" << tmp_vector.size() << " id: " << request->id << " Sender: " << request->sender << " request: " << request->description;
            tmp_vector.at(i)->accept(request);
        }
    }
}

void RequestHandler::setLog(bool log)
{
    m_log = log;
    qDebug() << "Request handler set log " << m_log;
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < receivers[i].size(); j++)
            receivers[i].at(j)->setLog(log);
    }
}

bool RequestHandler::log() const
{
    return m_log;
}
