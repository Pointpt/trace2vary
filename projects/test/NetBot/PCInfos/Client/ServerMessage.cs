using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Client
{
    class ServerMessage
    {
        String OS = null;
        String CPU = null;
        String Harddisk= null;
        String text = null;
        public ServerMessage(String os, String cpu, String hdd)
        {
            this.OS = os;
            this.CPU = cpu;
            this.Harddisk  = hdd;
        }

        public String ToString()
        {
            String ServerMessage = "";


            ServerMessage += "<Message>";
                ServerMessage += "<Head>";
                if (OS != null)
                {
                    ServerMessage += "<OS>";
                    ServerMessage += this.OS;
                    ServerMessage += "</OS>";
                }
                if (CPU != null)
                {
                    ServerMessage += "<CPU>";
                    ServerMessage += this.CPU;
                    ServerMessage += "</CPU>";
                }
                if (Harddisk != null)
                {
                    ServerMessage += "<Harddisk>";
                    ServerMessage += this.Harddisk;
                    ServerMessage += "</Harddisk>";
                }
                ServerMessage += "</Head>";
                ServerMessage += "<Body>";
                if (text != null)
                {
                    ServerMessage += "<Text>";
                    ServerMessage += this.text;
                    ServerMessage += "</Text>";
                }
                ServerMessage += "</Body>";
            ServerMessage += "</Message>";

            return ServerMessage;
        }
    }
}
