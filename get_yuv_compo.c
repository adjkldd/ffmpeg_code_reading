/*
 * gcc get_yuv_compo.c -o get_yuv_compo
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc == 4) {

    char* yuv_file = argv[1];
    int width = 0, height = 0;
    if (! strcmp(argv[2], "-s")) {
       char* dimension = argv[3];
       char* p = strchr(dimension, 'x');
       if (p) {
         height = atoi(p+1);
         *p = '\0';
         width = atoi(dimension);
       }
    }

    if (width == 0 || height == 0) {
       exit(0);
    }

    fprintf(stdout, "width: %d, height: %d\n", width, height);
    
    int luma_size = width * height;
    char* buf = (char *)malloc(luma_size);

    FILE* fp = fopen(yuv_file, "rb");
    int n = fread(buf, 1, luma_size, fp);
    if (n != luma_size) {
      fprintf(stderr, "not a corrent yuv file\n");
      exit(0);
    }

    char* p = strchr(yuv_file, '.');
    char yuv_file_we[128] = {0};
    char tmp_filename[128] = {0};
    if (p) {
      *p = '\0';
      strcpy(yuv_file_we, yuv_file); 
    }
    strcat(tmp_filename, yuv_file_we);
    strcat(tmp_filename + strlen(yuv_file_we), ".Y");
    FILE* out = fopen(tmp_filename, "wb+");
    if (out) {
      fwrite(buf, luma_size, 1, out);
      fclose(out);
    }

    n = fread(buf, 1, luma_size/4, fp);
    if (n != luma_size/4) {
      fprintf(stderr, "not a corrent yuv file\n");
      exit(0);
    }
    memset(tmp_filename, '\0', 128);
    strcat(tmp_filename, yuv_file_we);
    strcat(tmp_filename + strlen(yuv_file_we), ".U");
    out = fopen(tmp_filename, "wb+");
    if (out) {
      fwrite(buf, luma_size/4, 1, out);
      fclose(out);
    }
    

    n = fread(buf, 1, luma_size/4, fp);
    if (n != luma_size/4) {
      fprintf(stderr, "not a corrent yuv file\n");
      exit(0);
    }
    memset(tmp_filename, '\0', 128);
    strcat(tmp_filename, yuv_file_we);
    strcat(tmp_filename + strlen(yuv_file_we), ".V");
    out = fopen(tmp_filename, "wb+");
    if (out) {
      fwrite(buf, luma_size/4, 1, out);
      fclose(out);
    }
  } else {
    fprintf(stderr, "usage: %s input_file -s WxH\n", argv[0]);
  }
  return 0;
}
