#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(){
    Args arg;

    printf("NOMBRE FILE:");
    scanf("%s", arg.nametxt);

    printf("ENCODE/DECODE:");
    scanf("%s", arg.change);

    printf("PALABRA1");
    scanf("%s", arg.word1);

    printf("PALABRA2");
    scanf("%s", arg.word2);

    printf("NOMBRE FILE RETURN:");
    scanf("%s", arg.newnametxt);
}
