#include <stdio.h>
#include "Email.h"


void
printMail (EMAIL msg)
{
  printf ("ID:\n  %i\n", getEmailId(msg));
  printf ("FROM:\n  %i\n", getEmailFrom(msg));
  printf ("TO:\n  %i\n", getEmailTo(msg));
  printf ("IS_READABLE\n  %i\n", isReadable(msg));
}

int
isReadable (EMAIL msg)
{
  return 1;
}

EMAIL cloneEmail(EMAIL msg) {
    return msg;
}

EMAIL createEmail (int from, int to) {
  EMAIL msg = 1;
  setEmailFrom(msg, from);
  setEmailTo(msg, to);
  return msg;
}
