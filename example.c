#include "fuck.h"
#include <stdlib.h>
#include <signal.h>

void handle_error(int sig) {
    fuck(sig, "crash.log");
    exit(1);
}

void foo() {
    char *bar = NULL;
    *bar = 42; /* whoops! */
}

int main() {
    signal(SIGSEGV, &handle_error);
    signal(SIGILL, &handle_error);
    foo();
}
