#ifndef INCLUDED_CACHE_PROTOCOL_H
#define INCLUDED_CACHE_PROTOCOL_H

#include <string>

class CacheProtocol {
  public:
	virtual ~CacheProtocol() = default;

	virtual bool get_line_if_cached(std::string *line);

	virtual size_t cache_size() const = 0;
};
#endif //INCLUDED_CACHE_PROTOCOL_H