#include "optimistic-prefetch-cache.h"
#include <fstream>
#include "util/file-utils.h"
using std::string;

OptimisticPrefetchCache::OptimisticPrefetchCache(
	const string& filename,
	size_t start_line,
	size_t max_line,
	size_t max_bytes)
:  	filename_(filename),
	cache_start_line_(start_line),
 	cache_end_line_(max_line),
 	cache_max_bytes_(max_bytes)
{
}

bool OptimisticPrefetchCache::get_line_if_cached(size_t line_num, std::string *line) {
	std::ifstream input(filename_.c_str());
	// if the line is not in cache, reset the cache to start at this line and
	// get all the lines that potentially can fit into cache
	if (line_num > cache_end_line_ || line_num < cache_start_line_) {
		cache_.resize(0);
		cache_start_line_ = line_num;
		cache_end_line_ = line_num + cache_max_bytes_;
	}
	// if the cache is empty (fill it)
	if (cache_.empty()) {
		// reserve the maximum number of lines
		cache_.reserve(cache_end_line_ - cache_start_line_ + 1);
		// ignore the lines of the file before the start_line
		for (auto i = 0; i < cache_start_line_; ++i) {
    		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
  		// read the lines into cache
  		size_t curr_line = cache_start_line_;
  		size_t num_bytes_read = 0;
		for (std::string line; curr_line <= cache_end_line_ &&
							   num_bytes_read < cache_max_bytes_	 &&
							   std::getline(input, line);) {
			cache_.push_back(line);
			curr_line++;
			num_bytes_read += line.length();
		}
		cache_.shrink_to_fit();
	}
	*line = cache_[line_num + 1];
	return true;
}
