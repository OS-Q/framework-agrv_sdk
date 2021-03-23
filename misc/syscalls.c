// See LICENSE for license details.

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/signal.h>
#include "encoding.h"

#define SYS_write 64

#undef strcmp

static uintptr_t syscall(uintptr_t which, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
  volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();

  return magic_mem[0];
}

void printstr(const char* s)
{
  syscall(SYS_write, 1, (uintptr_t)s, strlen(s));
}

#ifndef AGRV_ENTRY
#define AGRV_ENTRY main
#endif
int __attribute__((weak)) AGRV_ENTRY(int argc, char** argv)
{
  // single-threaded programs override this function.
  printstr("Implement main()!\n");
  return -1;
}

#ifndef NEED_MINIMAL

extern uint32_t __data_vma;
extern uint32_t __data_lma;
extern uint32_t __data_size;
extern uint32_t __sdata_vma;
extern uint32_t __sdata_lma;
extern uint32_t __sdata_size;
extern uint32_t __sram_text_vma;
extern uint32_t __sram_text_lma;
extern uint32_t __sram_text_size;
extern uint32_t __itim_text_vma;
extern uint32_t __itim_text_lma;
extern uint32_t __itim_text_size;
extern uint32_t __exec_text_vma;
extern uint32_t __exec_text_lma;
extern uint32_t __exec_text_size;
extern uint32_t __bss_vma;
extern uint32_t __bss_size;
extern uint32_t __sbss_vma;
extern uint32_t __sbss_size;

__attribute__((section(".text.init")))
void _init(int offset)
{
  memcpy(&__exec_text_vma, &__exec_text_lma, (int)&__exec_text_size);
  memcpy(&__itim_text_vma, &__itim_text_lma, (int)&__itim_text_size);
  memcpy(&__data_vma,      &__data_lma,      (int)&__data_size);
  memcpy(&__sdata_vma,     &__sdata_lma,     (int)&__sdata_size);
  memcpy(&__sram_text_vma, &__sram_text_lma, (int)&__sram_text_size);

  memset(&__bss_vma,  0, (int)&__bss_size);
  memset(&__sbss_vma, 0, (int)&__sbss_size);

  int ret = AGRV_ENTRY(0, 0);
}
#endif

#undef putchar
__attribute__((weak)) int putchar(int ch)
{
  return 0;
}

void printhex(uint64_t x)
{
  char str[17];
  int i;
  for (i = 0; i < 16; i++)
  {
    str[15-i] = (x & 0xF) + ((x & 0xF) < 10 ? '0' : 'a'-10);
    x >>= 4;
  }
  str[16] = 0;

  printstr(str);
}

size_t printnum(void (*putch)(int, void**, size_t, size_t), void **putdat,
                unsigned long long num, int base, int width, int padc, size_t idx, size_t size)
{
  unsigned digs[sizeof(num)*CHAR_BIT];
  int pos = 0;
  int hex_base = 'a';
  if (base < 0) {
    hex_base = 'A';
    base = -base;
  }

  while (1)
  {
    unsigned long long div = num / base;
    digs[pos++] = num - div * base;
    if (num < base)
      break;
    num = div;
  }

  while (width-- > pos)
    putch(padc, putdat, idx++, size);

  while (pos-- > 0)
    putch(digs[pos] + (digs[pos] >= 10 ? hex_base - 10 : '0'), putdat, idx++, size);

  return idx;
}

static unsigned long long getuint(va_list *ap, int lflag)
{
  if (lflag >= 2)
    return va_arg(*ap, unsigned long long);
  else if (lflag)
    return va_arg(*ap, unsigned long);
  else
    return va_arg(*ap, unsigned int);
}

static long long getint(va_list *ap, int lflag)
{
  if (lflag >= 2)
    return va_arg(*ap, long long);
  else if (lflag)
    return va_arg(*ap, long);
  else
    return va_arg(*ap, int);
}

static float getfloat(va_list *ap)
{
  return va_arg(*ap, double);
}

