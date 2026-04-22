#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    // TODO: 在这里添加你的代码
    const char*query_start = strchr(url, '?');
    if (query_start == NULL) {
        goto exit;
    }
    query_start = query_start + 1;

    char *query_copy = (char *)malloc(strlen(query_start) + 1);
    if (query_copy == NULL) {
        err = -1;
        goto exit;
    }
    strcpy(query_copy, query_start);

    char *pair= strtok(query_copy, "&");

    while (pair != NULL) {
        char *equal = strchr(pair, '=');
        if (equal != NULL) {
            *equal = '\0';

            char *key = pair;
            char *value = equal + 1;
            printf("%s=%s\n", key,value);
        }else {
            printf("%s\n", pair);
        }
        pair = strtok(NULL, "&");
    }
    free(query_copy);


    
exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}