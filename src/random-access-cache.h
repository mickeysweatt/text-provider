#ifndef INCLUDED_RANDOM_ACCESS_CACHE
#define INCLUDED_RANDOM_ACCESS_CACHE

#include "cache-protocol.h"

class RandomAccessCache : public CacheProtocol {
  // This class provides a simple cache that caches no lines. Optimal for large
  // files in which cache a particular line has no benefit in the common case.
  public:
    RandomAccessCache() = default;

    ~RandomAccessCache() override {};

    bool get_line_if_cached(size_t line_num, std::string *line) override {
      return false;
    }

    size_t cache_size() const override {
      return 0;
    }
};

#endif // INCLUDED_RANDOM_ACCESS_CACHE