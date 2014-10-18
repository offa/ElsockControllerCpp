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
 * @file Main.cpp
 * 
 * @version     0.1
 * @author      offa
 * @date        9.10.2014
 * 
 * Start the program; contains the <code>main()</code>-function.
 */

#include <QApplication>
#include "app/MainWindow.h"

/**
 * Entry point of the application.
 * 
 * @param argc      Argument count
 * @param argv      Argument vector
 * @return          Returncode of the application
 */
int main(int argc, char** argv)
{
    QApplication::setApplicationName("ElsockController");
    QApplication::setApplicationVersion(ELSOCK_VERSION);
    
    QApplication app(argc, argv);

    MainWindow window(app.applicationName(), app.applicationVersion());
    window.show();
    
    return app.exec();
}

