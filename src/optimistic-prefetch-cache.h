#ifndef INCLUDED_OPTIMISTIC_PREFETCH_CACHE
#define INCLUDED_OPTIMISTIC_PREFETCH_CACHE

#include "cache-protocol.h"
#include <vector>


class OptimisticPrefetchCache : public CacheProtocol {
  public:
	OptimisticPrefetchCache(const std::string& filename,
  							size_t start_line,
  							size_t max_line,
  							size_t max_bytes = SIZE_MAX);

	~OptimisticPrefetchCache() override = default;

	bool get_line_if_cached(size_t line_num, std::string *line) override;

	size_t cache_size() const override {
		return cache_.size();
	}
private:
	std::string filename_;
 	std::vector<std::string> cache_;
 	size_t cache_start_line_;
 	size_t cache_end_line_;
 	size_t cache_max_bytes_;
 	size_t files_num_lines_;
};

#endif // INCLUDED_OPTIMISTIC_PREFETCH_CACHE