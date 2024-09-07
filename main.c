#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define sxcjson_capacity (1<<16)

struct {
    char sxcjson_char[sxcjson_capacity];
    struct sxcjson sxcjson_data[sxcjson_capacity];
    struct sxcjson* sxcjson_passive[sxcjson_capacity];
    uint32_t sxcjson_char_size;
    uint32_t sxcjson_passive_size;
} global;

struct sxcjson {
    char* str;
    struct sxcjson* val;
    struct sxcjson* next;
};

struct sxcjson* sxcjson_parse_obj(const char* src, uint32_t* i) {
    struct sxcjson* result = (struct sxcjson*)malloc(sizeof(struct sxcjson));
    uint32_t start = *i;
    if (src[*i] == '{') {
        (*i)++;
        result = sxcjson_parse_obj(src, i);
        (*i)++;
        return result;
    }
    while (src[*i] != '{' && src[*i] != '}' && src[*i] != ':' && src[*i] != ',' && src[*i] != '\0') {
        (*i)++;
    }
    uint32_t str_size = *i - start;
    char* str = (char*)malloc(sizeof(char) * (str_size + 1));
    result->str = str;
    result->next = NULL;
    result->val = NULL;
    memcpy(str, src + start, str_size);
    str[str_size] = '\0';
    if (src[*i] != ':') {
        return result;
    }
    (*i)++;
    result->val = sxcjson_parse_obj(src, i);
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
        result = result->val;
        if (str[i] == '.') {
            i++;
        }
    }
    return result;
}
void sxcjson_free(struct sxcjson* json) {
    if (json->val != NULL) {
        sxcjson_free(json->val);
    }
    if (json->next != NULL) {
        sxcjson_free(json->next);
    }
    free(json->str);
    free(json);
}
int main() {
    const char* src = "{foo:{a:1,b:2,c:3},bar:{f:6,e:5,d:4}}";
    struct sxcjson* json = sxcjson_parse(src);
    struct sxcjson* foo_e = sxcjson_provide(json, "bar.e");
    puts(foo_e->str);  // 5
    sxcjson_free(json);
    return 0;
}