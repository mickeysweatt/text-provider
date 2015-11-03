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

#include <boost/asio.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include "text-provider-protocol.h"

class Session : public std::enable_shared_from_this<Session>
// Encapsulates a connection to a client
{
private:
    enum { max_length = 1024 };

public:
  Session(boost::asio::ip::tcp::socket          socket,
          std::shared_ptr<TextProviderProtocol> provider);

  int start();

private:
  int do_read();
  // Read from a client, return when client ends session.

  int process_command(size_t length);
  // The core implementaion of the specificed protocol

  int do_write(std::ostream& output);
  // Response to the user

private:
  boost::asio::ip::tcp::socket          socket_;
  char                                  data_[max_length];
  boost::asio::streambuf                write_buffer_;
  std::shared_ptr<TextProviderProtocol> provider_;
};

class TcpServer
{
public:
  TcpServer(boost::asio::io_service&               io_service,
             std::shared_ptr<TextProviderProtocol> provider);

private:
  void do_accept();

private:
  boost::asio::ip::tcp::acceptor acceptor_;
  boost::asio::ip::tcp::socket socket_;
  std::shared_ptr<TextProviderProtocol> provider_;
};

inline
Session::Session(boost::asio::ip::tcp::socket socket,
          std::shared_ptr<TextProviderProtocol> provider)
: socket_(std::move(socket))
, provider_(provider)
{
}

inline
int Session::start() {
  return do_read();
}

#endif