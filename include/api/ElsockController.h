/*
 * ElsockControllerCpp is a controller for elsock devices.
 * Copyright (C) 2014  offa
 * 
 * This file is part of ElsockControllerCpp.
 *
 * ElsockControllerCpp is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ElsockControllerCpp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ElsockControllerCpp.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file ElsockController.h
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 * 
 * Provides controlls to the remote elsock host.
 */

#ifndef ELSOCKCONTROLLER_H
#define	ELSOCKCONTROLLER_H

#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QMap>

#include "ElsockTypes.h"


/**
 * Query data.
 */
typedef QMap<Device, Status> ElsockData;


/**
 * The class <code>ElsockController</code> provides access to Elsock-devices.
 */
class ElsockController
{
public:
    
    /**
     * Constructor.
     * 
     * @param protocol      Protocol to communicate with the remote host
     * @param address       Remotehost address
     */
    explicit ElsockController(QString protocol, QString address);
    
    /**
     * Copy-constructor.
     * 
     * @param other     Other object
     */
    ElsockController(const ElsockController& other);
    
    /**
     * Destructor.
     */
    virtual ~ElsockController();
    
    
    /**
     * Sets the device <code>dev</code> to status <code>status</code>.
     * 
     * @param dev       Device
     * @param status    Status
     */
    void sendCommand(Device dev, Status status) const;
    
    /**
     * Toggles the device <code>device</code>.
     * 
     * @param dev       Device
     */
    void sendToggle(Device dev) const;
    
    /**
     * Toggles all devices.
     */
    void sendToggleAll() const;
    
    /**
     * Returns the status of device <code>device</code>.
     * 
     * @param device        Device
     * @return              Status
     */
    Status getStatus(Device device) const;
    
    /**
     * Returns the status of all devices.
     * 
     * @return      Status of all devices
     */
    ElsockData getStatus() const;

    
    /**
     * Returns the protocol thats used to communicate with the remote host.
     * 
     * @return      Protocol
     */
    QString getProtocol() const;
    
    /**
     * Returns the remote hosts address.
     * 
     * @return      Address
     */
    QString getAddress() const;
    
    
    /**
     * Swaps <code>first</code> and <code>second</code>.
     * 
     * @param first     First object    
     * @param second    Second object
     */
    friend void swap(ElsockController& first, ElsockController& second);
    
    /**
     * Assignment operator.
     * 
     * @param other     Object to assign to this
     * @return          Reference to this object
     */
    ElsockController& operator=(ElsockController other);
    
    
private:
    
    /**
     * Returns the base address used to communicate with the remote host
     * (including the trailing <code>'/'</code>).
     * 
     * @return      Baseaddress
     */
    QString getBaseAddress() const;

    /**
     * Constructs the query-url for <code>queryObjs</code>.
     * 
     * @param queryObjs     Querydata
     * @return              Query-url
     */
    QUrl constructQuery(ElsockData queryObjs) const;
    
    /**
     * Sends a request for the query-url <code>url</code> and returns the
     * remote host's reply.
     * 
     * @param url       Query-url
     * @return          Reply to query
     */
    QNetworkReply* sendReq(const QUrl& url) const;
    
    
    QString m_protocol;
    QString m_address;
    QSharedPointer<QNetworkAccessManager> m_networkAccessManager;
};

#endif	/* ELSOCKCONTROLLER_H */

