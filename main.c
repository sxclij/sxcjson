#include <stdio.h>
#include <stdint.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse(const char* src,uint32_t* i) {
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}