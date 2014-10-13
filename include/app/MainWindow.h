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
 * @file MainWindow.h
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 * 
 * Provides a user interface for controlling the remote elsock host.
 */

#ifndef MAINWINDOW_H
#define	MAINWINDOW_H

#include "ui_MainWindow.h"
#include "api/ElsockController.h"
#include <QMap>
#include <QString>

/**
 * The class <code>MainWindow</code> implements the main window of the
 * application.
 * 
 * It provices controlls to the remote elsock-host.
 */
class MainWindow : public QDialog
{
    Q_OBJECT
    
public:
    
    /**
     * Constructor.
     * 
     * @param appName       Application name (shown as title)
     * @param appVersion    Application version
     */
    MainWindow(const QString appName = "MainWindow", const QString appVersion = "");
    
    /**
     * Destructor.
     */
    virtual ~MainWindow();
    
    
signals:

    /**
     * The host address has changed it's validity.
     * 
     * @param valid     If <tt>true</tt> the host is valid or
     *                  <tt>false</tt> if not
     */
    void hostValidityChanged(bool valid);


private slots:
    
    /**
     * Toggles all devices.
     */
    void toggleAll();
    
    /**
     * Set all devices to <code>ON</code>.
     */
    void setAllOn();
    
    /**
     * Set all devices to <code>OFF</code>.
     */
    void setAllOff();
    
    /**
     * Toggles the device <code>dev</code>.
     * 
     * @param dev       Device
     */
    void toggleDevice(Device dev);
    
    /**
     * Toggles the device with id <code>devId</code>.
     * 
     * @param devId     Device-ID
     */
    void toggleDevice(int devId);
    
    /**
     * Tests if a valid host has been entered.
     * 
     * @param str
     */
    void hostChanged(const QString& str);
    
    /**
     * Updates components depending on the host's state.
     * 
     * @param state     If <tt>true</tt> the new host has been accepted,
     *                  otherwise <tt>false</tt> if not
     */
    void hostAccpeted(bool state);
    
private:
    
    /**
     * Connects signals and slots.
     */
    void connectSignals();
    
    
    Ui::MainWindow widget;
    ElsockController m_controller;
    
    static const QString IP_BYTE_REGEX;
    static const QRegExp IP_REGEX;
};

#endif	/* MAINWINDOW_H */
