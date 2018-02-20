using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Server
{
    public class Data
    {
        static List<Device> networkDevices = new List<Device>();

        
        //Öffentliche Zugriffsmethoden
        public static List<Device> Devices
        {
            get { return networkDevices; }
            set { networkDevices = value; }
        }
    }
}
