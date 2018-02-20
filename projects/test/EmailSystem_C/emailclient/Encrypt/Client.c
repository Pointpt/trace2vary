void
outgoing (CLIENT client, EMAIL msg)
{ 
  
  //encrypt
    int receiver = getEmailTo(msg);
    int pubkey = findPublicKey(client, receiver);
    if (pubkey) {
        setEmailEncryptionKey(msg, pubkey);
        setEmailIsEncrypted(msg, 1);
    }
  
  //end encrypt
  
  original (client, msg);
}


