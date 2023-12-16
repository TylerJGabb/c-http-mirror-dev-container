#include <stdio.h>
#include <stdlib.h>

#include "server.h"

int main(int argc, char *argv[]) {
  int port = 8080;
  if (argc < 2) {
    printf("No port specified, using default port %d\n", port);
  } else {
    port = atoi(argv[1]);
    if (port < 1 || port > 65535) {
      printf("Invalid port specified %s, using default port %d\n", argv[1],
             port);
    } else {
      printf("Using port %d\n", port);
    }
  }
  return listen_and_serve_http(port);
}
