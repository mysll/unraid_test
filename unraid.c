#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/uio.h>
#include <netinet/in.h>

#define RSA void
#define BTRS_FORMAT "regGUID=%s&regTy=%s&regTo=\"%s\"&regTm=%s&regGen=0&regDays=0"

typedef int (*RSA_PUBLIC_DECRYPT_FUNC)(int flen, unsigned char *from, unsigned char *to, RSA *rsa, int padding);
RSA_PUBLIC_DECRYPT_FUNC rsa_public_decrypt;

const char* get_self_exe_name() {
  static char buffer[4096] = "";
  readlink("/proc/self/exe", buffer, 4096);
  char* ptr = &buffer[strlen(buffer)];
  while (*ptr != '/') --ptr;
  return (ptr + 1);
}

int RSA_public_decrypt(int flen, unsigned char *from, unsigned char *to, RSA *rsa, int padding) {
  if (!rsa_public_decrypt) {
    rsa_public_decrypt = (RSA_PUBLIC_DECRYPT_FUNC)dlsym(RTLD_NEXT, "RSA_public_decrypt");
  }
  const char* proc = get_self_exe_name();
  if (!strcmp(proc, "emhttpd") || !strcmp(proc, "shfs")) {
    sprintf(to, BTRS_FORMAT, getenv("UNRAID_GUID"), getenv("UNRAID_VERSION"), getenv("UNRAID_NAME"), getenv("UNRAID_DATE"));
    int len = strlen(to);
    return len;
  } else {
    return rsa_public_decrypt(flen, from, to, rsa, padding);
  }
}
