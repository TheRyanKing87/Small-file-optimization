#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void
test_failed()
{
	printf(1, "TEST FAILED\n");
	exit();
}

void
test_passed()
{
 printf(1, "TEST PASSED\n");
 exit();
}

#define NBLOCKS (NDIRECT+1)
#define SIZE NBLOCKS*4

int
main(int argc, char *argv[])
{
  int fd, i;
  char buf[SIZE];
  char buf2[SIZE];
  char tmp;
  struct stat st;
  
  for(i = 0; i < SIZE; i++){
    buf[i] = (char)(i+(int)'0');
  }

  //int x = 0;
  memset(buf2, 0, SIZE);
  printf(1, "size: %d\n", SIZE);
  printf(1, "buf: %s\n", buf);
  //open, write 1 byte to the end, close
  for(i = 0; i < SIZE+5; i++){
    if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
      printf(1, "Failed to create the small file\n");
      test_failed();
    }
    //printf(1, "buf: %s\n", buf);
    //printf(1, "&tmp: %p\n", &tmp);
    //printf(1, "tmp: %s\n", tmp);
    //x = read(fd, &tmp, 1);

    while(read(fd, &tmp, 1) == 1) { } //go to end of file
    printf(1, "&buf[i]: %s\n", &buf[i]);
    if(write(fd, &buf[i], 1) != 1){
      printf(1, "www\n");
      break;
    }
    printf(1, "XXX i %d\n", i);
    close(fd);
  }
  //printf(1, "buf: %s\n", buf);
  //read
  if((fd = open("test_file.txt", O_CREATE | O_SMALLFILE | O_RDWR)) < 0){
    printf(1, "Failed to open the small file\n");
    test_failed();
  }
  
  if(fstat(fd, &st) < 0){
    printf(1, "Failed to get stat on the small file\n");
    test_failed();
  }
  
  if(st.size != SIZE){
    printf(1, "Invalid file size.\n");
    test_failed();
  }
  
  if(read(fd, buf2, SIZE) != SIZE){
    printf(1, "Read failed!\n");
    test_failed();
  }
  close(fd);

  for(i = 0; i < SIZE; i++){
    if(buf[i] != buf2[i]){
      printf(1, "buf1 %c =? buf2 %c (i = %d)\n", buf[i], buf2[i], i);
      printf(1, "Data mismatch.\n");
      test_failed();
    }
  }
  
  test_passed();
	exit();
}
