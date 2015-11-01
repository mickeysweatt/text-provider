#ifndef INCLUDED_RANDOM_ACCESS_CACHE
#define INCLUDED_RANDOM_ACCESS_CACHE

#include "cache-protocol.h"

class RandomAccessCache : public CacheProtocol {
  public:
	RandomAccessCache() = default;

	~RandomAccessCache() override {};

	bool get_line_if_cached(std::string *line) override {
		return false;
	}

	size_t cache_size() const override {
		return 0;
	}
};

#endif // INCLUDED_RANDOM_ACCESS_CACHE