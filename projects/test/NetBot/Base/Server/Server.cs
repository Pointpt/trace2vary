using System;
using System.Text;
using System.Net.Sockets;
using System.Threading;
using System.Net;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.IO;



namespace Server
{
    class Server
    {
        private TcpListener tcpListener;
        private Thread listenThread;
        private Controller Owner;
        private List<Thread> clientThreads = new List<Thread>();

        public Server(Controller own, int port)
        {
            this.Owner = own;
            this.tcpListener = new TcpListener(IPAddress.Any, port);
            this.listenThread = new Thread(new ThreadStart(ListenForClients));
            this.listenThread.Start();
        }

        private void ListenForClients()
        {
            this.tcpListener.Start();

            while (true)
            {
                //Status anzeigen
                ((UIMainWindow)Owner.Owner).OnStatusEvent("Warten auf Verbindungen...");
                //Blockiert solange bis sich ein Client am Server anmeldet
                TcpClient client = this.tcpListener.AcceptTcpClient();
                
                //Aufbau eines aktiven Kommunikationsthreads
                Thread clientThread = new Thread(new ParameterizedThreadStart(HandleClientComm));
                clientThreads.Add(clientThread);
                clientThread.Start(client);
            }
        }

        private void HandleClientComm(object client)
        {
            TcpClient tcpClient = (TcpClient)client;
            NetworkStream clientStream = tcpClient.GetStream();

            StreamReader SReader = new StreamReader(getIncomingStream(clientStream));
            
            //Lesen aus dem Datenstrom
             String empfangen="";

            empfangen = SReader.ReadToEnd();
            
            
            String[] identifikation = tcpClient.Client.RemoteEndPoint.ToString().Split(':');
            Message answer = Owner.processingMessage(new Message(identifikation[0], Convert.ToInt32(identifikation[1]), empfangen));
            if (answer != null)
            {
                sendtoClient(tcpClient, answer.Msg);
            }
            
            //Schlieﬂen des Datenstroms und des TCPClients
	    SReader.BaseStream.Close();
            SReader.Close();
            tcpClient.Close();
        }

        private Stream getIncomingStream(NetworkStream clientStream)
        {
            return clientStream;
        }

        private Stream getOutgoingStream(NetworkStream clientStream)
        {
            return clientStream;
        }

        public void sendtoClient(TcpClient tcpClient, String nachricht)
        {
            NetworkStream clientStream = tcpClient.GetStream();

            StreamWriter SWriter = new StreamWriter(getOutgoingStream(clientStream));

            //Schreiben auf dem Stream
            SWriter.WriteLine(nachricht);

            //Close all the connections.
	    SWriter.BaseStream.Close();
            SWriter.Close();
            clientStream.Flush();     
        }

        public void stopServer()
        {
            tcpListener.Stop();
            listenThread.Abort();
            foreach (Thread th in clientThreads)
                th.Abort();
        }


    }
}
