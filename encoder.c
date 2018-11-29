#include <stdio.h>
#include <string.h>

const int bmpHeaderSize = 54;
const int maxMessageSize = 1000;
int i;
int readCode;
int msgIdx = 0;
int imgIdx = 0;
int bitIdx = 0;
int currentMessagePosition=0;
char c;
FILE *imgIN = NULL;
FILE *imgOUT = NULL;

int main(int argc, char *argv[] )
{
  char msg[maxMessageSize];
  if( argc < 4 ){
    printf( "Usage: %s bmp_in bmp_out secret message.\n", argv[0] );
    return 1;
  }

  // open and check imgIN
  imgIN = fopen( argv[1], "rb" );
  if( imgIN == NULL ){
    printf( "Could not open the IN bmp file.\n" );
    return 1;
  }
  // open and check imgOUT
  imgOUT = fopen( argv[2], "wb" );
  if( imgOUT == NULL ){
    printf( "Could not open the OUT bmp file.\n" );
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
  msg[currentMessagePosition] = '\0'; //null term
  
  while( ( readCode = fgetc( imgIN )) != EOF ){
    c = (char)readCode; // pixel value save

    // first 54 bits skip cuz they are header
    if( imgIdx >= bmpHeaderSize && msgIdx <= strlen( msg ) ){ 
      // bit mask
      char bit_mask = 1 << bitIdx;
      // for lowest order    
      if( ( msg[msgIdx] & bit_mask) > 0 )
        c |= 1;
      else
        c &= 254;
      // inc bit index
      bitIdx++;
      // move to next byte
      if( bitIdx >= 8 ){
        bitIdx = 0;
        msgIdx++;
      }      
    }

    // copy bites to new file
    fputc( c, imgOUT );
    imgIdx++;
  }

  printf( "---\nENCODER: Secret message with %d bytes is storing in socOUT.bmp file\n---\n", imgIdx );

  fclose(imgIN);
  fclose(imgOUT);
  
  return 0;
}
