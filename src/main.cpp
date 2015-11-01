#include <boost/asio.hpp>
#include <iostream>
#include "server.h"
#include "util/file-utils.h"
#include "TextProviderProtocol.h"
#include "simple-local-cache-text-provider.h"

int main(int argc, char *argv[])
{
    const size_t SMALL_FILE_SIZE = 4294967296; // 4GB
    if (argc != 2) {
       std::cerr << "Usage: text-provider <file-name>\n";
      return 1;
    }
    try
    {
        std::string filename(argv[1]);
        size_t file_length = FileUtils::filesize(filename);
        std::shared_ptr<TextProviderProtocol> provider;
        size_t cache_size = file_length <= SMALL_FILE_SIZE ? file_length :
                            SMALL_FILE_SIZE;
        provider = std::make_shared<SimpleLocalCacheTextProvider>(filename,
                                                                 0,
                                                                 cache_size);
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