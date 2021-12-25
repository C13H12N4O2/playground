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
using System.IO;

namespace ChatServer
{
    public partial class Form1 : Form
    {
        private Dictionary<string, string> _dictionary;
        private List<string> _color;
        private UdpClient _server;
        private IPEndPoint _ipe;
        private DataTable _dt;
        private string _fileName;

        public Form1()
        {
            _init();
            InitializeComponent();
            _initDataTable();
            _initServer();
            _receiveData();
        }

        private void _init()
        {
            _dictionary = new Dictionary<string, string>();
            _color = new List<string> { "Red", "Yellow", "Blue", "Pink", "White", "Green", "Gold" };
            _fileName = "grid_data.xml";
            _dt = new DataTable();
        }

        private void _initDataTable()
        {
            if (System.IO.File.Exists(_fileName)) _dt = _openXML();
            else
            {
                _dt.TableName = "DataTable";
                _dt.Columns.Add("UID", typeof(string));
                _dt.Columns.Add("Chat", typeof(string));
            }

            _gridViewChatHistory.CustomDrawCell += _gridViewChatHistory_CustomDrawCell;
            _gridControlChatHistory.DataSource = _dt;

            for (int i = 0; i != _gridViewChatHistory.DataRowCount; ++i)
                _addUID(_getCellValue(i));
        }

        private void _initServer()
        {
            try
            {
                _ipe = new IPEndPoint(IPAddress.Parse("127.0.0.1"), 8080);
                _server = new UdpClient(_ipe);
                Debug.Print("UDP 서버 실행 중...\n");
            }
            catch (Exception e)
            {
                Debug.Print(e.ToString());
            }
        }

        private async Task _receiveData()
        {
            while (true)
            {
                DataRow insertData = _dt.NewRow();
                var receiveResult = await _server.ReceiveAsync();
                string UID = _getBuffer(receiveResult);
                insertData["UID"] = UID;
                receiveResult = await _server.ReceiveAsync();
                insertData["Chat"] = _getBuffer(receiveResult);
                _dt.Rows.Add(insertData);
                _addUID(UID);
            }
        }

        private DataTable _openXML()
        {
            DataSet xmlDataSet = new DataSet();
            xmlDataSet.ReadXml(_fileName);
            return xmlDataSet.Tables[0];
        }

        private void _btnSave_Click(object sender, EventArgs e)
        {
            System.IO.FileStream stream = new System.IO.FileStream(_fileName, System.IO.FileMode.Create);

            System.Xml.XmlTextWriter xmlWriter = new System.Xml.XmlTextWriter(stream, System.Text.Encoding.Unicode);
            _dt.WriteXml(xmlWriter);
            xmlWriter.Close();
        }

        private void _gridViewChatHistory_CustomDrawCell(object sender, DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventArgs e)
        {
            DataRow row = _gridViewChatHistory.GetDataRow(e.RowHandle);

            if (e.Column.FieldName == "UID")
                _paintColor(e);
        }

        private void _addUID(string UID)
        {
            if (!_dictionary.ContainsKey(UID))
                _dictionary[UID] = _color[_getColor()];
        }

        private void _paintColor(DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventArgs e)
        {
            if (_dictionary[e.CellValue.ToString()] == "Red")
                e.Appearance.BackColor = Color.Red;
            else if (_dictionary[e.CellValue.ToString()] == "Yellow")
                e.Appearance.BackColor = Color.Yellow;
            else if (_dictionary[e.CellValue.ToString()] == "Blue")
                e.Appearance.BackColor = Color.Blue;
            else if (_dictionary[e.CellValue.ToString()] == "Pink")
                e.Appearance.BackColor = Color.Pink;
            else if (_dictionary[e.CellValue.ToString()] == "White")
                e.Appearance.BackColor = Color.White;
            else if (_dictionary[e.CellValue.ToString()] == "Green")
                e.Appearance.BackColor = Color.Green;
            else if (_dictionary[e.CellValue.ToString()] == "Gold")
                e.Appearance.BackColor = Color.Gold;
        }

        private string _getBuffer(UdpReceiveResult receiveResult)
        {
            return Encoding.Default.GetString(receiveResult.Buffer);
        }

        private string _getCellValue(int i)
        {
            return _gridViewChatHistory.GetRowCellValue(i, "UID").ToString();
        }

        private int _getColor()
        {
            return _dictionary.Count % _color.Count;
        }
    }
}
