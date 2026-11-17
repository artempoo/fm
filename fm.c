#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct {
  char *path;
  char *name;
  int len;
} PathType;

typedef struct {
  PathType buf_col1[256];
  PathType buf_col2[256];
  PathType buf_col3[256];
  int size_buf1;
  int size_buf2;
  int size_buf3;
} DataBuffers;

// Проблема в том, что эта функция печатает по одному символу а не целым словом
void draw_column(int width_col, int term_char_index, int full_width, DataBuffers buf) {
  // здесь необходимо разделить экран на три колонки, чтобы удобно заполнять новые строки в будущем
  int index_cur = term_char_index % full_width;
  int row = term_char_index / full_width;
  if (index_cur < width_col) {
    // здесь печатаем первый массив

    // нужно проверить не выходим ли за пределы буффера строк
    if (row < buf.size_buf1) {
      int len = buf.buf_col1[row].len;

      // printf("\n\n index_cur: %d, buf.size_buf1: %d \n\n ", index_cur, buf.size_buf1);
      // printf("\n\n len name: %d, index name: %d \n\n ", len, idx);
      // printf("char: %c\n\n", buf.buf_col1[index_cur].name[0]);

      if (index_cur < len) {
        // printf("char: %c\n\n", buf.buf_col1[index_cur].name[idx]);

        printf("%c", buf.buf_col1[row].name[index_cur]);
      } else {
        printf("_");
      }
    } else {
      // Если вышли за пределы, нужно печатать пустые строки
      printf(" ");
    }
    // Проблема в том, что я перемещаюсь по буфферу из индекса ширины терминала а это не правильно!
    // нужно получить индекс строки

    // printf("1");
  } else if (index_cur >= width_col && index_cur <= (width_col * 2)) {
    // второй массив
    printf("2");

  } else if (index_cur >= (width_col * 2) && index_cur <= full_width) {
    // третий массив
    printf("3");
  }
}

int main(void) {
  struct dirent *dirp;
  const char *path = "./";

  struct winsize ws;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
  int term_width = ws.ws_col;
  int term_height = ws.ws_row;

  int width_col = term_width / 3;

  printf("%d\n\n", width_col);

  // printf("%d - %d\n\n", term_width, term_height);

  DataBuffers framebuffer;

  DIR *dp = opendir(path);

  /* ### Заполняем текущую директорию ### */
  int count = 0;
  while ((dirp = readdir(dp)) != NULL) {
    int len = strlen(dirp->d_name);
    framebuffer.buf_col1[count].name = strdup(dirp->d_name);
    framebuffer.buf_col1[count].len = len;
    framebuffer.size_buf1 = count;

    framebuffer.buf_col2[count].name = strdup(dirp->d_name);
    framebuffer.buf_col2[count].len = len;
    framebuffer.size_buf2 = count;

    framebuffer.buf_col3[count].name = strdup(dirp->d_name);
    framebuffer.buf_col3[count].len = len;
    framebuffer.size_buf3 = count;
    count++;
  }

  int index = 0;
  while (index < term_width * term_height) {
    draw_column(width_col, index, term_width, framebuffer);
    index++;
  }

  // for (int i = 0; i < framebuffer.size_buf1; i++) {
  //   printf("%s \n", framebuffer.buf_col1[i].name);
  // }

  closedir(dp);
  // TODO: Освободить памяти буфферов

  return 0;
}
