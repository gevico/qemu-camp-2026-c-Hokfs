#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    // TODO: 在这里添加你的代码

      case ET_NONE: type_str = "Unknown"; break;
      case ET_REL:  type_str = "Relocatable file"; break; // .o 文件
      case ET_EXEC: type_str = "Executable file"; break;  // 可执行文件
      case ET_DYN:  type_str = "Shared object file"; break; // 动态库或PIE可执行文件
      case ET_CORE: type_str = "Core file"; break;        // 崩溃转储文件
      default:      type_str = "Unknown type"; break;

    // I AM NOT DONE
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码

    for (int i = 0; i < 2; i++) {
        printf("Parsing %s...\n", filepath[i]);

        // 1. 打开文件 (O_RDONLY 表示只读)
        fd = open(filepath[i], O_RDONLY);
        if (fd < 0) {
            printf("无法打开文件: %s\n", filepath[i]);
            continue;
        }

        // 2. 暴力读取二进制面单
        // 直接把文件开头的 sizeof(Elf64_Ehdr) 个字节，塞进 ehdr 结构体里
        if (read(fd, &ehdr, sizeof(Elf64_Ehdr)) == sizeof(Elf64_Ehdr)) {
            // 3. 读取成功，打印类型
            print_elf_type(ehdr.e_type);
        } else {
            printf("读取 ELF 头部失败\n");
        }

        // 4. 关门大吉
        close(fd);
    }

  // I AM NOT DONE
  
  return 0;
}
