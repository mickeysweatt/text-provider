#include "lru-line-cache.h"
#include "util/file-utils.h"

bool LruLineCache::get_line_if_cached(size_t line_num, std::string *line)
{
  if (!cache_.exists(line_num)) {
    string line = FileUtils::get_nth_line(filename_, line_num);
    cache_.put(line_num, line);
  }
  *line = cache_.get(line_num);
  return true;
}