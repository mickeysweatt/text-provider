// FileUtils.h                                                         -*-C++-*-
#ifndef INCLUDED_UTIL_FILE_UTIL
#define INCLUDED_UTIL_FILE_UTIL
//@Purpose: Provide a utility functions for interacting with files.
//
//@Classes:
//  FileUtils: A utility class for interacting with files.

#include <fstream>

                    // ================
                    // class FileUtils
                    // ================
class FileUtils {
  public:
    // CLASS METHODS
    static size_t filesize(const std::string& filename);
    // Get the number of bytes in the file with the specified 'filename'.

    static size_t linecount(const std::string& filename);
    // Get the number of lines in the file with the specified 'filename'

    static std::string get_nth_line(const std::string& filename,
                                    size_t line_num);
    // Return the the line in the file with the specified 'filename' with
    // the specifed 'line_num'.
};
//==============================================================================
//                             INLINE FUNCTION DEFINTIONS
//==============================================================================
// CLASS METHODS
// Defintions influnced by stack overflow post regarding optimal ways to perfrom
// each task.
inline size_t FileUtils::filesize(const std::string& filename) {
  std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
  return static_cast<size_t>(in.tellg());
}

inline size_t FileUtils::linecount(const std::string& filename) {
  std::ifstream in (filename);
  // new lines will be skipped unless we stop it from happening
  in.unsetf(std::ios_base::skipws);
  // count the newlines with an algorithm specialized for counting:
  size_t line_count = std::count(
      std::istream_iterator<char>(in),
      std::istream_iterator<char>(),
      '\n');
  return line_count;
}

inline std::string FileUtils::get_nth_line(const std::string& filename,
                                           size_t line_num) {
  std::ifstream input(filename.c_str());
  for (auto i = 0; i < line_num; ++i) {
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  std::string line;
  std::getline(input, line);
  return line;
}


#endif // INCLUDED_UTIL_FILE_UTIL