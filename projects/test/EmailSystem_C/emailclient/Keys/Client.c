
int
isKeyPairValid (int publicKey, int privateKey)
{
    printf("keypair valid %d %d", publicKey, privateKey);
  if (!publicKey || !privateKey)
    return 0;
  return privateKey == publicKey;
}

void
generateKeyPair (CLIENT client, int seed)
{
    setClientPrivateKey(client, seed);
}
