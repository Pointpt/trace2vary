#include <stdio.h>
#include "Client.h"

int queue_empty = 1;

EMAIL queued_message;

CLIENT queued_client;

// outgoing emails leave the client at this point. here they are put in an outgoing queue instead.
void
mail (CLIENT client, EMAIL msg)
{
  puts("mail sent");
  incoming (getEmailTo(msg), msg);
}

// emails to be sent are processed by this method before beeing mailed.
void
outgoing (CLIENT client, EMAIL msg)
{
  setEmailFrom(msg, getClientId(client));
  mail(client, msg);
}

// incoming emails reach the user at this point. here they are put in a mailbox.
void
deliver (CLIENT client, EMAIL msg)
{
   puts("mail delivered\n");   
}

// incoming emails are processed by this method before delivery.
void
incoming (CLIENT client, EMAIL msg)
{
  deliver (client, msg);
}

CLIENT createClient(char *name) {
    CLIENT client = initClient();
    return client;
}

void
sendEmail (CLIENT sender, CLIENT receiver) 
{
  EMAIL email = createEmail (0, receiver);
  outgoing (sender, email);
  //incoming (receiver, email);
  
}

void
queue (CLIENT client, EMAIL msg)
{
    queue_empty = 0;
    queued_message = msg;
    queued_client = client;
}

int
is_queue_empty ()
{
    return queue_empty;
}

CLIENT
get_queued_client ()
{
    return queued_client;
}

EMAIL
get_queued_email ()
{
    return queued_message;
}


