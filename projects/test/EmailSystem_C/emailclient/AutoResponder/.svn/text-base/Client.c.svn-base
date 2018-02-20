#include <string.h>
#include "Client.h"
void
autoRespond (CLIENT client, EMAIL msg)
{
  puts("sending autoresponse\n");
  int sender = getEmailFrom(msg);
  setEmailTo(msg, sender);
  queue(client, msg);
}

void
incoming (CLIENT client, EMAIL msg)
{    
  original (client, msg);
  if (getClientAutoResponse(client)) {
    autoRespond (client, msg);
  }
}
