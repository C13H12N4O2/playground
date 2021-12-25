using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace WindowsFormsApplication2
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void btnClickThis_Click(object sender, EventArgs e)
        {
            lblHelloWorld.Text = "Hello World!";
            chk_ex.Text = check_example();

            Arithmetic obj = new Arithmetic();
            ArithmeticDelegate ex1 = new ArithmeticDelegate(obj.Add);
            delegate_example.Text = ex1(10, 20).ToString();

            EventExam1 obj2 = new EventExam1();
            obj2.ClickMethod(10);
        }

        private string check_example()
        {
            int data1 = 99999;
            short data2 = (short)data1;

            return "data1 = " + data1;
        }
    }
}

class Arithmetic
{
    public int Add(int a, int b) { return a + b; }
    public int Sub(int a, int b) { return a - b; }
    public int Mul(int a, int b) { return a * b; }
    public int Div(int a, int b)
    {
        if ((a == 0) || (b == 0))
            return 0;
        return a / b;
    }
}

public delegate int ArithmeticDelegate(int a, int b);

class MyEventArgs : EventArgs
{
    private int ClickCount;
    public MyEventArgs()
    {
        this.ClickCount = 0;
    }

    public MyEventArgs(int data)
    {
        this.ClickCount = data;
    }

    public int GetClickCount()
    {
        return this.ClickCount;
    }
}

class ExampleClass
{
    public void OnClick(object sender, MyEventArgs args)
    {
        Console.WriteLine("{0} 개체에서 {1}번 이벤트가 발생했습니다.",
            sender.ToString(), args.GetClickCount());
    }
}

class EventExam1
{
    public delegate void ClickEvent(object sender, MyEventArgs args);
    private event ClickEvent ExamEvent;

    public EventExam1()
    {
        ExampleClass obj = new ExampleClass();
        ExamEvent += new ClickEvent(obj.OnClick);
    }

    public void ClickMethod(int clickcount)
    {
        if (ExamEvent != null)
        {
            MyEventArgs args = new MyEventArgs(10);
            ExamEvent(this, args);
        }
    }
}