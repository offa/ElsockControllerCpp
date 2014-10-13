/*
 * ElsockController is a controller application for elsock devices.
 * Copyright (C) 2014  offa
 * 
 * This file is part of ElsockController.
 *
 * ElsockController is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ElsockController is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ElsockController.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file ElsockController.cpp
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 * 
 * Provides controlls to the remote elsock host.
 */

#include "api/ElsockController.h"

#include <QByteArray>
#include <QEventLoop>

#if __cplusplus < 201100L
# include <algorithm>
#else
# include <utility>
#endif /* __cplusplus */

ElsockController::ElsockController(QString protocol, QString address)
                                    : m_protocol(protocol.toLower()), 
                                    m_address(address),
                                    m_networkAccessManager(new QNetworkAccessManager)
{
}

ElsockController::ElsockController(const ElsockController& other) 
                            : m_protocol(other.m_protocol),
                            m_address(other.m_address), 
                            m_networkAccessManager(other.m_networkAccessManager)
{
}

ElsockController::~ElsockController()
{
}


ElsockController& ElsockController::operator=(ElsockController other)
{
    swap(*this, other);
    
    return *this;
}

void ElsockController::sendCommand(Device dev, Status status) const
{
    ElsockData data;
    data.insert(dev, status);
    
    QUrl query = constructQuery(data);
    QNetworkReply* reply = sendReq(query);
    
    if( reply->error() != QNetworkReply::NoError )
    {
        qDebug() << reply->errorString();
    }
}

void ElsockController::sendToggle(Device dev) const
{
    sendCommand(dev, TOGGLE);
}

void ElsockController::sendToggleAll() const
{
    sendCommand(ALL, TOGGLE);
}

Status ElsockController::getStatus(Device device) const
{
    return getStatus()[device];
}

ElsockData ElsockController::getStatus() const
{
    ElsockData data;
    data.insert(ALL, GET_STATUS);
    
    QUrl query = constructQuery(data);
    QNetworkReply* reply = sendReq(query);
    
    ElsockData response;
    
    if( reply->error() != QNetworkReply::NoError )
    {
        response.insert(ALL, UNKNOWN);
        qDebug() << reply->errorString();
    }
    else
    {
        QByteArray data = reply->readAll();
        Device dev = DEVICE_0;
        
        Q_FOREACH(char c, data)
        {
            switch(c)
            {
                case '0':
                    response.insert(dev, OFF);
                    dev = static_cast<Device>(dev + 1);
                    break;
                case '1':
                    response.insert(dev, ON);
                    dev = static_cast<Device>(dev + 1);
                    break;
                default:
                    break;
            }
            
            if( dev > DEVICE_9 )
            {
                break;
            }
        }
    }
    
    return response;
}

QString ElsockController::getAddress() const
{
    return m_address;
}

QString ElsockController::getProtocol() const
{
    return m_protocol;
}

QString ElsockController::getBaseAddress() const
{
    return QString("%1://%2/").arg(m_protocol).arg(m_address);
}

QUrl ElsockController::constructQuery(ElsockData queryObjs) const
{
    QString q(getBaseAddress());
    q.append("q?");
    
    int n = queryObjs.size();
    
    Q_FOREACH(Device obj, queryObjs.keys())
    {
        q.append("L").append(toDeviceID(obj)).append("=")
            .append(toStatusID(queryObjs[obj]));
        
        if( --n > 0 )
        {
            q.append("&");
        }
    }
    
    return QUrl(q);
}

QNetworkReply* ElsockController::sendReq(const QUrl& url) const
{
    QNetworkReply* reply = m_networkAccessManager->get(QNetworkRequest(url));
    
    QEventLoop blockUntilReady;
    blockUntilReady.connect(&(*m_networkAccessManager), SIGNAL(finished(QNetworkReply*)), SLOT(quit())); 
    blockUntilReady.exec();
    
    return reply;
}

void swap(ElsockController& first, ElsockController& second)
{
    using std::swap;
    
    swap(first.m_address, second.m_address);
    swap(first.m_networkAccessManager, second.m_networkAccessManager);
    swap(first.m_protocol, second.m_protocol);
}
