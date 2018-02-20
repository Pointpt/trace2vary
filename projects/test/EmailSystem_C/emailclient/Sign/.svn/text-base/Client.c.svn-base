// adds the sign flag to message body
void
sign (CLIENT client, EMAIL msg)
{
  int privkey = getClientPrivateKey(client);
  if (!privkey)
    return;
  setEmailIsSigned(msg, 1);
  setEmailSignKey(msg, privkey);
}

void
outgoing (CLIENT client, EMAIL msg)
{
  sign (client, msg);
  original (client, msg);
}


