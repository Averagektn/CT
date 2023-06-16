#include <stdio.h>

#define STRING_LEN      100
#define STATEMENT_NUM   3
#define CHAR_TYPE       3

#define  IS_DIGIT(a) ((a) >= '0' && (a) <= '9')
#define IS_LETTER(a) (((a >= 'a') && (a <= 'z')) || ((a >= 'A') && (a <= 'Z')) || (a == '_'))

typedef enum State {
    letter = 0, digit = 1, unknown = 2
} statement;

typedef enum Boolean {
    true = 1, false = 0
} bool;

statement getCharType(char c) {
    statement result = unknown;
    if (IS_DIGIT(c))
        result = digit;
    if (IS_LETTER(c))
        result = letter;
    return result;
}

bool getCorrectIdentificator(char* s) {
    int stateTable[STATEMENT_NUM][CHAR_TYPE] = {
            //    alpha digit error
            {0,0,0},  //zero
            {2,0,0},  //A
            {2,2,0}   //Quit

    };
    statement state;
    int stateNum = 1;

    for (int i = 0; (stateNum) && (s[i]); i++) {
        state = getCharType(s[i]);
        stateNum = stateTable[stateNum][state];
    }

    if (stateNum)
        return true;
    else
        return false;
}


int main() {
    char s[STRING_LEN];

    printf("Enter string:\n");
    gets(s);

    if (getCorrectIdentificator(s))
        printf("Identificator is correct\n");
    else
        printf("Error: Incorrect identificator %s\n", s);

    printf("Correct substrings:\n");
    for (int i = 0; s[i]; i++) {
        if (getCorrectIdentificator(s + i))
            printf("Substring: %s\n", s + i);
    }

    return 0;
}