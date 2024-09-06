#include <stdio.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse() {
    
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}