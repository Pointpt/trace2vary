// checks for a valid signature and replaces it by a flag signaling a verified signature
void
verify (CLIENT client, EMAIL msg)
{

  if (!isReadable (msg) || !isSigned(msg))
    return;
    
  int pubkey = findPublicKey(client, getEmailFrom(msg));
  if (pubkey && isKeyPairValid(getEmailSignKey(msg), pubkey)) {
    setEmailIsSignatureVerified(msg, 1);
  }

}

void
incoming (CLIENT client, EMAIL msg)
{
  verify (client, msg);
  original (client, msg);
}

