namespace Client
{
    class Client
    {
        private Stream getStream(NetworkStream clientStream)
        {
            return StreamVerschluesselung(clientStream);
        }

        //Methode um den gesamten NetworkStream des TCP Clients mit dem Rijndael Algorithmus zu verschlüsseln
        private CryptoStream StreamVerschluesselung(NetworkStream clientStream)
        {
            // Erzeugen der Verschlüsselungsklasse
            RijndaelManaged RMCrypto = new RijndaelManaged();

            //Keys für die symmetrische Verschlüsselung
            byte[] Key = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };
            byte[] IV = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16 };

            //Erzeugen eines Verschlüsselten Datentroms, mit Hilfe der Keys und der Verschlüsselungsklasse
            return new CryptoStream(clientStream, RMCrypto.CreateEncryptor(Key, IV), CryptoStreamMode.Write);
        }

    }
}
