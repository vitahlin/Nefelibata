/**
 * 解决进程的竞争条件，父进程先运行
 */

#include "./../lib/apue.h"

static void output(char* str) {
    char* ptr;
    int c;

    // 取消输出缓存
    setbuf(stdout, NULL);

    for (ptr = str; (c = *ptr++) != 0;) {
        putc(c, stdout);
    }
}

int main(int argc, const char** agrv) {
    pid_t pid;

    TELL_WAIT();

    char child_str[] = "output from child\n";
    char parent_str[] = "output from parent\n";

    if ((pid = fork()) < 0) {
        LogErrQuit("fork error");
    } else if (pid == 0) {
        TELL_PARENT(getppid());
        output(child_str);
    } else {
        WAIT_CHILD();
        output(parent_str);
    }

    return 0;
}
