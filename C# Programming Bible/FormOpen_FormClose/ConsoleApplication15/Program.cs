using System;
using System.Windows.Forms;

namespace ConsoleApplication15
{
    class NewWinForm : Form
    {
        public NewWinForm(string strText)
        {
            this.Text = strText;
            this.Load += new System.EventHandler(this.Form_Load);
            this.FormClosed += new FormClosedEventHandler(this.Form_Closed);
            this.Show();
        }
        private void Form_Load(object sender, System.EventArgs e)
        {
            Console.WriteLine("Loads windows");
        }
        private void Form_Closed(object sender, FormClosedEventArgs e)
        {
            Console.WriteLine("Closes windows");
        }
        static void Main(string[] args)
        {
            Application.Run(new NewWinForm("Add an event"));

            while (true) { }
        }
    }
}
