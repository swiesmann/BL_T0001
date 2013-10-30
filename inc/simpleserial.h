#ifndef INC_SIMPLESERIAL_H_
#define INC_SIMPLESERIAL_H_

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


#include <boost/asio.hpp>
#include <string>

#include "./apitypes.h"
#include "./cmd_def.h"


// don't pollute namespace (no 'using namespace'),
// but make typing a little easier
namespace bio = ::boost::asio;
typedef ::bio::serial_port_base bio_spb;


class SimpleSerial {
    private:
    static ::bio::io_service*  io_srvc_;
    static ::bio::serial_port* srl_port_;

    public:
    static void InitSerial(std::string port, uint16 baud_rate, uint8 char_size,
                    bio_spb::parity::type parity_type,
                    bio_spb::stop_bits::type stop_bits_type,
                    bio_spb::flow_control::type flow_ctrl_type);

    static void WriteBleMessage(uint8 len1, uint8* data1,
                                   uint16 len2, uint8* data2);

    static int ReadBleMessage();
};


#endif  // INC_SIMPLESERIAL_H_