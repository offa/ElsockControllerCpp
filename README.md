# Elsock Controller

A controller application / library for [Elsock](https://github.com/forflo/arduino_elsock)-devices.

It can be used as a stand-alone application or as a library for other projects.

## Requirements

 * **Qt 5** - Network / Widget (if build as application)
 * **CMake** - building
 * **Doxygen** - building of documentation *(OPTIONAL)*

## Building

Building the library and application:

    mkdir build
    cmake ..
    make

Additional `make`-targets:

    # Builds just the library
    make Elsock

    # Builds the application (includes the library)
    make ElsockController 

## Example

```cpp
#include <api/ElsockController.h>

/* ... */

// Connect to elsock host
ElsockController ec("http", "127.0.0.1");

// Set device #7 to ON
ec.sendCommand(DEVICE_7, ON);
// Set device #9 to ON
ec.sendCommand(DEVICE_9, ON);

// Toggle all devices
ec.sendToggleAll();

// Receive status
ElsockData response = ec.getStatus();

// Get status of device #4
Status statusDev4 = response[DEVICE_4];
// Get status of device #9
Status statusDev9 = response[DEVICE_9];
    
// Print status of devices #4 and #9
std::cout << "Device #4: " << ( statusDev4 == ON ? "ON" : "not ON" )
          << "\n"
          << "Device #9: " << ( statusDev9 == ON ? "ON" : "not ON" )
          << std::endl;

// Turn off all devices
ec.sendCommand(ALL, OFF);
```
*Don't forget to link **Elsock** and **Qt 5 Network**!*


## License

**GPLv3:**

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
