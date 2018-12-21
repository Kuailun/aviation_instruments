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
    class Program
    {
         static void Main(string[] args)
         {
            InstrumentX_Interface instrumentX_Interface=new InstrumentX_Interface();
            InstrumentX_Data instrumentX_Data = new InstrumentX_Data();

            instrumentX_Data.degree_pitch = 10;

            instrumentX_Interface.Start(ref instrumentX_Data);

            instrumentX_Data.degree_pitch = 0;
            instrumentX_Data.degree_bank = 0;

            int i = 0;
            while(i!=150)
            {
                Thread.Sleep(51);
                instrumentX_Data.degree_pitch+=10;
                instrumentX_Data.degree_bank+=10;
                i++;
            }
            instrumentX_Interface.Stop();
        }
    }
}
