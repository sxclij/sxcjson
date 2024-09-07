#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse_obj(const char* src, uint32_t* i) {
    struct sxcjson* result = (struct sxcjson*)malloc(sizeof(struct sxcjson));
    if (src[*i] == ':') {
        (*i)++;
        parse_obj(src, i);
    } else {
        uint32_t start = i;
        while (*i != '{' && *i != '}' && *i != ':' && *i != ',') {
            (*i)++;
        }
        char* str = (char*)malloc(sizeof(char) * (*i - start) + 1);
        result->key = str;
        result->next = NULL;
        result->val = NULL;
        memcpy(str, src + start, *i - start);
        str[*i - start] = '\0';
        return result;
    }
}
struct sxcjson* parse(const char* src) {
    uint32_t i = 0;
    parse_obj(src, &i);
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}