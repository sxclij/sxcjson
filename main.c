#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sxcjson_capacity (1 << 16)

struct sxcjson {
    char* str;
    struct sxcjson* child;
    struct sxcjson* next;
};
struct {
    char sxcjson_char[sxcjson_capacity];
    struct sxcjson sxcjson_data[sxcjson_capacity];
    uint32_t sxcjson_char_size;
    uint32_t sxcjson_data_size;
} global;

struct sxcjson* sxcjson_parse_obj(const char* src, uint32_t* i) {
    struct sxcjson* result = &global.sxcjson_data[global.sxcjson_data_size++];
    if (src[*i] == '{') {
        (*i)++;
        result = sxcjson_parse_obj(src, i);
        (*i)++;
        return result;
    }
    if (src[*i] == '\"') {
        (*i)++;
    }
    uint32_t start = *i;
    while (src[*i] != '{' && src[*i] != '}' && src[*i] != ':' && src[*i] != ',' && src[*i] != '\"' && src[*i] != '\0') {
        (*i)++;
    }
    uint32_t str_size = *i - start;
    char* str = &global.sxcjson_char[global.sxcjson_char_size];
    global.sxcjson_char_size += str_size + 1;
    result->str = str;
    result->next = NULL;
    result->child = NULL;
    memcpy(str, src + start, str_size);
    str[str_size] = '\0';
    if (src[*i] == '\"') {
        (*i)++;
    }
    if (src[*i] != ':') {
        return result;
    }
    (*i)++;
    result->child = sxcjson_parse_obj(src, i);
    if (src[*i] == ',') {
        (*i)++;
        result->next = sxcjson_parse_obj(src, i);
    }
    return result;
}
struct sxcjson* sxcjson_parse(const char* src) {
    uint32_t i = 0;
    return sxcjson_parse_obj(src, &i);
}
struct sxcjson* sxcjson_provide(struct sxcjson* json, const char* str) {
    uint32_t i = 0;
    struct sxcjson* result = json;
    while (str[i] != '\0') {
        uint32_t start = i;
        while (str[i] != '.' && str[i] != '\0') {
            i++;
        }
        while (memcmp(result->str, str + start, i - start) != 0) {
            result = result->next;
            if (result == NULL) {
                return NULL;
            }
        }
        result = result->child;
        if (str[i] == '.') {
            i++;
        }
    }
    return result;
}
void sxcjson_init() {
    global.sxcjson_char_size = 0;
    global.sxcjson_data_size = 0;
}
int main() {
    sxcjson_init();
    const char* src = "{\"foo\":{\"a\":1,\"b\":2,\"c\":3},\"bar\":{\"f\":6,\"e\":5,\"d\":4}}";
    struct sxcjson* json = sxcjson_parse(src);
    struct sxcjson* foo_e = sxcjson_provide(json, "bar.e");
    puts(foo_e->str);  // 5
    return 0;
}