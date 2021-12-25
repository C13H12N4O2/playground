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

namespace Stock_Price_Viewer_Beta
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            WebClient wc = new WebClient();
            string path = "https://m.stock.naver.com/sise/siseList.nhn?menu=market_sum&sosok=0";
            byte[] data = wc.DownloadData(path.Trim());
            string str = System.Text.Encoding.UTF8.GetString(data);
            label1.Text = str;
            DataTable dt = new DataTable();
            dt.Columns.Add("Test1", typeof(string));
            DataRow insertData = dt.NewRow();
            insertData = dt.NewRow();
            insertData["Test1"] = str;
            dt.Rows.Add(insertData);
            /*
            foreach (var item in str.Split(' '))
            {
                insertData = dt.NewRow();
                insertData["Test1"] = item;
                dt.Rows.Add(insertData);
            }
             */
        }
    }
}
