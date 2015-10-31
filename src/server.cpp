#include "server.h"

// Based on: ()
// server.h
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>


using boost::asio::ip::tcp;

// namespace {
// 	static std::string make_string(boost::asio::streambuf& streambuf)
//     {
// 	    return {buffers_begin(streambuf.data()),
// 	         buffers_end(streambuf.data())};
//     }
// }

// tcp_connection::pointer tcp_connection::create(boost::asio::io_service& io_service)
// {
//     return pointer(new tcp_connection(io_service));
// }

int session::process_command(size_t length)
{
    if (strcmp(data_,"QUIT\r\n") == 0 ) {
        return 0;
    }
    if (strcmp(data_,"SHUTDOWN\r\n") == 0 ) {
        return 1;
    }
    else {
        do_write(length);
        return do_read();
    }
}

// std::string tcp_connection::get_command() {
//     boost::asio::streambuf read_buffer;
//     auto bytes_transferred = read_until(socket_, read_buffer, '\n');
//     std::string command = make_string(read_buffer);
//     return command;
// }


void tcp_server::do_accept()
{
    acceptor_.async_accept(socket_,
        [this](boost::system::error_code ec)
        {
          if (!ec)
          {
            std::make_shared<session>(std::move(socket_))->start();
          }

          do_accept();
        });
}