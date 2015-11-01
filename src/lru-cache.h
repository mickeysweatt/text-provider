#ifndef INCLUDED_LRU_CACHE_PROTOCOL
#define INCLUDED_LRU_CACHE_PROTOCOL

#include <string>
#include <unordered_map>
#include <list>
#include "cache-protocol.h"
#include "util/GenericLruCache.h"
#include "util/file-utils.h"

class LruCache : public CacheProtocol {
  public:
    LruCache(const string& filename, size_t cache_size)
    : filename_(filename)
    , cache_(cache_size)
    {
    }

    bool get_line_if_cached(size_t line_num, std::string *line) override;

    size_t cache_size() const override {
      return cache_.size();
    }

  private:
    std::string filename_;
    GenericLruCache<size_t, std::string> cache_;
};
#endif //INCLUDED_LRU_CACHE_PROTOCOL