#include <string.h>
#include <stdio.h>
#define BUFFER_SIZE 100
#define MAX 1000

void showHelp(){
    printf("Copies one or more files to another location.\n\n");
    printf("COPY\t[/D] [/V] [/N] [/Y | /-Y] [/Z] [/L] [/A | /B ] source [/A | /B]\n");
    printf("\t[+ source [/A | /B] [+ ...]] [destination [/A | /B]]\n\n");
    printf("source \t \t Specifies the file or files to be copied.\n");
    printf("/A \t \t Indicates an ASCII text file.\n");
    printf("/B \t \t Indicates a binary file.\n");
    printf("/D \t \t Allow the destination file to be created decrypted\n");
    printf("destination \t Specifies the directory and/or filename for the new file(s).\n");
    printf("/V \t \t Verifies that new files are written correctly.\n");
    printf("/N \t \t Uses short filename, if available, when copying a file with a\n");
    printf("\t \t non-8dot3 name.\n");
    printf("/Y \t \t Suppresses prompting to confirm you want to overwrite an\n");
    printf("\t \t existing destination file.\n");
    printf("/-Y \t \t Causes prompting to confirm you want to overwrite an\n");
    printf("\t \t existing destination file.\n");
    printf("/Z \t \t Copies networked files in restartable mode.\n");
    printf("/L \t \t If the source is a symbolic link, copy the link to the target\n");
    printf("\t \t instead of the actual file the source link points to.\n\n");
    printf("The switch /Y may be preset in the COPYCMD environment variable.\n");
    printf("This may be overridden with /-Y on the command line.  Default is\n");
    printf("to prompt on overwrites unless COPY command is being executed from\n");
    printf("within a batch script.\n\n");
    printf("To append files, specify a single file for destination, but multiple files\n");
    printf("for source (using wildcards or file1+file2+file3 format).\n\n");
}
void printWrongSyntax(){
    printf("Wrong syntax!");
}
void printSuccessfulMessage(){
    printf("\t 1 file(s) copied.");
}
void copyFile(const char *file1, const char *file2){
    FILE *f1 = fopen(file1, "rb");
    FILE *f2 = fopen(file2, "wb");

    if (!f1 || !f2){
        fprintf(stderr, "Error: cannot r or w file.");
    }

    char buffer[BUFFER_SIZE];
    int count;
    do{
        count = fread(buffer, 1, BUFFER_SIZE,f1);
        fwrite(buffer, 1, count, f2);
    } while (count == BUFFER_SIZE);
    fclose(f1);
    fclose(f2);
}
void appendFile(const char *file1, const char *file2){
    FILE *f1 = fopen(file1, "rb");
    FILE *f2 = fopen(file2, "ab");

    if (!f1 || !f2){
        fprintf(stderr, "Error: cannot r or w file.");
    }
    fwrite("\n", 1, 1, f2);
    char buffer[BUFFER_SIZE];
    int count;
    do{
        count = fread(buffer, 1, BUFFER_SIZE,f1);
        fwrite(buffer, 1, count, f2);
    } while (count == BUFFER_SIZE);
    fclose(f1);
    fclose(f2);
}
void lower(char *argv){
    if (strcmp(argv, "COPY/?")==0 || strcmp(argv, "COPY")==0){
        argv[0] = 'c'; argv[1] = 'o'; argv[2] = 'p'; argv[3] = 'y';}
}
void separate(char *argv, char *sourcefile, char *sourcefile2){
    int i = 0, tmp = 0;
    while (argv[i]!='+'){
        if (argv[i]!=' '){
            sourcefile[tmp] = argv[i];
            tmp++;
        }
        i++;
    }
    sourcefile[tmp] = '\0';
    tmp = 0;
    i++;
    while (argv[i]==' ') i++;
    while (i<strlen(argv)){
        sourcefile2[tmp] = argv[i];
        tmp++;
        i++;
    }
    sourcefile2[tmp] = '\0';
}
void adjust(char *sourcefile, char *destination){
    char *ptr = strchr(destination, '\\');
    if (ptr!=NULL){
        if (destination[strlen(destination)-1]!='\\'){
            destination[strlen(destination)] = '\\';
            destination[strlen(destination)] = '\0';
        }
        strcat(destination, sourcefile);
    }
}
void threeComponents(int argc, char **argv, char *ptr){
    if (argc==6){
        copyFile(argv[2], argv[5]);
        appendFile(argv[4], argv[5]);
    } else if (argv[2][strlen(argv[2])-1] == '+'){
        argv[2][strlen(argv[2])-1] = '\0';
        copyFile(argv[2], argv[4]);
        appendFile(argv[3], argv[4]);
    } else if (argv[3][0]=='+'){
        for (int i=0; i<strlen(argv[3])-1; i++) argv[3][i] = argv[3][i+1];
        argv[3][strlen(argv[3])-1] = '\0';
        copyFile(argv[2], argv[4]);
        appendFile(argv[3], argv[4]);
    } else if (ptr!=NULL){
        char sourcefile[MAX], sourcefile2[MAX];
        separate(argv[2], sourcefile, sourcefile2);
        copyFile(sourcefile, argv[3]);
        appendFile(sourcefile2, argv[3]);
    }
}
void twoComponents(char **argv){
    adjust(argv[2], argv[3]);
    copyFile(argv[2], argv[3]);
}
int main(int argc, char **argv){
    lower(argv[1]);
    if (strcmp(argv[1], "copy/?")==0 || ((strcmp(argv[1], "copy")==0 && ((strcmp(argv[2], "/?")==0) || (strcmp(argv[2], "/")==0 && strcmp(argv[3], "?")==0))))){
        showHelp();
        return 0;
    } else if (strcmp(argv[1], "copy")==0 && argc>=3){
        char *ptr = strchr(argv[2], '+');
        if (argc>=5 || ptr!=NULL){
            threeComponents(argc, argv, ptr);
            printSuccessfulMessage();
        } else{
            twoComponents(argv);
            printSuccessfulMessage();
        }
    } else{
        printWrongSyntax();
        return 0;
    }
}