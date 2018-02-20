#include "ClientLib.h"
#include "Email.h"
#include "EmailLib.h"

/*
 * two sorts of emails are processed by this client: incoming and outgoing ones.
 * control flow is
 * email from internet > incoming > deliver > receipient receives mail
 * sender writes email > outgoing > mail > email sent through internet
 */
void queue (CLIENT client, EMAIL msg);

int is_queue_empty ();
CLIENT get_queued_client ();
EMAIL get_queued_email ();

void mail (CLIENT client, EMAIL msg);
void outgoing (CLIENT client, EMAIL msg);
void deliver (CLIENT client, EMAIL msg);
void incoming (CLIENT client, EMAIL msg);
CLIENT createClient(char *name);

void sendEmail (CLIENT sender, CLIENT receiver);
