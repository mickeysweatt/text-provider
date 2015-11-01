// CacheProtocol.h                                                     -*-C++-*-
#ifndef INCLUDED_CACHE_PROTOCOL_H
#define INCLUDED_CACHE_PROTOCOL_H

//@Purpose: Provde an abstract protocol for a line cache.
//
//@Classes:
//  CacheProtocol: A pure abstract protocol used for line caches

#include <string>

                    // ===================
                    // class CacheProtocol
                    // ===================

class CacheProtocol {
    // This class provides a generic interface to be use for line caches. It
    // intends to leave the caching policy, including cache size, as a decision
    // of concreate implementations.
  public:
    // CREATORS
    virtual ~CacheProtocol();
        // Destory this object. Note left concreate, non-inlined to gurantee
        // that a vtable is generated.

    // MANIPULATORS
    virtual bool get_line_if_cached(size_t line_num, std::string *line) = 0;
        // Search the cache for the line with the specified, 'line_num', and if
        // found set the specified 'line' to its value. Return tre if the line
        // is loaded, and false otherwise. The behavior is undefined unless the
        // 'line_num' represents a valid line number in the file being cache.
        // Note that this method is a manipulator to allow concreate
        // implementations to make caching decisions.

    virtual size_t cache_size() const = 0;
        // Return the number of lines in this cache.
};
#endif //INCLUDED_CACHE_PROTOCOL_H