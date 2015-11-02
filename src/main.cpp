#include <boost/asio.hpp>
#include <iostream>

#include "server.h"
#include "util/file-utils.h"
#include "text-provider-protocol.h"
#include "optimistic-prefetch-cache.h"
#include "simple-local-cache-text-provider.h"

int main(int argc, char *argv[])
{
  enum { SMALL_FILE_SIZE = 7000000000 }; // ~7GB
  if (argc != 2) {
    std::cerr << "Usage: text-provider <file-name>\n";
    return 1;
  }
  try
  {
    std::string filename(argv[1]);
    size_t file_length = FileUtils::filesize(filename);
    std::shared_ptr<TextProviderProtocol> provider;
    std::shared_ptr<CacheProtocol> cache;
    // If the file is small enough to cache the whole thing do so.
    size_t cache_size =
        file_length <= SMALL_FILE_SIZE ? file_length : SMALL_FILE_SIZE;
    cache = std::make_shared<OptimisticPrefetchCache>(filename,
                                                      0,
                                                      cache_size);
    provider = std::make_shared<SimpleLocalCacheTextProvider>(filename,
                                                              cache);
    boost::asio::io_service io_service;
    tcp_server server(io_service, provider);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}