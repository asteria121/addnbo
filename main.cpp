#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <netinet/in.h>

uint32_t GetUint32(const char* fileName)
{
  // Open network byte order from file
  FILE* fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    // File open error
    perror("Failed to open file");
    exit(0);
  }
  
  // Check if file is not 4B
  if (fseek(fp, 0, SEEK_END) != 0)
  {
    perror("Failed to get file size fseek()");
    exit(0);
  }
  
  size_t size = ftell(fp);
  if(size != 4)
  {
    // ftell() success but file is not 4B
    fprintf(stderr, "ERROR: Input file should be 4B\n");
    exit(0);
  }
  else if (size == -1L)
  {
    // If ftell() fails
    perror("Failed to get file size ftell()");
    exit(0);
  }
  
  // Seek to original position
  if (fseek(fp, 0, SEEK_SET) != 0)
  {
    perror("Failed to initialize file position");
    exit(0);
  }
  
  // Read network byte order
  uint8_t buff[4] = { 0x00, 0x00, 0x00, 0x00 };
  fread(buff, sizeof(uint8_t*), 4, fp);
  
  // Convert network byte order to host byte order
  uint32_t* no = reinterpret_cast<uint32_t*>(buff);
  
  // Close file pointer
  fclose(fp);
  
  return ntohl(*no);
}

int main(int argc, char* argv[])
{
  // Check arguments
  if (argc != 3)
  {
    fprintf(stderr, "Usage: addnbo <file1> <file2>\n");
    exit(0);
  }
  
  uint32_t a = GetUint32(argv[1]);
  uint32_t b = GetUint32(argv[2]);
  uint32_t res = a + b;
  
  printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", a, a, b, b, res, res);
  
  return 0;
}
