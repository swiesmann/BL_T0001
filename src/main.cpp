/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Simon Wiesmann
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstddef>

#include "../inc/simpleserial.h"


// don't pollute namespace (no 'using namespace'),
// but make typing a little easier
namespace bio = ::boost::asio;
typedef ::bio::serial_port_base bio_spb;

void solveThisIssue();

void print_help() {
    printf("\tUsage: BL_T0001 COM-port\n");
}


int main(int argc, char* argv[]) {
    // workaround for eclipse on windows
    solveThisIssue();

    printf(">> Bluegiga Demo application to scan devices - brought to you by BLELabs <<\n");

    // we expect at least one input parameter (serial interface)
    if (argc < 2) {
        print_help();
        exit(-1);
    }


    try {
        // confirm which device is going to be used
        printf("device: %s \n", argv[1]);

        // keep original tutorial settings
        SimpleSerial::InitSerial(argv[1],           // serial port
                57600,                              // baud rate
                8,                                  // character size
                bio_spb::parity::none,              // no parity bit
                bio_spb::stop_bits::one,            // one stop bit
                bio_spb::flow_control::hardware);   // hardware flow control

        // tell the bluegiga library which function to use for serial output
        bglib_output = SimpleSerial::WriteBleMessage;

        // stop previous operation
        printf("[>] ble_cmd_gap_end_procedure()\n");
        ble_cmd_gap_end_procedure();

        // read the response to ble_cmd_gap_end_procedure
        if (SimpleSerial::ReadBleMessage()) {
            fprintf(stderr, "Error reading message. "
                    "Expected ble_rsp_gap_end_procedure.\n");
            return 1;
        }

        // get connection status, current command will be handled in response
        printf("[>] ble_cmd_connection_get_status(0)\n");
        ble_cmd_connection_get_status(0);

        // process responses from scan (ble_cmd_connection_get_status)
        while (true) {
            printf("----------------------------------------\n");
            if (SimpleSerial::ReadBleMessage()) {
                fprintf(stderr, "Error reading message\n");
                break;
            }
        }
    } catch(const boost::system::system_error& e) {
        fprintf(stderr, "Error: %s \n", e.what());
        return 1;
    }
}


// Eclipse Auto Formatter fails after setvbuf line, that's why these statements are at the end of the file
/**
 * @brief workaround for eclipse on windows (http://wiki.eclipse.org/CDT/User/FAQ#Eclipse_console_does_not_show_output_on_Windows)
 */
inline void solveThisIssue() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}
