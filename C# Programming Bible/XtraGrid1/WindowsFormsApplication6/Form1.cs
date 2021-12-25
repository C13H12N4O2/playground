using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication6
{
    public partial class Form1 : Form
    {

        DataTable dt = new DataTable();
        public Form1()
        {
            InitializeComponent();

            dt.Columns.Add("type1", typeof(string));
            dt.Columns.Add("type2", typeof(int));
            dt.Columns.Add("type3", typeof(int));

            gridControl1.DataSource = dt;

            gridView1.CustomDrawCell += gridView1_CustomDrawCell;
        }

        void gridView1_CustomDrawCell(object sender, DevExpress.XtraGrid.Views.Base.RowCellCustomDrawEventArgs e)
        {
            DataRow row = gridView1.GetDataRow(e.RowHandle);

            if (e.RowHandle % 2 == 0)
                e.Appearance.BackColor = Color.Yellow;
            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            DataRow row = dt.NewRow();
            row["type1"] = "test";
            row["type2"] = 1;
            row["type3"] = 1;


            dt.Rows.Add(row);
        }
    }
}
