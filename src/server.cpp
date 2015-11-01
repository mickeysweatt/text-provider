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
#include <cstdlib>

using boost::asio::ip::tcp;
using std::string;

int session::process_command(size_t length)
{
  string command(data_, length);
  if (command == "QUIT\r\n") {
    return 0;
  }
  else if (strcmp(data_,"SHUTDOWN\r\n") == 0 ) {
    return 1;
  }
  else {
    std::istringstream iss(data_, strlen(data_));
    std::vector<string> tokens{std::istream_iterator<  string>{iss},
                               std::istream_iterator<string>{}};
     std::ostream output(&write_buffer_);
     bool success = false;
      if (tokens.size() == 2 || tokens[0] == "GET") {
        size_t line_num = atol(tokens[1].c_str());
        if (line_num > 0 && line_num < provider_->file_length()) {
          output << "OK\r\n" << provider_->read_n_th_line(line_num) << std::endl;
          success = true;
        }
      }
      if (!success) {
        output << "ERR\r\n";
      }
      return do_write(output);
  }
}

int session::do_read()
{
  auto self(shared_from_this());
  socket_.async_read_some(boost::asio::buffer(data_, max_length),
  [this, self](boost::system::error_code ec, std::size_t length)
  {
    if (!ec)
    {
      int status = process_command(length);
      if (status == 0) {
          return 0;
      }
      else if (status == 1) {
          socket_.get_io_service().stop();
      }
      else {
          return do_read();
      }
    }
    return 0;
  });
return 0;
}

int session::do_write(std::ostream& output)
{
  auto self(shared_from_this());
  boost::asio::async_write(socket_, write_buffer_,
      [this, self] (boost::system::error_code ec, std::size_t /*length*/)
      {
        if (!ec)
        {
          return do_read();
        }
        return -1;
      });
  return 0;
}

void tcp_server::do_accept()
{
  acceptor_.async_accept(socket_,
      [this](boost::system::error_code ec)
      {
        if (!ec)
        {
          std::make_shared<session>(std::move(socket_), provider_)->start();
        }

        do_accept();
      });
}