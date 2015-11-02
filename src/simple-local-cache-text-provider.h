//
//  SimpleLocalCacheTextProvider.h
//
//  Created by admin on 10/29/15.
//  Copyright (c) 2015 admin. All rights reserved.
//

#ifndef INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER
#define INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER

#include "text-provider-protocol.h"
#include "cache-protocol.h"
#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

class SimpleLocalCacheTextProvider : public TextProviderProtocol ,
									public std::enable_shared_from_this<SimpleLocalCacheTextProvider>
{
  public:
  	SimpleLocalCacheTextProvider(const std::string& filename,
  								 std::shared_ptr<CacheProtocol> cache)
  	: filename_(filename)
  	, cache_(cache)
  	{
  	}

  	~SimpleLocalCacheTextProvider() override = default;

	std::string read_n_th_line(size_t n) override;

	size_t file_length() override;

 private:
 	size_t files_num_lines_;
 	std::string filename_;
 	std::shared_ptr<CacheProtocol> cache_;
 };

#endif /* INCLUDED_SIMPLE_LOCAL_CACHE_TEXT_PROVIDER */
