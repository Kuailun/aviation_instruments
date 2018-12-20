using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace InstrumentX_Interface_CSharp
{
    class InstrumentX_Interface
    {
        private static Socket sock;
        private static IPEndPoint iep1;
        private static byte[] data;
        private Thread t;
        private bool running = false;
        private InstrumentX_Data m_data;

        public void Start(ref InstrumentX_Data p_data)
        {
            m_data = p_data;
            running = true;
            t = new Thread(BroadcastMessage);
            t.Start();
        }
        public void Stop()
        {
            running = false;
        }

        public InstrumentX_Interface()
        {
            m_data = new InstrumentX_Data();
            sock = new Socket(AddressFamily.InterNetwork, SocketType.Dgram,ProtocolType.Udp);
            //255.255.255.255
            iep1 =
            new IPEndPoint(IPAddress.Broadcast, 1011);
            string hostname = Dns.GetHostName();
            data = Encoding.ASCII.GetBytes(hostname);
            sock.SetSocketOption(SocketOptionLevel.Socket,SocketOptionName.Broadcast, 1);
        }

        public void SetData()
        {
            string json = JsonConvert.SerializeObject(m_data);
            data = System.Text.Encoding.Default.GetBytes(json);
        }

        private void BroadcastMessage()
        {
            while (running)
            {
                SetData();
                sock.SendTo(data, iep1);
                Thread.Sleep(100);
            }

        }
    }
}
