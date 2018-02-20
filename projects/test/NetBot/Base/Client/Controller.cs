using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml.Serialization;
using System.Management;
using Microsoft.Win32;
using System.Threading;

namespace Client
{
    class Controller
    {
        System.Windows.Forms.Form owner;
        Client communicationClient;
        Boolean angemeldet = false;

        //Menüitems für das Kontextmenü
        System.Windows.Forms.MenuItem menuItem1;
        System.Windows.Forms.MenuItem menuItem2;
        System.Windows.Forms.MenuItem menuItem3;


        public Controller(System.Windows.Forms.Form own)
        {
            this.owner = own;
            loadConfiguration();
            createClient();
            
        }


        private void createClient()
        {
            communicationClient = new Client(Configuration.targetIP, Configuration.targetPort, this);
            if (Configuration.AutomatischeAnmeldung)
            {
                sendStartMessageToServer();
                recognizeAutomaticLogin();
            }
            else
            {
                BalloonTipText("Automatisches anmelden deaktiviert. Zum Verbinden mit dem Server verwenden Sie die manuelle Anmeldung", System.Windows.Forms.ToolTipIcon.Info);
            }
        }

        private void sendStartMessageToServer()
        {
            sendOverClient("");
        }

        private void recognizeAutomaticLogin()
        {
            BalloonTipText("NCS Client hat sich erfolgreich mit Server verbunden", System.Windows.Forms.ToolTipIcon.Info);
            angemeldet = true;
        }

        public void sendOverClient(String msg)
        {
            communicationClient.sendAndReceive(msg);
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
                return;
            }

        }

        public void loadConfiguration()
        {
            StreamReader fileReader;
            string filePath = "configuration.xml";
            if (File.Exists(filePath))
            {
                fileReader = new StreamReader(filePath);
                Configuration.XMLtoConfiguration(fileReader.ReadLine());
                fileReader.Close();
            }
        }

        public System.Windows.Forms.ContextMenu createClientMenu()
        {
            System.Windows.Forms.ContextMenu contextMenu;
            contextMenu = new System.Windows.Forms.ContextMenu();
            
            menuItem1 = new System.Windows.Forms.MenuItem();
            menuItem2 = new System.Windows.Forms.MenuItem();
            menuItem3 = new System.Windows.Forms.MenuItem();
            
            contextMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] { menuItem1 });
            contextMenu.MenuItems.Add("-");
            contextMenu.MenuItems.AddRange(new System.Windows.Forms.MenuItem[] { menuItem2, menuItem3 });

            menuItem1.Index = 0;
            menuItem1.Text = "Automatisch an- oder abmelden";
            menuItem1.Name = "autoAnmeldung";
    
            menuItem2.Index = 1;
            if(Configuration.AutomatischeAnmeldung)
                menuItem2.Text = "Abmelden";
            else
                menuItem2.Text="Anmelden";

            menuItem3.Index = 2;
            menuItem3.Text = "Beenden";
            
            ConnectMenuWithClickHandler(ref menuItem1, new EventHandler(this.ClickAutoAnAbmelden));
            ConnectMenuWithClickHandler(ref menuItem2, new EventHandler(this.ClickAnAbmelden));
            ConnectMenuWithClickHandler(ref menuItem3, new EventHandler(this.ClickBeenden));

            return contextMenu;
        }

        private void ConnectMenuWithClickHandler(ref System.Windows.Forms.MenuItem MenuItem, EventHandler newHandler)
        {
            MenuItem.Click += newHandler;
        }

        public void BalloonTipText(String text, System.Windows.Forms.ToolTipIcon icon)
        {
            ((TrayForm)owner).Tray.BalloonTipText = text;
            ((TrayForm)owner).Tray.BalloonTipIcon = icon;
            ((TrayForm)owner).Tray.ShowBalloonTip(10);
        }

        public void ClickAutoAnAbmelden(object Sender, EventArgs e)
        {
            if (Configuration.AutomatischeAnmeldung)
                Configuration.AutomatischeAnmeldung = false;
            else
                Configuration.AutomatischeAnmeldung = true;
            ((TrayForm)owner).Update();

        }

        public void ClickAnAbmelden(object Sender, EventArgs e)
        {
            if (!angemeldet)
            {
                this.sendOverClient("test");
                menuItem2.Text = "Abmelden";
                angemeldet = true;
            }
            else
            {
                this.sendOverClient("<logout/>");
                menuItem2.Text = "Anmelden";
                angemeldet = false;
            }
        }

        public void ClickBeenden(object Sender, EventArgs e)
        {
            Dispose();
        }


        public void Dispose()
        {
            saveConfiguration();
            owner.Dispose();
        }

        //Öffentliche Zugriffsmethoden
        public System.Windows.Forms.Form Owner
        {
            get { return owner; }
            set { owner = value; }
        }

    }
}
