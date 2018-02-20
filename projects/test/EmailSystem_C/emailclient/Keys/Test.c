void
setup_bob(CLIENT bob)
{
  original(bob);
  setClientPrivateKey(bob, 123);
  
}

void
setup_rjh(CLIENT rjh)
{

  original(rjh);
  setClientPrivateKey(rjh, 456);
 
}

void
setup_chuck(CLIENT chuck)
{
  original(chuck);
  setClientPrivateKey(chuck, 789);
}

void
bobKeyAdd()
{ 
    createClientKeyringEntry(bob);    
    setClientKeyringUser(bob, 0, 2);
    setClientKeyringPublicKey(bob, 0, 456);    
    puts("bob added rjhs key");
    printf("%d\n",getClientKeyringUser(bob, 0));
    printf("%d\n",getClientKeyringPublicKey(bob, 0));    
}

void
rjhKeyAdd()
{
    createClientKeyringEntry(rjh);
    setClientKeyringUser(rjh, 0, 1);
    setClientKeyringPublicKey(rjh, 0, 123);
}

void
rjhKeyAddChuck()
{
    createClientKeyringEntry(rjh);
    setClientKeyringUser(rjh, 0, 3);
    setClientKeyringPublicKey(rjh, 0, 789);
}


void
bobKeyAddChuck()
{
    createClientKeyringEntry(bob);
    setClientKeyringUser(bob, 1, 3);
    setClientKeyringPublicKey(bob, 1, 789);
}

void
chuckKeyAdd()
{
    createClientKeyringEntry(chuck);
    setClientKeyringUser(chuck, 0, 1);
    setClientKeyringPublicKey(chuck, 0, 123);
}

void
chuckKeyAddRjh()
{
    createClientKeyringEntry(chuck);
    setClientKeyringUser(chuck, 0, 2);
    setClientKeyringPublicKey(chuck, 0, 456);
}

void
rjhDeletePrivateKey()
{
    setClientPrivateKey(rjh, 0);
}

void
bobKeyChange()
{
  generateKeyPair(bob, 777);
}

void
rjhKeyChange()
{
  generateKeyPair(rjh, 666);
}


