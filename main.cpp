#include <bits/stdc++.h>

struct json {
    std::string key;
    enum {
        json_kind_num,
        json_kind_str,
        json_kind_vec,
        json_kind_json,
    } value_kind;
    union {
        int64_t* num;
        std::string* str;
        std::vector<struct json*> vec;
        struct json* json;
    }value;
};

struct json* parse(std::string src) {
    struct json* root = (struct json*)malloc(sizeof(struct json));
}

int main() {
    struct json* json = parse("{\"foo_root\":{\"foo_child\":1}}");
}