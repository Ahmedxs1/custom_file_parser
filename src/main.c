#include <stdlib.h>
#include <stdio.h>

#include "parser.h"


int main()
{
    printf("Hello, World\n");

    Parser* p = malloc(sizeof(Parser));
    if (p == NULL) return 1;

    if (!InitParser(p, "file.txt")) {
        return 69;
    }
    Lyric* lyrics = getLyrics(p);

    // print lyrics
    for (int i = 0; i < p->lyricsCount; ++i) {
        const Lyric lyric = lyrics[i]; 
        printf("%s %f\n", lyric.content, lyric.duration);
    }

    freeParser(p);
    

    return 0;
}