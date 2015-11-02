//
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// An asynchronous tcp server using boost asio based on:
// http://www.boost.org/doc/libs/1_54_0/doc/html/boost_asio/example/cpp11/echo/async_tcp_echo_server.cpp

#ifndef INCLUDED_SERVER_H
#define INCLUDED_SERVER_H

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <boost/asio.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include "text-provider-protocol.h"

class session : public std::enable_shared_from_this<session>
// Encapsulates a connection to a client
{
public:
  session(boost::asio::ip::tcp::socket socket,
          std::shared_ptr<TextProviderProtocol> provider)
    : socket_(std::move(socket))
    , provider_(provider)
  {
  }

  int start()
  {
    return do_read();
  }

private:
  int do_read();
  // Read from a client, return when client ends session.

  int process_command(size_t length);
  // The core implementaion of the specificed protocol

  int do_write(std::ostream& output);
  // Response to the user

  boost::asio::ip::tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  boost::asio::streambuf write_buffer_;
  std::shared_ptr<TextProviderProtocol> provider_;
};

class tcp_server
{
public:
  tcp_server(boost::asio::io_service& io_service,
             std::shared_ptr<TextProviderProtocol> provider)
    : acceptor_(io_service
    , boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(),
                                     10322)),
      socket_(io_service),
      provider_(provider)
  {
    do_accept();
  }

private:
  void do_accept();
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ip::tcp::socket socket_;
  std::shared_ptr<TextProviderProtocol> provider_;
};
#endif