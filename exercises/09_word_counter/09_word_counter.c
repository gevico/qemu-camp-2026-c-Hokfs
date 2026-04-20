#include <stdio.h>

int main() {
    char str[]="Don't ask what your country can do for you, but ask what you can do for your country.";
    int wordCount = 0;
    // TODO: 在这里添加你的代码

    int found = 0;
    int i=0;
    while (str[i]!='\0') {
        if (str[i]==' ') {
            found = 0;
        }else if (found==0) {
            wordCount++;
            found = 1;
        }
        i++;
    }
    
    printf("单词数量: %d\n", wordCount);
    
    return 0;
}