namespace Server
{
    public class Device
    {
        //Devicedaten
        private String operatingSystem = "";
        private String processor = "";
        private String Harddisk = "";

        public String OS
        {
            get
            {
                return operatingSystem;
            }
            set
            {
                operatingSystem = value;
            }
        }

        public String CPU
        {
            get
            {
                return processor;
            }
            set
            {
                processor = value;
            }
        }

        public String HDD
        {
            get
            {
                return Harddisk;
            }
            set
            {
                Harddisk = value;
            }
        }
    }
}
