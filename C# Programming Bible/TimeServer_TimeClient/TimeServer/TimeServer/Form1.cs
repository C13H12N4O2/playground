using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.IO;
using System.Threading;

namespace TimeServer
{
    public partial class Form1 : Form
    {
        public NetworkStream stream;
        public const int port = 8080;

        TcpListener listener = null;

        StreamWriter write = null;

        Thread th = null;
        
        public Form1()
        {
            InitializeComponent();
            _initBtn();
        }

        private void _initBtn()
        {
            _btnServerStart.Click += _btn_Click;
            _btnServerEnd.Click += _btn_Click;
        }

        void Accept()
        {
            try
            {
                listener = new TcpListener(port);
                listener.Start();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error Message : " + ex.StackTrace);
            }

            _enabledSwitch();

            Socket client = listener.AcceptSocket();

            if (client.Connected)
            {
                stream = new NetworkStream(client);
                write = new StreamWriter(stream);
                write.Write(DateTime.Now);
                write.Flush();
            }
        }

        void Stop()
        {
            try
            {
                listener.Stop();
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error Message : " + ex.StackTrace);
            }

            _enabledSwitch();
        }

        private void _enabledSwitch()
        {
            /*
            if (_btnServerStart.Enabled == true)
            {
                _btnServerStart.Enabled = false;
                _btnServerEnd.Enabled = true;
            }
            else
            {
                _btnServerStart.Enabled = true;
                _btnServerEnd.Enabled = false;
            }
             */
        }

        private void _btn_Click(object sender, EventArgs e)
        {
            Button btn = sender as Button;

            if (btn.AccessibleName == "Start")
            {
                MessageBox.Show("Test");
                th = new Thread(new ThreadStart((Accept)));
                th.Start();
            }
            else
            {
                this.Stop();

                try
                {
                    th.Abort();
                }
                catch
                {

                }
            }
        }
    }
}
