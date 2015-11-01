#include "lru-cache.h"

bool LruCache::get_line_if_cached(size_t line_num, std::string *line)
{
      bool found = false;
      if (!cache_.exists(line_num)) {
        string line = FileUtils::get_nth_line(filename_, line_num);
        cache_.put(line_num, line);
        found = true;
      }
      *line = cache_.get(line_num);
      return found;
}