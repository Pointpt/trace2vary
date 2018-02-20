using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;
using System.Xml.Serialization;
using System.Text;
using System.Xml;

namespace Server
{
    class Controller
    {
        System.Windows.Forms.Form owner;
        Server server;

        public Controller(System.Windows.Forms.Form own)
        {
            this.owner = own;
        }


        public void createServer()
        {
            server = new Server(this,Configuration.Port);
        }

        public void saveConfiguration()
        {
            try
            {

                String filePath = "configuration.xml";
                StreamWriter fileWriter = null;

                fileWriter = File.CreateText(filePath);


                String str = Configuration.configurationToXML();
                fileWriter.Write(str);

                if (fileWriter != null)
                    fileWriter.Close();
            }
            catch (Exception ef)
            {
            }

        }

        public Message processingMessage(Message msg)
        {
            //Vorhandenen Client identifizieren
            Boolean vorhanden = false;
            int vorhandenIndex = -1;
            for (int i=0;i< Data.Devices.Count;i++)
            {
                if (msg.sourceIP.Equals(Data.Devices[i].IP))
                {
                    vorhanden = true;
                    vorhandenIndex = i;
                }
            }
            //Device hinzufügen
            if (!vorhanden)
            {
                Device dev = new Device(msg.sourceIP, Convert.ToString(msg.sourcePort));
                loadDeviceInfos(dev,msg);
                Data.Devices.Add(dev);
                ((UIMainWindow)Owner).OnStatusEvent("Ein neuer Client mit der IP " + msg.sourceIP + " hat sich angemeldet");
            }
            else
            {
                Data.Devices[vorhandenIndex].Login();
                ((UIMainWindow)Owner).OnStatusEvent("Ein bekannter Client (" + Data.Devices[vorhandenIndex].Name + ") hat sich wieder angemeldet");
            }
            ((UIMainWindow)Owner).OnUpdateEvent();
            
            Message answer=null;

            //Antwortauswertung ======================================
            XmlDocument xml = new XmlDocument();
            Boolean logout = false;
            try
            {
                xml.LoadXml(msg.Msg);
                if(xml.InnerXml.Equals("<logout />"))
                    logout = true;
            }
            catch (Exception ef)
            {
                xml = null;
            }

            //Logouterkennung
            if (xml != null && logout)
            {
                for (int i = 0; i < Data.Devices.Count; i++)
                {
                    if (msg.sourceIP.Equals(Data.Devices[i].IP))
                    {
                        Data.Devices[i].Logout();
                        ((UIMainWindow)Owner).OnUpdateEvent();
                        ((UIMainWindow)Owner).OnStatusEvent("Der Client ("+Data.Devices[i].Name+") hat sich abgemeldet");
                    }
                }
            }




            msg.answerMessage("angekommen");

            return answer;
        }

        private void loadDeviceInfos(Device dev, Message msg)
        {
        }

        public void Dispose()
        {
            server.stopServer();
        }

        //Öffentliche Zugriffsmethoden
        public System.Windows.Forms.Form Owner
        {
            get { return owner; }
            set { owner = value; }
        }




    }
}
