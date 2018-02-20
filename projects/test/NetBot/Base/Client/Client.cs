using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;
using System.Security.Cryptography;

namespace Client
{
    class Client
    {
        String ipAddress = "";
        int port = 0;
        Controller owner;
        TcpClient client; 
        public Client(String ip, int port, Controller owner)
        {
            this.ipAddress = ip;
            this.port = port;
            this.owner = owner;
        }

        private void createConnection()
        {
            try
            {
                client = new TcpClient();

                IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(Configuration.targetIP), Configuration.targetPort);

                client.Connect(serverEndPoint);
            }
            catch (Exception ef) { };
        }

        public void sendAndReceive(String msg)
        {
            Thread serverThread = new Thread(new ParameterizedThreadStart(send));

            serverThread.Start(msg);
        }



        public void send(object obj)
        {
            try
            {
                createConnection();
                String msg = (String)obj;

                NetworkStream clientStream = client.GetStream();

                StreamWriter SWriter = new StreamWriter(getStream(clientStream));

                //Schreiben auf dem Stream
                SWriter.WriteLine(msg);
                
                //Close all the connections.
		SWriter.Close();
		clientStream.Flush();
		ConnectionClosed();
            }
            catch (Exception ef)
            {
                owner.BalloonTipText("Der Server ist nicht erreichbar. Überprüfen Sie ihre Verbindungsparameter.",System.Windows.Forms.ToolTipIcon.Error);
            }
        }

        private Stream getStream(NetworkStream clientStream)
        {
            return clientStream;
        }

        private void ConnectionClosed()
        {
            client.Close();
        }

    }
}
