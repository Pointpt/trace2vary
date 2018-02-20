#include "featureselect.h"
#include "EmailLib.h"

void printMail (EMAIL msg);

int isReadable (EMAIL msg);

EMAIL createEmail (int from, int to);

EMAIL cloneEmail(EMAIL msg);
