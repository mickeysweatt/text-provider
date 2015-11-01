#ifndef INCLUDED_CACHE_PROTOCOL_H
#define INCLUDED_CACHE_PROTOCOL_H

#include <string>

class CacheProtocol {
  public:
	virtual ~CacheProtocol();

	virtual bool get_line_if_cached(size_t line_num, std::string *line) = 0;

	virtual size_t cache_size() const = 0;
};
#endif //INCLUDED_CACHE_PROTOCOL_H