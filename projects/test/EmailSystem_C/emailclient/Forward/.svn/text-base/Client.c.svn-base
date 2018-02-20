
void
forward (CLIENT client, EMAIL msg)
{  
  puts("Forwarding message.\n");  
  printMail(msg);
  queue(client, msg);
 
}

void
incoming (CLIENT client, EMAIL msg)
{  
  original (client, msg);
  int fwreceiver = getClientForwardReceiver(client);
  if (fwreceiver) {
    
    setEmailTo(msg, fwreceiver);  
    forward (client, msg);
    
  }
}
