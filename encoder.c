#include <stdio.h> 
#include <string.h>

const int bmpHeaderSize = 54;
const int maxMessageSize = 1000;
unsigned int biBitCount = 0;
unsigned int biCompression = 0;
int i;
int readCode;
int msgIdx = 0;
int imgIdx = 0;
int bitIdx = 0;
int currentMessagePosition = 0;
char c;
FILE * imgIN = NULL;
FILE * imgOUT = NULL;

int main(int argc, char * argv[]) {
    if (argc < 4) {
        printf("--- ENCODER: Usage: %s bmp_in bmp_out secret message ---\n", argv[0]);
        return 1;
    }

    // open and check imgIN
    imgIN = fopen(argv[1], "rb");
    if (imgIN == NULL) {
        printf("--- ENCODER: Could not open the IN bmp file ---\n");
        return 1;
    }
    fseek(imgIN, 0L, SEEK_SET);
    char bfType[3];
    bfType[2] = '\0';
    if (fread(bfType, sizeof(char), 2, imgIN) && (strcmp("BM", bfType) == 0)) {
        printf("--- ENCODER: file actually is a bmp file ---\n");
    } else {
        printf("--- ENCODER: file actually is not a bmp file ---\n");
        return 1;
    }

    fseek(imgIN, 28L, SEEK_SET);
    if (fread( & biBitCount, sizeof(char), 2, imgIN)) {
        fseek(imgIN, 30L, SEEK_SET);
        if (fread( & biCompression, sizeof(char), 4, imgIN) && (biCompression == 0) && biBitCount != 0) {
            printf("--- ENCODER: file actually is not compressed ( BI_RGB ) ---\n");
            printf("--- ENCODER: biBitCount and biCompression is OK ---\n");
            fseek(imgIN, 0L, SEEK_SET);
        } else if (fread( & biCompression, sizeof(char), 4, imgIN) && (biCompression == 3) && (biBitCount == 16 || biBitCount == 32)) {
            printf("--- ENCODER: file actually is not compressed ( BI_BITFIELDS ) ---\n");
            printf("--- ENCODER: biBitCount and biCompression is OK ---\n");
            fseek(imgIN, 0L, SEEK_SET);
        } else {
            printf("--- ENCODER: biBitCount and biCompression is NOT OK ---\n");
            return 1;
        }
    } else {
        printf("--- ENCODER: can not read biBitCount ---\n");
        return 1;
    }

    // open and check imgOUT
    imgOUT = fopen(argv[2], "wb");
    if (imgOUT == NULL) {
        printf("Could not open the OUT bmp file.\n");
        return 1;
    }

    // read message in args
    char msg[maxMessageSize];
    for (i = 3; i < argc; i++) {
        strcpy(msg + currentMessagePosition, argv[i]);
        currentMessagePosition += strlen(argv[i]);

        if (i < argc - 1)
            msg[currentMessagePosition] = ' ';
        currentMessagePosition++;
    }
    msg[currentMessagePosition] = '\0'; //null term

    if (sizeof(msg[currentMessagePosition] / sizeof(char)) > maxMessageSize) {
        printf("--- ENCODER: size of message is more than 1000 symbols ---\n");
        return 1;
    }

    while ((readCode = fgetc(imgIN)) != EOF) {
        c = (char) readCode; // pixel value save

        // first 54 bits skip cuz they are header
        if (imgIdx >= bmpHeaderSize && msgIdx <= strlen(msg)) {
            // bit mask
            char bit_mask = 1 << bitIdx;
            // for lowest order    
            if ((msg[msgIdx] & bit_mask) > 0)
                c |= 1;
            else
                c &= 254;
            // inc bit index
            bitIdx++;
            // move to next byte
            if (bitIdx >= 8) {
                bitIdx = 0;
                msgIdx++;
            }
        }

        // copy bites to new file
        fputc(c, imgOUT);
        imgIdx++;
    }

    printf("--- ENCODER: Secret message with %d bytes is storing in %s file ---\n", imgIdx, argv[2]);

    fclose(imgIN);
    fclose(imgOUT);

    return 0;
}