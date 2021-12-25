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

namespace TimeClient
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void _btnConnect_Click(object sender, EventArgs e)
        {
            TcpClient client = new TcpClient(_labelServerIP.Text.Trim(), 8080);
            NetworkStream stream = client.GetStream();
            StreamReader read = new StreamReader(stream);
            DateTime data = DateTime.Parse(read.ReadLine());
            _labelServerIP.Text = data.ToLongTimeString().ToString();
        }
    }
}
