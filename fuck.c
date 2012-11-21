#include "fuck.h"
#include <execinfo.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void fuck(int sig, char const *filename) {
    void *buffer[1024];
    int count;
    int fds[2];
    size_t i;
    char const *signame = strsignal(sig);
    char const *post_stack_trace =
    "Send this to the author of this program.\n";

    count = backtrace(buffer, 1024);

    fds[0] = 1; /* stdout */
    fds[1] = open(filename, O_RDWR | O_CREAT, S_IRWXG);
    if (!fds[1]) return; /* well, fuck */
    for (i = 0; i < 2; ++i) {
        write(fds[i], signame, strlen(signame));
        write(fds[i], "\n", 1);
        backtrace_symbols_fd(buffer, count, fds[i]);
        write(fds[i], post_stack_trace, strlen(post_stack_trace));
    }
    close(fds[1]);
}
