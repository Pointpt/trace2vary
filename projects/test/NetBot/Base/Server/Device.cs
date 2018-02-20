using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace Server
{
    public class Device
    {
        //Kommunikationsparameter
        String identifikation="";
        String ipAddress="";
        String port="";

        //Logindaten
        String lastLoginTime="";
        Boolean currentlyLogin = false;

        public Device(String ip, String port)
        {
            this.ipAddress = ip;
            this.port = port;
            this.identifikation = "PC_" + this.ipAddress;
            this.lastLoginTime = Convert.ToString(DateTime.Now);
            this.currentlyLogin = true;
        }

        public void Login()
        {
            this.lastLoginTime = Convert.ToString(DateTime.Now);
            this.currentlyLogin = true;
        }

        public void Logout()
        {
            this.currentlyLogin = false;
        }

        //Öffentliche Zugriffsmethoden
        public String Name
        {
            get { return identifikation; }
            set { identifikation = value; }
        }

        public String IP
        {
            get { return ipAddress; }
            set { ipAddress = value; }
        }
        public String Port
        {
            get { return port; }
            set { port = value; }
        }
        public String lastLogin
        {
            get { return lastLoginTime; }
            set { lastLoginTime = value; }
        }
        public Boolean isLogin
        {
            get { return currentlyLogin; }
            set { currentlyLogin = value; }
        }
    }
}
