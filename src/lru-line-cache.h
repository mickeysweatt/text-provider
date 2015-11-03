// LruCache.h                                                          -*-C++-*-
#ifndef INCLUDED_LRU_LINE_CACHE
#define INCLUDED_LRU_LINE_CACHE

//@Purpose: Provide an LruLineCache
//
//@Classes:
//  LruLineCache: A fixed size LRU line cache

#include <string>

#include "cache-protocol.h"
#include "util/GenericLruCache.h"

                    // ==================
                    // class LruLineCache
                    // ==================

class LruLineCache : public CacheProtocol {
    // This class provides a cache implementation using a least recently used
    // cache replacement policy.
  public:
    // CREATORS
    LruLineCache(const string& filename, size_t cache_size);
      // Create a new LruLineCache to cache up to the specifed 'cache_size'
      // lines from a file with the specified 'filename'. The behavior is
      // undefined unless 'filename' references a valid ASCII file to which the
      // user of this type has read access.

    ~LruLineCache() = default;
      // Destroy this object.

    // MANIPULATORS
    bool get_line_if_cached(size_t line_num, std::string *line) override;
      // Search the cache for the line with the specified, 'line_num', and if
      // found set the specified 'line' to its value. Return tre if the line
      // is loaded, and false otherwise. The behavior is undefined unless the
      // 'line_num' represents a valid line number in the file being cache.

    // ACCESORS
    size_t cache_size() const override;
      // Return the number of lines in this cache.

  private:
    // DATA
    std::string filename_;  // the name of the file
    GenericLruCache<size_t, std::string> cache_;  // the lru cache
};

//==============================================================================
//                             INLINE FUNCTION DEFINTIONS
//==============================================================================

// CREATORS
inline
LruLineCache::LruLineCache(const string& filename, size_t cache_size)
: filename_(filename)
, cache_(cache_size)
{
}

// ACCESSORS
inline
size_t LruLineCache::cache_size() const {
  return cache_.size();
}

#endif // INCLUDED_LRU_LINE_CACHE