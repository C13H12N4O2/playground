using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication7
{
    public partial class Form1 : Form
    {
        private interface data { }
        private class dataList : data
        {
            private string Name;
            private int Price;
            private int Quantity;
        }
        private List<data> _stockData = new List<data>();
        DataTable dt = new DataTable();
        public Form1()
        {
            InitializeComponent();

            dt.Columns.Add("Name", typeof(string));
            dt.Columns.Add("Price", typeof(long));
            dt.Columns.Add("Quantity", typeof(long));

            gridControl1.DataSource = dt;
            gridView1.CustomDrawCell += gridView1_CustomDrawCell;

            string[] lines = System.IO.File.ReadAllLines(@"C:\Users\imeco\Desktop\Test\WindowsFormsApplication7\WindowsFormsApplication7\data_2021_02_24.txt");
            string[] data;

            DataRow insertData = dt.NewRow();
            foreach (string item in lines)
            {
                insertData = dt.NewRow();
                data = item.Split(' ');
                insertData["Name"] = data[0];
                insertData["Price"] = long.Parse(data[1]);
                insertData["Quantity"] = long.Parse(data[2]);
                dt.Rows.Add(insertData);
            }
        }

        void gridView1_CustomDrawCell(object sender, DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventArgs e)
        {
            DataRow row = gridView1.GetDataRow(e.RowHandle);

            if (e.RowHandle % 2 == 0)
                e.Appearance.BackColor = Color.Yellow;
        }
    }
}
