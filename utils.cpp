#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

#include "utils.h"

using namespace std;

int64_t get_file_size(const char *fname) {
    std::ifstream f (fname, std::ifstream::binary);

    if ( f ) {
        int64_t sz = get_file_size( f );
        f.close();
        return sz;
    } else {
        throw runtime_error( "get_file_size(): File IO error - " + string(fname) );
    }
    return 0;
}

int64_t get_file_size(std::ifstream& f) {
    if ( f.is_open() ) {
        std::streampos old_pos = f.tellg();
        f.seekg(0, f.end);
        int64_t sz = f.tellg();
        f.seekg( old_pos, f.beg );
        return sz;
    } else {
        throw runtime_error( "get_file_size(): File error" );
    }
}
