#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    // TODO: 在这里添加你的代码



        // 1. 找到三个斜杠的位置
        const char *first_slash = cmd + 1; // cmd[1] 就是第一个 '/'
        const char *second_slash = strchr(first_slash + 1, '/');
        if (second_slash == NULL) return -1; // 格式错误

        const char *third_slash = strchr(second_slash + 1, '/');
        if (third_slash == NULL) return -1; // 格式错误

        // 2. 利用指针相减，计算要截取的长度
        size_t old_len = second_slash - first_slash - 1;
        size_t new_len = third_slash - second_slash - 1;

        // 3. 动态分配内存并拷贝 (千万别忘了 +1 给 '\0' 留位置)
        *old_str = (char*)malloc(old_len + 1);
        strncpy(*old_str, first_slash + 1, old_len);
        (*old_str)[old_len] = '\0'; // strncpy 不一定会加 \0，必须手动封口

        *new_str = (char*)malloc(new_len + 1);
        strncpy(*new_str, second_slash + 1, new_len);
        (*new_str)[new_len] = '\0';



    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    // TODO: 在这里添加你的代码


        // 1. 用 strstr 找到 old 第一次出现的位置
        char *pos = strstr(str, old);
        if (pos == NULL) {
            return; // 没找到，直接结束，什么都不改
        }

        size_t old_len = strlen(old);
        size_t new_len = strlen(new);

        // 计算尾巴的长度（也就是我们要挪动的家具的大小，记得 +1 包含 \0）
        size_t tail_len = strlen(pos + old_len) + 1;

        // 2. 挪动尾巴！
        // ⚠️ 极其致命的考点：必须用 memmove，绝对不能用 strcpy 或 memcpy！
        // 因为这块内存在同一个数组里，位置是重叠的。memmove 专门处理重叠拷贝。
        memmove(pos + new_len, pos + old_len, tail_len);

        // 3. 腾出空间后，把 new 拷贝进去
        // 这里只拷贝字母即可，不需要拷贝 new 的 \0，因为尾巴已经自带 \0 了
        memcpy(pos, new, new_len);

    
    
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