int vprintfmt(void (*putch)(int, void**, size_t, size_t), void **putdat, const char *fmt, va_list ap, size_t size)
{
  register const char* p;
  const char* last_fmt;
  register char ch;
  unsigned long long num;
  float fval;
  int base, lflag, width, precision, precision2, altflag;
  char padc;
  size_t idx = 0;

  while (1) {
    while ((ch = *fmt) != '%') {
      if (ch == '\0')
        return idx;
      fmt++;
      putch(ch, putdat, idx++, size);
    }
    fmt++;

    // Process a %-escape sequence
    last_fmt = fmt;
    padc = ' ';
    width = -1;
    precision = -1;
    precision2 = -1;
    lflag = 0;
    altflag = 0;
  reswitch:
    switch (ch = *fmt++) {

    // flag to pad on the right
    case '-':
      padc = '-';
      goto reswitch;
      
    // flag to pad with 0's instead of spaces
    case '0':
      padc = '0';
      goto reswitch;

    // width field
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      precision = 0; precision2 = -1;
      for (; ; ++fmt) {
        if (ch == '.') {
          precision2 = 0;
        } else if (precision2 >= 0) {
          precision2 = precision2 * 10 + ch - '0';
        } else {
          precision = precision * 10 + ch - '0';
        }
        ch = *fmt;
          
        if (ch != '.' && (ch < '0' || ch > '9'))
          break;
      }
      goto process_precision;

    case '*':
      precision = va_arg(ap, int);
      goto process_precision;

#if 0 //ZZZZZZZZ
    case '.':
      if (width < 0)
        width = 0;
      goto reswitch;
#endif

    case '#':
      altflag = 1;
      goto reswitch;

    process_precision:
      if (width < 0)
        width = precision, precision = -1;
      goto reswitch;

    // long flag (doubled for long long)
    case 'l':
      lflag++;
      goto reswitch;

    // short flag (h or hh), ignored
    case 'h':
      goto reswitch;

    // character
    case 'c':
      putch(va_arg(ap, int), putdat, idx++, size);
      break;

    // string
    case 's':
      if ((p = va_arg(ap, char *)) == NULL)
        p = "(null)";
      if (width > 0 && padc != '-')
        for (width -= strnlen(p, precision); width > 0; width--)
          putch(padc, putdat, idx++, size);
      for (; (ch = *p) != '\0' && (precision < 0 || --precision >= 0); width--) {
        putch(ch, putdat, idx++, size);
        p++;
        if (lflag && *p == '\0') { // Very simple but incomplete way to handle %ls (wchar)
          p++;
        }
      }
      for (; width > 0; width--)
        putch(' ', putdat, idx++, size);
      break;

    // (signed) decimal
    case 'd':
    case 'i':
      num = getint(&ap, lflag);
      if ((long long) num < 0) {
        putch('-', putdat, idx++, size);
        num = -(long long) num;
      }
      base = 10;
      goto signed_number;

    // unsigned decimal
    case 'u':
      base = 10;
      goto unsigned_number;

    // (unsigned) octal
    case 'o':
      // should do something with padding so it's always 3 octits
      base = 8;
      goto unsigned_number;

    // pointer
    case 'p':
      lflag = 1;
      putch('0', putdat, idx++, size);
      putch('x', putdat, idx++, size);
      /* fall through to 'x' */

    // (unsigned) hexadecimal
    case 'x':
    case 'X':
      base = ch == 'x' ?  16 : -16;
    unsigned_number:
      num = getuint(&ap, lflag);
    signed_number:
      idx = printnum(putch, putdat, num, base, width, padc, idx, size);
      break;

    case 'f':
    floating_number:
      fval = getfloat(&ap);
      if (fval < 0) {
        putch('-', putdat, idx++, size);
        fval = -fval;
      }
      if (precision2 < 0) {
        precision2 = 3;
      }
      if (width >= 0) {
        width -= precision2;
        if (precision2 > 0) {
          --width;
        }
      }
      base = 10;
#ifdef PRINTF_LONG_LONG_FLOAT_SUPPORT
      // Under riscv32imafc this needs about 6K-byte code of soft float library
      num = (int long long)(fval);
      fval -= num;
#else
      // Without PRINTF_LONG_LONG_FLOAT_SUPPORT floating point numbers greater than INT_MAX will be printed as INT_MAX.
      num = (int)(fval);
      fval -= (unsigned)num;
#endif
      idx = printnum(putch, putdat, num, base, width, padc, idx, size);
      if (precision2 > 0) {
        num = 0;
        width = precision2;
        padc = '0';
        putch('.', putdat, idx++, size);
        while (precision2-- > 0) {
          fval *= 10.;
        }
        num = (int)(fval+1e-6);
        idx = printnum(putch, putdat, num, base, width, padc, idx, size);
      }
      break;

    // escaped '%' character
    case '%':
      putch(ch, putdat, idx++, size);
      break;
      
    // unrecognized escape sequence - just print it literally
    default:
      putch('%', putdat, idx++, size);
      fmt = last_fmt;
      break;
    }
  }
  return idx;
}

