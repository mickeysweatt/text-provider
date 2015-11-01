#ifndef INCLUDED_UTIL_FILE_UTIL
#define INCLUDED_UTIL_FILE_UTIL

#include <fstream>
class FileUtils {
public:
	static size_t filesize(const std::string& filename)
	{
	    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
	    return static_cast<size_t>(in.tellg());
	}
	static size_t linecount(const std::string& filename) {
		std::ifstream in (filename);
		// new lines will be skipped unless we stop it from happening:
	    in.unsetf(std::ios_base::skipws);
	    // count the newlines with an algorithm specialized for counting:
	    size_t line_count = std::count(
	        std::istream_iterator<char>(in),
	        std::istream_iterator<char>(),
	        '\n');
	    return line_count;
	}
};
#endif // INCLUDED_UTIL_FILE_UTIL