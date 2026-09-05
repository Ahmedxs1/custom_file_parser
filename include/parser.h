#ifndef PARSER_H
#define PARSER_H



typedef struct {
    char* content;
    float duration;
} Lyric;

typedef struct {
    char* fileName;
    Lyric* lyrics;
    int lyricsCount;
    int lineCount;
} Parser;

bool InitParser(Parser* p, char* fileName);
Lyric* getLyrics(Parser* p);
void freeParser(Parser* p);

#endif