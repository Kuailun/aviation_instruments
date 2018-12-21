using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using InstrumentX_Interface_CSharp;
using System.Threading;

namespace InstrumentX_CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            InstrumentX_Interface instrumentX_Interface = new InstrumentX_Interface();
            InstrumentX_Data instrumentX_Data = new InstrumentX_Data();

            instrumentX_Data.degree_pitch = 10;

            instrumentX_Interface.Start(ref instrumentX_Data);

            instrumentX_Data.degree_pitch = 0;
            instrumentX_Data.degree_bank = 0;

            int i = 0;
            while (i != 100)
            {
                Thread.Sleep(51);
                instrumentX_Data.degree_pitch += 10;
                instrumentX_Data.degree_bank += 10;
                instrumentX_Data.speed_indicator_speed += 2;
                i++;
            }
            instrumentX_Interface.Stop();
        }
    }
}
