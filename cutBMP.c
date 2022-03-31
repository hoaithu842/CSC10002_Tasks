#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#define MAX 1000
#pragma pack(1)

struct DIBHeader{
    uint16_t sign;
    uint32_t fileSize;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t byteOffset;
    uint32_t DIBSize;
    uint32_t width;
    uint32_t height;
    uint16_t colorPlanes;
    uint16_t colorDepth;
    uint32_t compressAlgo;
    uint32_t arraySize;
    uint32_t horizontalRes;
    uint32_t verticalRes;
    uint32_t colorsinTable;
    uint32_t importantColors;
};
short checkAndAssignArguments(int argc, char **argv, int* cutHeight, int* cutWidth){
    if (argc<4){
        printf("Wrong syntax!");
        return 0;
    }
    
    if (argv[2][1]=='h') *cutHeight = atoi(argv[3]);
    else if (argv[2][1]=='w') *cutWidth = atoi(argv[3]);
    
    if (argc>4){
        if (argv[4][1]=='h') *cutHeight = atoi(argv[5]);
        else if (argv[4][1]=='w') *cutWidth = atoi(argv[5]);
    }

    return 1;
}


short checkAndReadBMPFile(char *filename, struct DIBHeader *header, int *rowLength, unsigned char **pixelArray){
    FILE *fi = fopen(filename, "rb");
        if (!fi){
            printf("Cannot open file to read");
            return 0;
        }

    fseek(fi, 0, SEEK_SET);
    fread(header, sizeof(*header), 1, fi);

        if ((*header).sign != 0x4D42){
            printf("Not a BMP file");
            return 0;
        }

    int padding = (4-((*header).width*((*header).colorDepth/8))%4)%4;
    *rowLength = (*header).width*((*header).colorDepth/8) + padding;
    int pixelArraySize = ((*header).height * (*rowLength));
	*pixelArray = (unsigned char*) malloc (pixelArraySize);

	fseek(fi, (*header).byteOffset, SEEK_SET);
	fread (*pixelArray, sizeof(char), pixelArraySize, fi);

    fclose(fi);
    return 1;
}


void initBMPFileFormat(int i, int j, int cutHeight, int cutWidth, struct DIBHeader header, struct DIBHeader *tmpHeader){
    *tmpHeader = header;
    (*tmpHeader).width = header.width/cutWidth;
    (*tmpHeader).height = header.height/cutHeight;

    if (i==cutWidth-1) (*tmpHeader).width = header.width - (header.width/cutWidth)*(cutWidth-1);
    if (j==cutHeight-1) (*tmpHeader).height = header.height - (header.height/cutHeight)*(cutHeight-1);

    (*tmpHeader).arraySize = (*tmpHeader).height * (*tmpHeader).width;
}


void initNewBMPFileName(char *filename, int stt){
    char st[MAX];
    itoa(stt, st, 10);
    filename[strlen(filename)-4] = '\0';
    strcat(filename, st);
    st[0] = '.'; st[1] = 'b'; st[2] = 'm'; st[3] = 'p'; st[4] = '\0';
    strcat(filename, st);
}


void createNewBMPFile(int no, char *argv, struct DIBHeader tmpHeader, unsigned char *tmpPixelArray, int tmpPixelArraySize, struct DIBHeader header){
    char *filename = strdup(argv);
    initNewBMPFileName(filename, no);
    
    FILE *fo = fopen(filename, "wb");

    fseek(fo, 0, SEEK_SET);
    fwrite(&tmpHeader, sizeof(tmpHeader), 1, fo);

    fseek(fo, header.byteOffset, SEEK_SET);
    fwrite(tmpPixelArray, sizeof(char), tmpPixelArraySize, fo);

    fclose(fo);
}


void cutBMPFile(int cutHeight, int cutWidth, struct DIBHeader header, char *argv, int rowLength, unsigned char *pixelArray){
    struct DIBHeader tmpHeader;
    int firstH = 0, firstW;

    for (int i=0; i<cutHeight; i++){
        firstW = 0;
        for (int j=0; j<cutWidth; j++){

            initBMPFileFormat(i, j, cutHeight, cutWidth, header, &tmpHeader);

            int padding = (4-(tmpHeader.width*(tmpHeader.colorDepth/8))%4)%4;
            int tmpRowLength = tmpHeader.width*(tmpHeader.colorDepth/8) + padding;
            int tmpPixelArraySize = (tmpHeader.height * tmpRowLength);
            unsigned char *tmpPixelArray = (unsigned char*) malloc (tmpPixelArraySize);

            for (int k=0; k<tmpHeader.height; k++){
                for (int v=0; v<tmpRowLength; v++){
                    if (v<tmpRowLength-padding) tmpPixelArray[k*tmpRowLength+v] = pixelArray[(k+firstH)*(rowLength)+(firstW+v)];
                    else tmpPixelArray[k*tmpRowLength+v] = 0;
                }
            }

            firstW = firstW + (header.width/cutWidth)*(tmpHeader.colorDepth/8);

            createNewBMPFile(i*cutWidth+j+1, argv, tmpHeader, tmpPixelArray, tmpPixelArraySize, header);
            free(tmpPixelArray);

        }
        firstH = firstH + header.height/cutHeight;
    }
    printf("Successful...");
}
void release(unsigned char **pixelArray){
    free(pixelArray);
}
int main(int argc, char **argv){
    int cutHeight = 1, cutWidth = 1;
    struct DIBHeader header;
    int rowLength;
    unsigned char *pixelArray;
    
    if ( checkAndAssignArguments(argc, argv, &cutHeight, &cutWidth) == 0 ) return 0;
    if ( checkAndReadBMPFile(argv[1], &header, &rowLength, &pixelArray) == 0 ) return 0;

    cutBMPFile(cutHeight, cutWidth, header, argv[1], rowLength, pixelArray);
    release(&pixelArray);
    
    return 0;
}