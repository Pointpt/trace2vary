void
printMail (EMAIL msg)
{
  original (msg);
  printf ("ENCRYPTED\n  %d\n", isEncrypted(msg));
  printf ("ENCRYPTION KEY\n  %d\n", getEmailEncryptionKey(msg));
}


int
isReadable (EMAIL msg)
{
  if (!isEncrypted(msg))
    return original (msg);
  else
    return 0;
}
