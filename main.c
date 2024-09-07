#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct sxcjson {
    char* key;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* parse_obj(const char* src, uint32_t* i) {
    struct sxcjson* result = (struct sxcjson*)malloc(sizeof(struct sxcjson));
    uint32_t start = i;
    if (src[*i] == '{') {
        return result;
    }
    if (src[*i] == '}') {
        return result;
    }
    if (src[*i] == ',') {
        return result;
    }
    while (*i != '{' && *i != '}' && *i != ':' && *i != ',') {
        (*i)++;
    }
    uint32_t str_size = *i - start;
    char* str = (char*)malloc(sizeof(char) * (str_size + 1));
    result->key = str;
    result->next = NULL;
    result->val = NULL;
    memcpy(str, src + start, str_size);
    str[str_size] = '\0';
    if (src[*i] != ':') {
        return result;
    }
    (*i)++;
    result->val = parse_obj(src, i);
    return result;
}
struct sxcjson* parse(const char* src) {
    uint32_t i = 0;
    parse_obj(src, &i);
}

int main() {
    struct sxcjson* json = parse("foo:abc");
}