#include <tap.h>
#include "../ha_mycsv.h"

void test_open()
{
  ha_mycsv* mycsv = new ha_mycsv(NULL, NULL);
  int ret = mycsv->open("exapmle.txt", O_RDWR, 0);
  ok(ret == 0, "open");
  delete mycsv;
}

int main()
{
  plan(1);
  test_open();
  return exit_status();
}
