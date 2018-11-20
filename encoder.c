#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[] )
{
  const int bmpHeaderSize = 54;
  const int maxMessageSize = 1000;
  int i;
  int currentMessagePosition=0;
  char c;
  char msg[maxMessageSize];
  FILE *imgIN = NULL;
  FILE *imgOUT = NULL;
  
  if( argc < 4 ){
    printf( "Usage: %s source_bmp output_bmp secret message.\n", argv[0] );
    return 1;
  }
  
  imgIN = fopen( argv[1], "rb" );
  if( imgIN == NULL ){
    printf( "Could not open the input bmp file.\n" );
    return 1;
  }

  imgOUT = fopen( argv[2], "wb" );
  if( imgOUT == NULL ){
    printf( "Could not open the output bmp file.\n" );
    return 1;
  }  

	// read message in args
  for( i=3; i<argc; i++ ){
    strcpy( msg+currentMessagePosition, argv[i] );
    currentMessagePosition += strlen(argv[i]);

    if( i<argc-1 )
      msg[currentMessagePosition] = ' ';
      currentMessagePosition++;
  }
  msg[currentMessagePosition] = '\0';
  
  printf(msg);
  return 0;
}
