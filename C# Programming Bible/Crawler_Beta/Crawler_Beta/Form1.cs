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
using System.IO;
using System.Text.RegularExpressions;

namespace Crawler_Beta
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            _labelDirectory.Text = _isDirectoryEmpty();
        }

        private void _crawling()
        {
            WebClient wc = new WebClient();
            byte[] data = wc.DownloadData(_textBoxIllustID.Text.Trim());
            string str = System.Text.Encoding.UTF8.GetString(data);
            wc.DownloadFile(_textBoxIllustID.Text.Trim(), "test.txt");

            var parts = Regex.Split(str, @"<div>[\s\S]+?<\/div>").Where(l => l != string.Empty).ToArray();
            foreach (var item in parts)
                _listViewImg.Items.Add(item);
        }

        private String _isDirectoryEmpty()
        {
            if (_folderBrowserDialog.SelectedPath == "")
            {
                _folderBrowserDialog.SelectedPath = @"C:\";
                return _folderBrowserDialog.SelectedPath;
            }
            return _folderBrowserDialog.SelectedPath;
        }

        private void _btnSelectFolder_Click(object sender, EventArgs e)
        {
            _folderBrowserDialog.ShowDialog();
            _labelDirectory.Text = _isDirectoryEmpty();
        }

        private void _downloadImg_Click(object sender, EventArgs e)
        {
            _crawling();
        }
    }
}
