#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse_obj(const char* src, uint32_t* i) {
    if (src[*i] == ':') {
        (*i)++;
        parse_obj(src, i);
    } else {
        uint32_t start = i;
        while (*i != '{' && *i != '}' && *i != ':' && *i != ',') {
            (*i)++;
        }
        char* str = (char*)malloc(sizeof(char) * (*i - start));
        memcpy(str, src + start, *i - start);
    }
}
struct sxcjson* parse(const char* src) {
    uint32_t i = 0;
    parse_obj(src, &i);
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}