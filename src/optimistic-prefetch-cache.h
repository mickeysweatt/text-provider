// OptimisticPrefetchCache.h                                                     -*-C++-*-
#ifndef INCLUDED_OPTIMISTIC_PREFETCH_CACHE
#define INCLUDED_OPTIMISTIC_PREFETCH_CACHE

//@Purpose: Create a cache that optimstically prefetching portions of a file
//
//@Classes:
//  OptimsticPrefetchCache: A cache which upon cache miss fetches prefetches many lines

#include "cache-protocol.h"
#include <vector>

                    // =============================
                    // class OptimisticPrefetchCache
                    // =============================

class OptimisticPrefetchCache : public CacheProtocol {
  public:
    OptimisticPrefetchCache(const std::string& filename,
                            size_t             start_line,
                            size_t             end_line,
                            size_t             max_bytes = SIZE_MAX);
      // Create a new cache large enough to hold at least the lines between the
      // specified 'start_line' and the specified 'end_line' or the specified
      // 'max_bytes' bytes, whichever is smaller, from a file with the
      // specified 'filename'. The behavior is undefined unless 'filename'
      // references a valid readable file and 'start_line' and 'end_line'
      // represent valid lines numbers in that file, and 'start_line' >=
      // 'end_line'.

    ~OptimisticPrefetchCache() override = default;
      // Destroy this object.

    bool get_line_if_cached(size_t line_num, std::string *line) override;
      // Search the cache for the line with the specified, 'line_num', and if
      // found set the specified 'line' to its value. Return tre if the line
      // is loaded, and false otherwise. The behavior is undefined unless the
      // 'line_num' represents a valid line number in the file being cache. Upon
      // cache miss this cache will fetch at least the line with 'line_num',
      // and may fetch other lines as well.

    size_t cache_size() const override;

  private:
    std::string              filename_;
    std::vector<std::string> cache_;
    size_t                   cache_start_line_;
    size_t                   cache_end_line_;
    size_t                   cache_max_bytes_;
    size_t                   files_num_lines_;
};

inline
size_t OptimisticPrefetchCache::cache_size() const {
    return cache_.size();
}

#endif // INCLUDED_OPTIMISTIC_PREFETCH_CACHE