#include <stdio.h>
#include <string.h>

#define LEN 100
#define SIZE 255

typedef enum BOOL {
    true = 1, false = 0
} bool;

int next=0;
char tokens[LEN][SIZE];

bool checkToken(char *tokenType) {
    return strcmp(tokenType, tokens[next++]) == 0 ? true : false;
}

bool checkH() {
    int save = next;
    if (checkToken("#\n"))
        return true;
    next = save;

    if (checkToken("marked\n"))
        return true;
    next = save;

    if (checkToken("num.\n"))
        return true;
    next = save;

    if (checkToken("line\n"))
        return true;
    next = save;

    if (checkToken(">\n"))
        return true;
    next = save;

    if (checkToken("code\n"))
        return true;
    next = save;

    if (checkToken("link\n") && checkToken(")\n"))
        return true;
    next = save;

    return false;
}

bool checkSt() {
    int save = next;

    if ((checkH()))
        return true;
    next = save;

    return false;
}

bool checkDelE() {
    int save = next;

    if (checkSt() && checkDelE())
        return true;
    next = save;

    return true;
}

bool checkE() {
    int save = next;

    if (checkDelE())
        return true;
    next = save;

    return false;
}

bool analyze(int index) {
    checkE();
    return next == index ? true : false;
}

int main() {
    FILE *f;

    f = fopen("output.txt", "r");
    int ind = 0;
    while ((fgets(tokens[ind++], LEN, f) != NULL));
    fclose(f);

    for (int i = 0; i < ind - 1; i++) {
        printf("%d: %s", i, tokens[i]);
    }

    if (analyze(ind - 1))
        printf("Grammar is correct\n");
    else
        printf("Grammar is incorrect, error token(id): %s(%d)\n", tokens[next], next);
}