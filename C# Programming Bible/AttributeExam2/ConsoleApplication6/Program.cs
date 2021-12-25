using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication6
{
    class AttributeExam2
    {
        [Obsolete("OldMethod는 NewMethod로 대체되었습니다.!!!")]
        public void OldMethod(){
            Console.WriteLine("이전 방식으로 구현됨!!!");
        }
        public void NewMethod()
        {
            Console.WriteLine("새로운 방식으로 구현됨!!!");
        }

        static void Main(string[] args)
        {
            AttributeExam2 obj = new AttributeExam2();
            obj.OldMethod();
            obj.NewMethod();

            while (true) { }
        }
    }
}
