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



int main() {
    struct json* json = parse("{\"foo_root\":{\"foo_child\":1}}");
    printf("test");
}