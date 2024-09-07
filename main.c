#include <stdint.h>
#include <stdio.h>

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
        while (*i != '{' && *i != '}' && *i != ':' &&*i != ',') {
            (*i)++;
        }
    }
}
struct sxcjson* parse(const char* src) {
    uint32_t i = 0;
    parse_obj(src, &i);
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}