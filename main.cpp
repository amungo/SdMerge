#include <cstdio>
#include <vector>

#include "utils.h"

using namespace std;

int main(int argc, char *argv[])
{
    if ( argc != 5 ) {
        fprintf( stderr, "Usage:\n" );
        fprintf( stderr, "SdMerge BLOCK_SIZE srcfileA srcfileB outfile\n\n" );
        return 0;
    }

    const char* f0name = argv[2];
    const char* f1name = argv[3];

    int block_size = atoi(argv[1]);
    FILE* f0   = fopen( f0name, "rb" );
    FILE* f1   = fopen( f1name, "rb" );
    FILE* fout = fopen( argv[4], "wb" );
    if ( !f0 || !f1 || !fout ) {
        fprintf(stderr, "File open error\n");
        return 1;
    }

    size_t f0size = get_file_size( f0name );
    size_t f1size = get_file_size( f1name );

    if ( f0size != f1size ) {
        fprintf( stderr, "Sizes of input files are not equal\n" );
        return 2;
    }

    size_t bcnt = f0size / block_size;

    if ( bcnt == 0 ) {
        fprintf( stderr, "Block size = %zu, file_size = %zu ==> blocks count is %zu.\n Too small files or block size is incorrect\n",
                 block_size, f0size, bcnt );
    }

    vector<uint8_t> buf0( block_size );
    vector<uint8_t> buf1( block_size );
    for ( int i = 0; i < bcnt; i++ ) {
        fread( buf0.data(), 1, block_size, f0 );
        fread( buf1.data(), 1, block_size, f1 );

        fwrite( buf0.data(), 1, block_size, fout );
        fwrite( buf1.data(), 1, block_size, fout );
    }

    fprintf( stderr, "Closing files now...\n" );

    fclose( f0 );
    fclose( f1 );
    fclose( fout );

    fprintf( stderr, "Done.\n" );

    return 0;
}
