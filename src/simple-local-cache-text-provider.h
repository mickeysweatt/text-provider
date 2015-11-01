//
//  SimpleLocalCacheTextProvider.h
//
//  Created by admin on 10/29/15.
//  Copyright (c) 2015 admin. All rights reserved.
//

#ifndef INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER
#define INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER

#include "TextProviderProtocol.h"
#include <string>
#include <vector>
#include <stdint.h>

class SimpleLocalCacheTextProvider : public TextProviderProtocol ,
									public std::enable_shared_from_this<SimpleLocalCacheTextProvider>
{
  public:
  	SimpleLocalCacheTextProvider(const std::string& filename,
  								 size_t start_line,
  								 size_t max_line,
  								 size_t max_bytes = SIZE_MAX);

  	~SimpleLocalCacheTextProvider() override = default;

	std::string read_n_th_line(size_t n) override;

	size_t file_length();

 private:
 	std::string filename_;
 	std::vector<std::string> cache_;
 	size_t cache_start_line_;
 	size_t cache_end_line_;
 	size_t cache_max_bytes_;
 	size_t files_num_lines_;
};


#endif /* INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER */
