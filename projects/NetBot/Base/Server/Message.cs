using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Server
{
    class Message
    {
        String absenderIP;
        int absenderPort;
        String nachricht;

        public Message(String IP, int port, String msg)
        {
            this.absenderIP = IP;
            this.absenderPort = port;
            this.nachricht = msg;
        }

        public Message answerMessage(String msg)
        {
            nachricht = msg;
            return this;
        }
        

        //Öffentliche Zugriffsmethoden
        public String sourceIP
        {
            get { return absenderIP; }
        }

        public int sourcePort
        {
            get { return absenderPort; }
        }

        public String Msg
        {
            get { return nachricht; }
        }

    }
}