int printf(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  int ret = vprintfmt((void*)putchar, 0, fmt, ap, 0);

  va_end(ap);
  return ret;
}

int puts(const char *s)
{
  return printf("%s\n", s);
}

static void sprintf_putch(int ch, void** data, size_t idx, size_t size)
{
  char** pstr = (char**)data;
  **pstr = ch;
  (*pstr)++;
}

int sprintf(char* str, const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  int ret = vprintfmt(sprintf_putch, (void**)&str, fmt, ap, 0);
  *str = 0;

  va_end(ap);
  return ret;
}

static void snprintf_putch(int ch, void** data, size_t idx, size_t size)
{
  if (idx < size) {
    char** pstr = (char**)data;
    **pstr = ch;
    (*pstr)++;
  }
}

int snprintf(char* str, size_t size, const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);

  int ret = vprintfmt(snprintf_putch, (void**)&str, fmt, ap, size - 1);
  *str = 0;

  va_end(ap);
  return ret;
}

__attribute__((section(".text.init")))
void* memcpy(void* dest, const void* src, size_t len)
{
  if ((((uintptr_t)dest | (uintptr_t)src | len) & (sizeof(uintptr_t)-1)) == 0) {
    const uintptr_t* s = src;
    uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = *s++;
  } else {
    const char* s = src;
    char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = *s++;
  }
  return dest;
}

__attribute__((section(".text.init")))
void* memset(void* dest, int byte, size_t len)
{
  if ((((uintptr_t)dest | len) & (sizeof(uintptr_t)-1)) == 0) {
    uintptr_t word = byte & 0xFF;
    word |= word << 8;
    word |= word << 16;
    word |= word << 16 << 16;

    volatile uintptr_t *d = dest;
    while (d < (uintptr_t*)(dest + len))
      *d++ = word;
  } else {
    volatile char *d = dest;
    while (d < (char*)(dest + len))
      *d++ = byte;
  }
  return dest;
}

size_t strlen(const char *s)
{
  const char *p = s;
  while (*p)
    p++;
  return p - s;
}

size_t strnlen(const char *s, size_t n)
{
  const char *p = s;
  while (n-- && *p)
    p++;
  return p - s;
}

int strcmp(const char* s1, const char* s2)
{
  unsigned char c1, c2;

  do {
    c1 = *s1++;
    c2 = *s2++;
  } while (c1 != 0 && c1 == c2);

  return c1 - c2;
}

char* strcpy(char* dest, const char* src)
{
  char* d = dest;
  while ((*d++ = *src++))
    ;
  return dest;
}

long atol(const char* str)
{
  long res = 0;
  int sign = 0;

  while (*str == ' ')
    str++;

  if (*str == '-' || *str == '+') {
    sign = *str == '-';
    str++;
  }

  while (*str) {
    res *= 10;
    res += *str++ - '0';
  }

  return sign ? -res : res;
}


// Dummy implementation of system call functions.
int _close (int file)
{
  return 0;
}

#include <sys/stat.h>
int _fstat(int file, struct stat *st)
{
  return 0;
}

int _isatty(int file)
{
  return 0;
}

int _lseek (int file, int offset, int whence)
{
  return 0;
}

int _open(const char *pathname, int flags)
{
  return 0;
}

int _kill(int pid, int sig)
{
  return 0;
}

int _getpid(void)
{
  return 0;
}
