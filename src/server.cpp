#include "server.h"

//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2015 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

namespace {
	static std::string make_string(boost::asio::streambuf& streambuf)
    {
	    return {buffers_begin(streambuf.data()),
	         buffers_end(streambuf.data())};
    }
}

tcp_connection::pointer tcp_connection::create(boost::asio::io_service& io_service)
{
    return pointer(new tcp_connection(io_service));
}

int tcp_connection::process_request()
{
    std::string command = get_command();
    if (command == "QUIT\r\n") {
        return 0;
    }
    else if (command == "SHUTDOWN\r\n") {
        return 1;
    }
    else {
        return process_request();
    }
}

std::string tcp_connection::get_command() {
    boost::asio::streambuf read_buffer;
    auto bytes_transferred = read_until(socket_, read_buffer, '\n');
    std::string command = make_string(read_buffer);
    return command;
}


void tcp_server::start_accept()
{
    tcp_connection::pointer new_connection = tcp_connection::create(
        acceptor_.get_io_service());
    std::cout << "Waiting for connection" << std::endl;

    acceptor_.async_accept(new_connection->socket(),
                           boost::bind(&tcp_server::handle_accept, this, new_connection,
                                       boost::asio::placeholders::error));
}

void tcp_server::handle_accept(tcp_connection::pointer new_connection,
                   const boost::system::error_code& error)
{
    std::cout << "Accepting connection" << std::endl;
    int status = -1;
    if (!error)
    {
        status = new_connection->process_request();
    }
    if (0 == status) {
        start_accept();
    }
}
