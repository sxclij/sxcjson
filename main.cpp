#include <bits/stdc++.h>

struct json {
    enum {
        json_kind_null,
        json_kind_str,
        json_kind_obj
    };
    std::string data;
    struct json* obj;
    struct json* next;
};

struct json* parse_obj(std::string* src, uint32_t* i) {
    struct json* kari = (struct json*)malloc(sizeof(struct json));
    if ((*src)[*i] == '{') {
    }
    if ((*src)[*i] == '}') {
    }
    if ((*src)[*i] == ',') {
        kari->next = parse_obj(src, i);
        ;
    }
    if ((*src)[*i] == ':') {
    }
}
struct json* parse(std::string src) {
    uint32_t i = 0;
    return parse_obj(&src, &i);
}

int main() {
    struct json* json = parse("{\"foo_root\":{\"foo_child\":1}}");
    printf("test");
}