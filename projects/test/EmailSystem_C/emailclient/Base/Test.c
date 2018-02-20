#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Client.h"
#include "Test.h"
#include "Util.h"

//setup hooks

void 
setup_bob(CLIENT bob) 
{
    setClientId(bob, bob);
}


void 
setup_rjh(CLIENT rjh)
{    
    setClientId(rjh, rjh);
}

void 
setup_chuck(CLIENT chuck)
{
    setClientId(chuck, chuck);
}



//actions

void
bobToRjh()
{

  puts("Please enter a subject and a message body.\n");
  sendEmail(bob,rjh);
  if (!is_queue_empty()) {
    outgoing(get_queued_client(), get_queued_email());
  }
}

void
rjhToBob()
{

  puts("Please enter a subject and a message body.\n");
  sendEmail(rjh,bob);
}

int get_nondet() {
    int nd;
    return nd;
}


void setup() {
  bob = 1;
  setup_bob(bob);
  printf("bob: %d\n",bob);
  //rjh = createClient("rjh");
  rjh = 2;
  setup_rjh(rjh);
  printf("rjh: %d\n",rjh);  
  //chuck = createClient("chuck");
  chuck = 3;
  setup_chuck(chuck);
  printf("chuck: %d\n",chuck);
}

int
main (void)
{ 
  select_helpers();
  select_features();
  if (valid_product()) { 
      setup();
      test();
  }

}
