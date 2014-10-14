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
 * @file MainWindow.cpp
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 */

#include "app/MainWindow.h"

#include <QSignalMapper>
#include <QRegExp>
#include <QRegExpValidator>


MainWindow::MainWindow(const QString appName, const QString appVersion) 
                                        : m_controller("http", "0.0.0.0")
{
    widget.setupUi(this);
    
    setWindowTitle(appName);
    widget.tlVersion->setText(appVersion);
    
    QRegExpValidator* ipRegexValidator = new QRegExpValidator(IP_REGEX, this);
    widget.leHostAddress->setValidator(ipRegexValidator);
    
    connectSignals();
    
    emit hostValidityChanged(false);
}

MainWindow::~MainWindow()
{
}


void MainWindow::toggleAll()
{
    m_controller.sendToggleAll();
}

void MainWindow::toggleDevice(Device dev)
{
    m_controller.sendToggle(dev);
}

void MainWindow::toggleDevice(int devId)
{
    toggleDevice(static_cast<Device>(devId));
}

void MainWindow::hostChanged(const QString& str)
{
    bool valid = IP_REGEX.exactMatch(str);
    
    if( valid == true )
    {
        widget.leHostAddress->setStyleSheet("");
    }
    else
    {
        widget.leHostAddress->setStyleSheet("border: 1px solid red");
    }
    
    emit hostValidityChanged(valid);
}

void MainWindow::hostAccpeted(bool state)
{
    state = !state;
    
    if( state == true )
    {
        widget.pbConnect->setText("Save");
    }
    else
    {
        widget.pbConnect->setText("Edit");
        
        int index = widget.cbProtocol->currentIndex();
        QString protocol = widget.cbProtocol->itemText(index).toLower();
        
        ElsockController newCtrl(protocol, widget.leHostAddress->text());
        swap(newCtrl, m_controller);
    }
    
    widget.cbProtocol->setEnabled(state);
    widget.leHostAddress->setEnabled(state);
}

void MainWindow::setAllOn()
{
    m_controller.sendCommand(ALL, ON);
}

void MainWindow::setAllOff()
{
    m_controller.sendCommand(ALL, OFF);
}

void MainWindow::connectSignals()
{
    connect(widget.pbToggleAll, SIGNAL(clicked()), this, SLOT(toggleAll()));
    connect(widget.pbAllOn, SIGNAL(clicked()), this, SLOT(setAllOn()));
    connect(widget.pbAllOff, SIGNAL(clicked()), this, SLOT(setAllOff()));
    connect(widget.leHostAddress, SIGNAL(textEdited(const QString&)), this, SLOT(hostChanged(const QString&)));
    
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbAllOn, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbAllOff, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbToggleAll, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice2, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice3, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice4, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice5, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice6, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice7, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice8, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbDevice9, SLOT(setEnabled(bool)));
    
    connect(this, SIGNAL(hostValidityChanged(bool)), widget.pbConnect, SLOT(setEnabled(bool)));
    connect(widget.pbConnect, SIGNAL(clicked(bool)), this, SLOT(hostAccpeted(bool)));
    
    QSignalMapper* signalMapper = new QSignalMapper(this);
    connect(widget.pbDevice1, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice2, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice3, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice4, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice5, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice6, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice7, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice8, SIGNAL(clicked()), signalMapper, SLOT(map()));
    connect(widget.pbDevice9, SIGNAL(clicked()), signalMapper, SLOT(map()));
    
    signalMapper->setMapping(widget.pbDevice1, DEVICE_1);
    signalMapper->setMapping(widget.pbDevice2, DEVICE_2);
    signalMapper->setMapping(widget.pbDevice3, DEVICE_3);
    signalMapper->setMapping(widget.pbDevice4, DEVICE_4);
    signalMapper->setMapping(widget.pbDevice5, DEVICE_5);
    signalMapper->setMapping(widget.pbDevice6, DEVICE_6);
    signalMapper->setMapping(widget.pbDevice7, DEVICE_7);
    signalMapper->setMapping(widget.pbDevice8, DEVICE_8);
    signalMapper->setMapping(widget.pbDevice9, DEVICE_9);
    
    connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(toggleDevice(int)));
}

const QString MainWindow::IP_BYTE_REGEX("(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])");
const QRegExp MainWindow::IP_REGEX(QString("^%1\\.%2\\.%3\\.%4$")
                                    .arg(MainWindow::IP_BYTE_REGEX)
                                    .arg(MainWindow::IP_BYTE_REGEX)
                                    .arg(MainWindow::IP_BYTE_REGEX)
                                    .arg(MainWindow::IP_BYTE_REGEX));