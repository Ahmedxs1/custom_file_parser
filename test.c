#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
    char content[19] = "   ";

    while (content[strlen(content) - 1] == ' ' &&  strlen(content) != 0){
        content[strlen(content) - 1] = '\0';
    }

    printf("%d \n", strlen(content));

    return 0;
}