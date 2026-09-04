#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_LINE_SIZE = 512;
const int MAX_NUM_OF_LYRICS = 100;

typedef struct {
    char* content;
    float duration;
} Lyric;

int main()
{

    Lyric* lyrics = malloc(MAX_NUM_OF_LYRICS * sizeof(Lyric));
    int lyricsCount = 0;

    char line[MAX_LINE_SIZE];
    
    FILE* file = fopen("file.txt", "r");
    if (file == NULL){
        return 69;
    }

    int lineCount = 1;

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

        // printf("%s\n", content);
        // printf("%s\n", duration);

        // trim content from extra spaces


        while (content[strlen(content) - 1] == ' ' &&  strlen(content) != 0){
            content[strlen(content) - 1] = '\0';
        }

        if (strlen(content) == 0) {
            printf("content field is empty at line %d\n", lineCount);
            return 69;
        }
        if (strlen(duration) == 0) {
            printf("duration field is empty at line %d\n", lineCount);
            return 69;
        }


        
        char* endptr;
        const float durationVal = strtof(duration, &endptr);

        if (strlen(endptr) != 0){
            printf("Failed to cast duration to float\n");
            return 69;
        }
        
        if (lyricsCount >= MAX_NUM_OF_LYRICS) {
            printf("Max number of lyrics surpassed\n");
            return 69;
        }

        Lyric lyric = {
            strdup(content),
            durationVal
        };
        lyrics[lyricsCount] = lyric;
        lyricsCount++;

        lineCount++;

    }
    
    // print lyrics
    for (int i = 0; i < lyricsCount; ++i) {
        const Lyric lyric = lyrics[i]; 
        printf("%s %f\n", lyric.content, lyric.duration);
    }


    // free memory
    for (int i = 0; i < lyricsCount; ++i) {
        free(lyrics[i].content); 
        
    }
    free(lyrics);

    return 0;

}