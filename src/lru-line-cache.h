// LruCache.h                                                          -*-C++-*-
#ifndef INCLUDED_LRU_LINE_CACHE
#define INCLUDED_LRU_LINE_CACHE

//@Purpose: Provide an LruLineCache
//
//@Classes:
//  mrm::HTTPServer: a simple cached http-proxy server

#include <string>

#include "cache-protocol.h"
#include "util/GenericLruCache.h"

class LruLineCache : public CacheProtocol {
  public:
    LruLineCache(const string& filename, size_t cache_size);

    bool get_line_if_cached(size_t line_num, std::string *line) override;

    size_t cache_size() const override;

  private:
    std::string filename_;
    GenericLruCache<size_t, std::string> cache_;
};

inline
LruLineCache::LruLineCache(const string& filename, size_t cache_size)
: filename_(filename)
, cache_(cache_size)
{
}

inline
size_t LruLineCache::cache_size() const {
  return cache_.size();
}

#endif //INCLUDED_LRU_CACHE_PROTOCOL