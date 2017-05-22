#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <string>
#include <fstream>

int64_t get_file_size( const char* fname );
int64_t get_file_size( std::ifstream& fs  );

#endif // UTILS_H
