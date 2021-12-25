using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace File_Search_Program
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Search_View.Clear();
            Search_View.View = View.Details;
            Search_View.LabelEdit = false;
            Search_View.CheckBoxes = true;
            Search_View.FullRowSelect = true;
            Search_View.GridLines = true;
            Search_View.Sorting = SortOrder.Ascending;
            Search_View.Columns.Add("파일명", 170, HorizontalAlignment.Left);
            Search_View.Columns.Add("파일크기", 80, HorizontalAlignment.Right);
            Search_View.Columns.Add("생성일자", 150, HorizontalAlignment.Left);
        }

        private void Search_Bar_Button_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog dir = new FolderBrowserDialog();

            if (dir.ShowDialog() == DialogResult.OK)
            {
                this.Search_Bar.Text = dir.SelectedPath.Trim();
            }
        }

        private void Search_Button_Click(object sender, EventArgs e)
        {
            if (File_Name_Format_Bar.Text != " ")
            {
                Search_View.Items.Clear();
                Findfile(File_Name_Format_Bar.Text);
            }
        }

        private void Search_Directory_Click(object sender, EventArgs e)
        {
            //
        }

        void Findfile(string str)
        {
            string dir = Search_Bar.Text.Trim();
            if (dir == "")
            {
                MessageBox.Show("검색 디렉토리를 입력하세요.!");
                return;
            }

            string[] files_list;
            try
            {
                files_list = Directory.GetFiles(dir, str);
                foreach (var i in files_list)
                {
                    ListViewItem item1 = new ListViewItem(i);
                    FileInfo finfo = new FileInfo(files_list[i]);
                    item1.SubItems.Add(finfo.Length.ToString() + " Byte");
                    item1.SubItems.Add(finfo.CreationTime.ToString());
                    Search_View.Items.Add(item1);
                }
            }
            catch
            {
                MessageBox.Show("파일 검색 중 예외가 발생했습니다.");
            }
        }

    }
}
