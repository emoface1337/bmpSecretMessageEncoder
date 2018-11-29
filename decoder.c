#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[] )
{
  const int bmpHeaderSize = 54;
  const int maxMessageSize = 1000;
  int i;
  int c;
  int imgIdx = 0;
  int msgIdx = 0;
  int bitIdx = 0;
  char msg[maxMessageSize];
  FILE *imgIN = NULL;
  
  if( argc < 2 ){
    printf( "Usage: %s bmp_in (where is secret message).\n", argv[0] );
    return 1;
  }

  
  imgIN = fopen( argv[1], "rb" );

  if( imgIN == NULL ){
    printf( "Could not open the IN bmp file.\n" );
    return 1;
  }

	// set msg to 0
  for( i=0; i < maxMessageSize; i++ )
    msg[i] = 0;

  // while loop for extracting lowest bits
  while( ( c = fgetc( imgIN )) != EOF ){
 
	 // first 54 bits skip cuz they are header
   if( imgIdx >= bmpHeaderSize ){
    
     // check lowest bit 
		 if( ( c & 1 )  > 0 )
        // if 1 - next need to write into msg
        msg[msgIdx] |= 1 << bitIdx;

      // inc bit index
      bitIdx++;

			// move to next byte
      if( bitIdx >= 8 ){
       if( msg[msgIdx] == '\0' )
          break; // if msg in index == null term
        bitIdx = 0;
        msgIdx++;
      }      
    }
    imgIdx++;
  }
  printf( "---\nDECODER: secret message: %s \n--- \n", msg );
  fclose(imgIN);
  return 0;
}