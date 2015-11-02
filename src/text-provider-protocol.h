//
//  text-provider-protocol.h
//
#ifndef INCLUDED_TEXT_PROVIDER_PROTOCOL
#define INCLUDED_TEXT_PROVIDER_PROTOCOL

#include <string>

class TextProviderProtocol {
  public:
  	virtual ~TextProviderProtocol() = default;

	virtual std::string read_n_th_line(size_t n) = 0;

	virtual size_t file_length() = 0;
};


#endif /* INCLUDED_TEXT_PROVIDER _PROTOCOL */
