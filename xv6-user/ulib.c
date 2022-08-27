#include "kernel/include/types.h"
#include "kernel/include/stat.h"
#include "kernel/include/fcntl.h"
#include "xv6-user/user.h"

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

char*
strcat(char *s, const char *t)
{
  char *os = s;
  while(*s)
    s++;
  while((*s++ = *t++))
    ;
  return os;
}


int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  char *cdst = (char *) dst;
  int i;
  for(i = 0; i < n; i++){
    cdst[i] = c;
  }
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;
  int neg = 1;
  if (*s == '-') {
    s++;
    neg = -1;
  }
  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n * neg;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  if (src > dst) {
    while(n-- > 0)
      *dst++ = *src++;
  } else {
    dst += n;
    src += n;
    while(n-- > 0)
      *--dst = *--src;
  }
  return vdst;
}

int
memcmp(const void *s1, const void *s2, uint n)
{
  const char *p1 = s1, *p2 = s2;
  while (n-- > 0) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

void *
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

char*
strncpy(char *s, const char *t, int n)
{
  char *os;

  os = s;
  while(n-- > 0 && (*s++ = *t++) != 0)
    ;
  while(n-- > 0)
    *s++ = 0;
  return os;
}

int
strncmp(const char *p, const char *q, uint n)
{
  while(n > 0 && *p && *p == *q)
    n--, p++, q++;
  if(n == 0)
    return 0;
  return (uchar)*p - (uchar)*q;
}

void itoa(uint n, char* s)
{
  int i, sign;       
  if ((sign = n) < 0)  /* record sign */
    n = -n;          /* make n positive */
  i = 0;
  do {       /* generate digits in reverse order */
    s[i++] = n % 10 + '0';   /* get next digit */
  } while ((n /= 10) > 0);     /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  int  j;
  char c;             
  for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}