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
using System.Diagnostics;
using System.Runtime.Serialization.Formatters.Binary;
using System.Runtime.Serialization;
using System.Collections;
using System.IO;

namespace ChatClient
{
    public partial class Form1 : Form
    {
        private UdpClient _server;
        private IPEndPoint _ipe;
        private DataTable _dt;
        private string _UID;
        public Form1()
        {
            InitializeComponent();
            _initDataTable();
            _initServer();
            _initUID();
        }

        private void _initUID()
        {
            _UID = Guid.NewGuid().ToString();
        }

        private void _initDataTable()
        {
            _dt = new DataTable();
            _dt.Columns.Add("UID", typeof(string));
            _dt.Columns.Add("Chat", typeof(string));
            _gridControlChatHistory.DataSource = _dt;
            _gridViewChatHistory.CustomDrawCell += _gridViewChatHistory_CustomDrawCell;
        }


        private void _initServer()
        {
            try
            {
                _server = new UdpClient("127.0.0.1", 8080);
                Debug.Print("UDP 서버 접속 성공...\n");
                _ipe = new IPEndPoint(IPAddress.Any, 0);
            }
            catch (Exception e)
            {
                Debug.Print(e.ToString());
            }
        }

        private void _endServer()
        {
            _server.Close();
            Debug.Print("UDP 서버 접속 종료...\n");
        }

        private void _sendData()
        {
            byte[] data = new byte[1024];
            data = _convertByte(_UID);
            _server.Send(data, data.Length);

            data = new byte[1024];
            data = _convertByte(_textBoxSend.Text);
            _server.Send(data, data.Length);

            DataRow insertData = _dt.NewRow();
            insertData["UID"] = _UID;
            insertData["Chat"] = _textBoxSend.Text;
            _dt.Rows.Add(insertData);
            _textBoxSend.Text = "";
        }

        private void _btnSend_Click(object sender, EventArgs e)
        {
            if (!_isTextEmpty(_textBoxSend.Text))
                _sendData();
        }

        private void _gridViewChatHistory_CustomDrawCell(object sender, DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventArgs e)
        {
            DataRow row = _gridViewChatHistory.GetDataRow(e.RowHandle);
        }

        private byte[] _convertByte(string str)
        {
            return Encoding.Default.GetBytes(str);
        }

        private bool _isTextEmpty(string text)
        {
            if (text == null)
                return true;
            else if (text == "")
                return true;
            return false;
        }
    }
}
