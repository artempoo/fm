↓
↑

"\x1b[2J\x1b[H" - очищает экран
"\x1b[?1049h" - альтернативный экран

#include <sys/ioctl.h>
#include <unistd.h>

struct winsize ws;

ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

Файловая система: opendir(), readdir(), stat() / lstat(), rename(), mkdir(), unlink() и другие системные интерфейсы.
fork() + exec()

#define BLACK "\x1b[30m"
#define WHITE "\x1b[37m"
#define RESET "\x1b[0m"

#define BG_BLACK "\x1b[40m"
#define BG_WHITE "\x1b[47m"

gh repo create fuck --public --source=. --remote=origin --push

// При запуске
printf("\x1b[?1049h\x1b[H");

// При выходе
printf("\x1b[?1049l");
fflush(stdout);
