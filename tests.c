#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void trigger_close() {
    int fd = open("test_close.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);
}

void trigger_creat() {
    int fd = creat("test_creat.txt", 0644);
    close(fd);
}

void trigger_open() {
    int fd = open("test_open.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);
}

void trigger_openat() {
    int fd = openat(AT_FDCWD, "test_openat.txt", O_CREAT | O_WRONLY, 0644);
    close(fd);
}

void trigger_rename() {
    rename("test_rename_old.txt", "test_rename_new.txt");
}

void trigger_renameat() {
    renameat(AT_FDCWD, "test_renameat_old.txt", AT_FDCWD, "test_renameat_new.txt");
}

void trigger_brk() {
    void *brk = sbrk(0);
    sbrk(4096);
    sbrk(-4096);
}

void trigger_mmap() {
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    munmap(addr, 4096);
}

void trigger_munmap() {
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    munmap(addr, 4096);
}

void trigger_mprotect() {
    void *addr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    mprotect(addr, 4096, PROT_READ);
    munmap(addr, 4096);
}

void trigger_clone() {
    if (fork() == 0) {
        exit(0);
    } else {
        wait(NULL);
    }
}

void trigger_execve() {
    if (fork() == 0) {
        char *args[] = { "/bin/echo", "Hello, world!", NULL };
        execve("/bin/echo", args, NULL);
    } else {
        wait(NULL);
    }
}

void trigger_exit() {
    if (fork() == 0) {
        _exit(0);
    } else {
        wait(NULL);
    }
}

void trigger_exit_group() {
    if (fork() == 0) {
        _exit(0);
    } else {
        wait(NULL);
    }
}

void trigger_wait4() {
    if (fork() == 0) {
        exit(0);
    } else {
        wait4(-1, NULL, 0, NULL);
    }
}

void trigger_waitid() {
    if (fork() == 0) {
        exit(0);
    } else {
        waitid(P_ALL, 0, NULL, WEXITED);
    }
}

void trigger_read() {
    int fd = open("test_read.txt", O_CREAT | O_RDONLY, 0644);
    char buffer[10];
    read(fd, buffer, sizeof(buffer));
    close(fd);
}

void trigger_write() {
    int fd = open("test_write.txt", O_CREAT | O_WRONLY, 0644);
    write(fd, "Hello", 5);
    close(fd);
}

void trigger_fstat() {
    int fd = open("test_fstat.txt", O_CREAT | O_WRONLY, 0644);
    struct stat st;
    fstat(fd, &st);
    close(fd);
}

void trigger_fstatat() {
    struct stat st;
    fstatat(AT_FDCWD, "test_fstatat.txt", &st, 0);
}

int main() {
    trigger_close();
    trigger_creat();
    trigger_open();
    trigger_openat();
    trigger_rename();
    trigger_renameat();
    trigger_brk();
    trigger_mmap();
    trigger_munmap();
    trigger_mprotect();
    trigger_clone();
    trigger_execve();
    trigger_exit();
    trigger_exit_group();
    trigger_wait4();
    trigger_waitid();
    trigger_read();
    trigger_write();
    trigger_fstat();
    trigger_fstatat();

    printf("All system calls triggered.\n");
    return 0;
}

