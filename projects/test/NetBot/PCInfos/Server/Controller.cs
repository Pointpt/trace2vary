namespace Server
{
    class Controller
    {
        private void loadDeviceInfos(Device dev, Message msg)
        {
            XmlDocument auswertung = new XmlDocument();
            try
            {
                //Substring für XML Auswertung wegen /r/n
                auswertung.LoadXml(msg.Msg.Substring(0, msg.Msg.Length - 2));
                dev.OS = auswertung["Message"]["Head"]["OS"].InnerText;
                dev.CPU = auswertung["Message"]["Head"]["CPU"].InnerText;
                dev.HDD = auswertung["Message"]["Head"]["Harddisk"].InnerText;
            }
            catch (Exception ef) { };
        }
    }
}
