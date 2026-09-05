#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


bool InitParser(Parser* p, char* fileName)
{
    // return false if memory allocation failed or file error input check output for input error

    p->lyricsCount = 0;
    p->lineCount = 1;
    p->fileName = fileName;

    // load lyrics from file

    const int MAX_LINE_SIZE = 512;
    const int MAX_NUM_OF_LYRICS = 100;
    char line[MAX_LINE_SIZE]; 

    p->lyrics = malloc(MAX_NUM_OF_LYRICS * sizeof(Lyric));
    if (p->lyrics == NULL) {
        return false;
    }
    p->lyricsCount = 0;

    FILE* file = fopen(p->fileName, "r");
    if (file == NULL){
        return false;
    }


    while (fgets(line, MAX_LINE_SIZE, file)) {
        line[strcspn(line, "\n")] = '\0';        
        
        char content[512] = "";
        char duration[10] = "";
        int open = 0;
        
        
        const int len = strlen(line); 
        for (int i = 0; i < len; ++i) {

            if (line[i] == '[') {
                open = 1;
                continue;
            }
            
            if (line[i] == ']') open = 2;
            if (open == 2) break;

            if (open == 1){
                // strcat(duration, (char*)line[i]);
                duration[strlen(duration) + 1] = '\0';
                duration[strlen(duration)] = line[i];
            }else{
                content[strlen(content) + 1] = '\0';
                content[strlen(content)] = line[i];
            }
            
        }

        // trim content from extra spaces

        const char* RED = "\033[31m";
        const char* RESET = "\033[0m";

        while (strlen(content) != 0 && content[strlen(content) - 1] == ' '){
            content[strlen(content) - 1] = '\0';
        }

        if (strlen(content) == 0) {
            printf("%s content field is empty at line %d %s\n", RED, p->lineCount, RESET);
            fclose(file);
            return false;
        }
        if (strlen(duration) == 0) {
            printf("%s duration field is empty at line %d %s\n", RED, p->lineCount, RESET);
            fclose(file);
            return false;
        }


        
        char* endptr;
        const float durationVal = strtof(duration, &endptr);

        if (strlen(endptr) != 0){
            printf("Failed to cast duration to float\n");
            fclose(file);
            return false;
        }
        
        if (p->lyricsCount >= MAX_NUM_OF_LYRICS) {
            printf("Max number of lyrics surpassed\n");
            fclose(file);
            return false;
        }

        Lyric lyric = {
            strdup(content),
            durationVal
        };
        p->lyrics[p->lyricsCount] = lyric;
        p->lyricsCount++;

        p->lineCount++;

    }
    
    fclose(file);

    return true;

}
Lyric* getLyrics(Parser* p)
{
    return p->lyrics;
}
void freeParser(Parser* p) 
{
    // must call to free memory
    
    for (int i = 0; i < p->lyricsCount; ++i) {
        free(p->lyrics[i].content); 
        
    }
    free(p->lyrics);
    free(p);

    return;
}
