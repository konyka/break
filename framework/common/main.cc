#include <stdio.h>
#include "application_interface.h"

using namespace bk;

extern bk::ApplicationInterface* g_pApp;

int main(int argc, char* argv[]) {
  int rc;

  if (0x00 != (rc = g_pApp->Init())) {
    printf("app initialize failed!");
    return rc;
  }

  while (!g_pApp->IsQuit()) {
    g_pApp->Tick();
  }

  g_pApp->DeInit();

  return 0;
}

