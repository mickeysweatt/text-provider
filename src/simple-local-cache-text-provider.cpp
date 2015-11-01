#include "simple-local-cache-text-provider.h"
#include <fstream>
#include "util/file-utils.h"

using std::string;


size_t SimpleLocalCacheTextProvider::file_length()
{
	if (files_num_lines_ == 0) {
		files_num_lines_ = FileUtils::linecount(filename_);
	}
	return files_num_lines_;
}

std::string SimpleLocalCacheTextProvider::read_n_th_line(size_t n)
{
	string line;
	cache_->get_line_if_cached(n, &line);
	return line;
}