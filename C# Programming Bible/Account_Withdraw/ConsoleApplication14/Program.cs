using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace ConsoleApplication14
{
    class Account
    {
        int money;
        Random rnd = new Random();

        public Account(int money)
        {
            this.money = money;
        }
        int Deposit(int amount)
        {
            lock (this)
            {
                Console.WriteLine("*** {0}님이 {1}원을 입금하려 합니다.",
                    Thread.CurrentThread.Name, amount);
                Console.WriteLine("입금전 예금 잔액 : \\ " + this.money);
                Console.WriteLine("입금 금액       : \\ " + amount);
                this.money += amount;
                Console.WriteLine("입금 후 예금 잔액: \\ " + this.money + "\n");
            }

            return amount;
        }
        int Widthraw(int amount)
        {
            if (this.money < 0)
            {
                throw new Exception("인출 가능한 잔액이 없습니다.");
            }

            lock (this)
            {
                if (this.money >= amount)
                {
                    Console.WriteLine("*** {0}님이 {1}원을 인출하려 합니다.",
                        Thread.CurrentThread.Name, amount);
                    Console.WriteLine("인출 전 예금 잔액: \\ " + this.money);
                    Console.WriteLine("인출 금액       : \\ " + amount);
                    this.money -= amount;
                    Console.WriteLine("인출 후 예금 잔액: \\ " + this.money + "\n");

                    return amount;
                }
                else
                {
                    return 0;
                }
            }
        }
        public void Trans()
        {
            int money;
            for (int i = 0; i != 10; ++i)
            {
                money = rnd.Next(-3000, 3000);
                if (money > 0)
                {
                    if (this.Widthraw(money) == 0)
                    {
                        Console.WriteLine("## Err : 인출 금액이 계좌 잔액보다 많습니다.");
                    }
                }
                else
                {
                    this.Deposit(money * -1);
                }
            }
        }
    }

    class ThreadExam7
    {
        public static void Main()
        {
            Thread[] th = new Thread[3];
            Account obj = new Account(10000);
            for (int i = 0; i != 3; ++i)
            {
                th[i] = new Thread(new ThreadStart(obj.Trans));
                th[i].Name = "고객[" + i + "]";
            }
            for (int i = 0; i != 3; ++i)
            {
                th[i].Start();
            }

            while (true) { }
        }
    }
}
