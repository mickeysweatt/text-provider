#include <boost/asio.hpp>
#include <iostream>

#include "server.h"
#include "util/file-utils.h"
#include "text-provider-protocol.h"
#include "optimistic-prefetch-cache.h"
#include "lru-line-cache.h"
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
    if (file_length <= SMALL_FILE_SIZE) {
      cache = std::make_shared<OptimisticPrefetchCache>(filename,
                                                        0,
                                                        file_length);
    }
    // otherwise use a large lru cache
    else {
      cache = std::make_shared<LruLineCache>(filename,
                                             SMALL_FILE_SIZE);
    }
    provider = std::make_shared<SimpleLocalCacheTextProvider>(filename,
                                                              cache);
    boost::asio::io_service io_service;
    TcpServer server(io_service, provider);
    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
  return 0;
}