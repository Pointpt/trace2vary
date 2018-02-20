
void
incoming (CLIENT client, EMAIL msg)
{
  //decrypt
  
  int privkey = getClientPrivateKey(client);
  if (privkey) {
    
      if (isEncrypted(msg)
          && isKeyPairValid(getEmailEncryptionKey(msg), privkey))
        {
          setEmailIsEncrypted(msg, 0);
          setEmailEncryptionKey(msg, 0);
        }
  }  
  //end decrypt
  
  original (client, msg);
}
