
void
sendToAddressBook (CLIENT client, EMAIL msg)
{

}


void
outgoing (CLIENT client, EMAIL msg)
{

    int size = getClientAddressBookSize(client);
    
    if (size) {
        sendToAddressBook(client, msg);
        puts("sending to alias in address book\n");
        int receiver = getEmailTo(msg);

        puts("sending to second receipient\n");
        int second = getClientAddressBookAddress(client, 1);
        setEmailTo(msg, second);
        original (client, msg);
        //incoming (second, msg);
        
        setEmailTo(msg, getClientAddressBookAddress(client, 0));
        original (client, msg);
    } else {
        original (client, msg);
    }  

}
