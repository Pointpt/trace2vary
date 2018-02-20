using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Server
{
    public class Configuration
    {
        //Datenelemente
        static int communicationPort=2000;



        //ConvertMethoden
        public static String configurationToXML()
        {
            String xml = "";
            xml += "<configuration>";
                xml += "<communication>";
                    xml += "<port>";
                        xml += Convert.ToString(communicationPort);
                    xml += "</port>";
                xml += "</communication>";
            xml += "</configuration>";
            return xml;
        }


        public static void XMLtoConfiguration()
        {

        }

        //Öffentliche Zugriffsmethoden
        public static int Port
        {
            get { return communicationPort; }
            set { communicationPort = value; }
        }



    }
}
