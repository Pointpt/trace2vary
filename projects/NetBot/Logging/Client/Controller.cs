namespace Client
{
    class Controller
    {
        private void recognizeAutomaticLogin()
        {
            original();
            Logging("NCS Client hat sich erfolgreich mit Server verbunden");
        }

        public void sendOverClient(String msg)
        {
            original(msg);
            Logging("Senden an Server");
        }

        public void saveConfiguration()
        {
            original();
            Logging("Konfiguration gespeichert");
        }

        public void loadConfiguration()
        {
            original();
            Logging("Konfiguration geladen");
        }

        // Verhaltensweisen im Client werden mitgeloggt und lokal auf dem Client gespeichert
        private void Logging(String Logmessage)
        {
            try
            {
                StreamWriter writer = new StreamWriter("ClientLog.txt", true);
                writer.WriteLine(DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + " | " + Logmessage);
                writer.Close();
            }
            catch (Exception ef)
            {

            }
        }

    }
}
