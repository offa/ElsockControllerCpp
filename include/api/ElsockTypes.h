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
 * @file ElsockTypes.h
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 * 
 * Basic types and appropriate utility functions.
 */

#ifndef ELSOCKTYPES_H
#define	ELSOCKTYPES_H

/**
 * Enumeration of supported devices.
 */
enum Device
{
    ALL,        ///< All devices
    DEVICE_0,   ///< Devie #0
    DEVICE_1,   ///< Devie #1
    DEVICE_2,   ///< Devie #2
    DEVICE_3,   ///< Devie #3
    DEVICE_4,   ///< Devie #4
    DEVICE_5,   ///< Devie #5
    DEVICE_6,   ///< Devie #6
    DEVICE_7,   ///< Devie #7
    DEVICE_8,   ///< Devie #8
    DEVICE_9    ///< Devie #9
};


/**
 * Returns the device-id.
 * 
 * @param dev       Device
 * @return          The id of <code>dev</code> or <code>'-'</code> if unknown
 */
inline char toDeviceID(const Device dev)
{
    switch(dev)
    {
        case ALL:
            return 'A';
        case DEVICE_0:
            return 'a';
        case DEVICE_1:
            return 'b';
        case DEVICE_2:
            return 'c';
        case DEVICE_3:
            return 'd';
        case DEVICE_4:
            return 'e';
        case DEVICE_5:
            return 'f';
        case DEVICE_6:
            return 'g';
        case DEVICE_7:
            return 'h';
        case DEVICE_8:
            return 'i';
        case DEVICE_9:
            return 'j';
        default:
            return '-';
    }
}


/**
 * Enumeration of device status.
 */
enum Status
{
    OFF,    ///< Off
    ON,     ///< On
    TOGGLE, ///< Toggle
    GET_STATUS, ///< Get status
    UNKNOWN     ///< Unknown
};


/**
 * Returns the status-id.
 * 
 * @param s     Status
 * @return      The id of <code>s</code> or <code>'-'</code> if unknown
 */
inline char toStatusID(const Status s)
{
    switch(s)
    {
        case OFF:
            return '0';
        case ON:
            return '1';
        case TOGGLE:
            return 't';
        case GET_STATUS:
            return 's';
        case UNKNOWN:
        default:
            return '-';
    }
}

#endif	/* ELSOCKTYPES_H */

