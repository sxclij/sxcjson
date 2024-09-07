#include <stdio.h>
#include <stdint.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse_obj(const char* src, uint32_t* i) {

}
struct sxcjson* parse(const char* src) {
    uint32_t i = 0;
    parse_obj(src, i);
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}