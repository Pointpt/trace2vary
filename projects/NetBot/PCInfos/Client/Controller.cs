namespace Client
{
    class Controller
    {
        private void sendStartMessageToServer()
        {
            sendOverClient(new ServerMessage(OSDetection(),CPUDetection(),HDDDetection()).ToString());
        }

        /* Systemdaten
         * ===================
         * Beispielhaft werden Name des Betriebssystems, Prozessorinformationen und Systemfestplatteninformationen angezeigt
         * 
         */
        string HDDDetection()
        {
            String space = Convert.ToString(System.IO.DriveInfo.GetDrives()[0].TotalSize / 1024 / 1024 / 1024) + "GB";
            String name = System.IO.DriveInfo.GetDrives()[0].Name;
            return name + " ( " + space + " )";
        }

        string CPUDetection()
        {
            RegistryKey RegKey = Registry.LocalMachine;
            RegKey = RegKey.OpenSubKey("HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0");
            Object cpuSpeed = RegKey.GetValue("~MHz");
            Object cpuType = RegKey.GetValue("ProcessorNameString");
            return cpuType + " ( " + cpuSpeed + " MHz )";
        }

        string OSDetection()
        {
            OperatingSystem myOSSystem = System.Environment.OSVersion;
            string myVersion = "";

            if (myOSSystem.Platform == PlatformID.Win32NT)
            {
                if (myOSSystem.Version.Major == 4) myVersion = "Win NT 4.0";
                if (myOSSystem.Version.Major == 5)
                {
                    switch (myOSSystem.Version.Minor)
                    {
                        case 0:
                            myVersion = "Win 2000";
                            break;
                        case 1:
                            myVersion = "Win XP";
                            break;
                        case 2:
                            myVersion = "Win 2003 Server";
                            break;
                    }
                }
                if (myOSSystem.Version.Major == 6)
                {
                    switch (myOSSystem.Version.Minor)
                    {
                        case 0:
                            myVersion = "Windows Vista";
                            break;
                        case 1:
                            myVersion = "Windows 7";
                            break;
                    }
                }

            }


            if (myVersion != "")
                return myVersion + " ( " + System.Environment.OSVersion + " )";
            else
                return "Betriebssystem konnte nicht ermittelt werden!";
        }
    }
}
