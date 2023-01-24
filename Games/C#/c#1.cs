using System;
using System.Collections;

enum Days
{
    Sun,
    Mon,
    Tue,
    Wed
};

namespace HelloWorldApplication
{
    public class Rectangle
    {
        public double length;
        public double width;

         public Rectangle()
        {
            Console.WriteLine("Construction");
        }

         ~Rectangle()
        {
            Console.WriteLine("Deconstrucition");
        }
        public double GetAreas()
        {
            return length * width;
        }

        public void setLength(double len)
        {
            length = len;
        }

        public void setWidth(double wid)
        {
            width = wid;
        }
        
        public double getLength()
        {
            return length;
        }

        public double getWidth()
        {
            return width;
        }
        
        public static Rectangle operator + (Rectangle lhs, Rectangle rhs)
        {
            Rectangle r = new Rectangle();
            r.length = lhs.length + rhs.length;
            r.width = lhs.width + rhs.width;
            return r;
        }

        public override string ToString()
        {
            return "length:" + length + " ,width:" + width;
        }
    }
    
    
    class Tester
    {
        public static void CallBack()
        {
            Console.WriteLine("Thread Starts");
            int sleepfor = 1000;
            Thread.Sleep(sleepfor);
            Console.WriteLine("Sleep for {0} seconds", sleepfor/1000);
            Console.WriteLine("Thread Ends");
        }
        static void Main(string[] args)
        {
            Console.WriteLine("Hello, World!");
            Console.WriteLine("print {0}", 1);

            for (;;)
            {
                Console.WriteLine("loop");
                break;
            }

            int[] arr = { 1, 2, 3, 4, 5 };
            for (int i = 0; i < arr.Length; i++)
            {
                Console.Write("{0} ", arr[i]);
            }
            Console.WriteLine();
            foreach (var VARIABLE in arr)
            {
                Console.Write("{0} ", VARIABLE);
            }

            Rectangle r1 = new Rectangle();
            r1.setLength(10);
            r1.setWidth(20);
            Console.WriteLine("Area:{0}", r1.GetAreas());
            Rectangle r2 = new Rectangle();
            r2.setLength(30);
            r2.setWidth(40);
            {
                Rectangle r3 = r1 + r2;
                Console.WriteLine("length:{0}, width:{1}", r3.getLength(), r3.getWidth());
                Console.WriteLine(r3.ToString());
            }
            var al = new ArrayList();
            for (int i = 0; i < 10; i++)
            {
                al.Add(i);
            }
            Console.WriteLine("al count:{0}", al.Count);
            foreach (var num in al)
            {
                Console.Write("{0} ", num);
            }
            al.Sort();
            
            var ht = new Hashtable();
            ht.Add("001", "Zara Ali");
            ht.Add("002", "Abida Rehman");
            ht.Add("003", "Joe Holzner");
            var keys = ht.Keys;
            foreach (var k in keys)
            {
                Console.WriteLine("{0}:{1}", k, ht[k]);
            }

            var q = new Queue();
            q.Enqueue('A');
            q.Enqueue('M');
            q.Enqueue('G');
            q.Enqueue('W');
            foreach (var ch in q)
            {
                Console.Write("{0} ", ch);
            }
            Console.WriteLine();
            var chs =q.Dequeue();
            Console.WriteLine("chs:{0}", chs);

            ThreadStart child = new ThreadStart(CallBack);
            Thread thread = new Thread(child);
            thread.Start();
            thread.Join();
        }
    }
}