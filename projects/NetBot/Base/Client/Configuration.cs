using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Client
{
    public class Configuration
    {
        //Datenelemente
        static String serverAddress="";
        static int serverPort = 0;
        static Boolean autoAnmelden = false;


        //ConvertMethoden
        public static String configurationToXML()
        {
            String xml = "";
            xml += "<configuration>";
                xml += "<communication>";
                    xml += "<targetIP>";
                        xml += serverAddress;
                    xml += "</targetIP>";
                    xml += "<targetPort>";
                        xml += Convert.ToString(serverPort);
                    xml += "</targetPort>";
                xml += "</communication>";
                xml += "<connectType>";
                    xml += "<AutoAnmeldung>";
                        xml += Convert.ToString(autoAnmelden);
                    xml += "</AutoAnmeldung>";
                xml += "</connectType>";
            xml += "</configuration>";
            return xml;
        }


        public static void XMLtoConfiguration(String XML)
        {
            XmlDocument xmldoc = new XmlDocument();
            xmldoc.LoadXml(XML);
            serverAddress = xmldoc["configuration"]["communication"]["targetIP"].InnerText;
            serverPort = Convert.ToInt32(xmldoc["configuration"]["communication"]["targetPort"].InnerText);
            autoAnmelden = Convert.ToBoolean(xmldoc["configuration"]["connectType"]["AutoAnmeldung"].InnerText);
        }

        //Öffentliche Zugriffsmethoden
        public static String targetIP
        {
            get { return serverAddress; }
            set { serverAddress = value; }
        }
        public static int targetPort
        {
            get { return serverPort; }
            set { serverPort = value; }
        }
        public static Boolean AutomatischeAnmeldung
        {
            get { return autoAnmelden; }
            set { autoAnmelden = value; }
        }


    }
}
