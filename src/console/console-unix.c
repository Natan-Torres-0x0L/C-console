#include "console.h"

#include <sys/select.h>
#include <sys/ioctl.h>

#include <fcntl.h>

#include <termios.h>
#include <unistd.h>


size_t
console_height(void) {
  struct winsize console_window_size = {0};

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &console_window_size);

  return console_window_size.ws_row;
}

size_t
console_width(void) {
  struct winsize console_window_size = {0};

  ioctl(STDOUT_FILENO, TIOCGWINSZ, &console_window_size);

  return console_window_size.ws_col;
}

void
console_setbuffer(bool buffer) {
  struct termios console_attr = {0};

  if (tcgetattr(STDIN_FILENO, &console_attr) < 0)
    return;

  console_attr.c_lflag = ((buffer) ? console_attr.c_lflag | ICANON : console_attr.c_lflag & (tcflag_t)~ICANON); 

  tcsetattr(STDIN_FILENO, TCSANOW, &console_attr);
}

void
console_setecho(bool echo) {
  struct termios console_attr = {0};

  if (tcgetattr(STDIN_FILENO, &console_attr) < 0)
    return;

  console_attr.c_lflag = ((echo) ? console_attr.c_lflag | ECHO : console_attr.c_lflag & (tcflag_t)~ECHO); 

  tcsetattr(STDIN_FILENO, TCSANOW, &console_attr);
}
