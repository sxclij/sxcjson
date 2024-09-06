#include <stdio.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

int main() {
    printf("good morning world");
}