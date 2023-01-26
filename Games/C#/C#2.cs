using System;

public class Pair<TFirst, TSecond>
{
    public TFirst First { get; }
    public TSecond Second { get; }
}

interface IControl
{
    void Paint();
}

interface ITextBox : IControl
{
    void SetText(string text);
}

interface IListBox : IControl
{
    void SetItems(string[] items);
}

public enum SomeRootVegetable
{
    HorseRadish,
    Radish,
    Turnip,
}

public class Color
{
    public static readonly Color Black = new Color(0, 0, 0);
    public static readonly Color White = new(255, 255, 255);
    public byte R, G, B;
    public Color(byte r, byte g, byte b)
    {
        R = r;
        G = g;
        B = b;
    }
}

public class Study
{
    static void Divide(int x, int y, out int quo, out int remainder)
    {
        quo = x / y;
        remainder = x % y;
    }

    static void Swap(ref int x, ref int y)
    {
        (x, y) = (y, x);
    }

    static void F() => Console.WriteLine("F()");
    static void F(int x) => Console.WriteLine("F(int x)");
    static void F(object x) => Console.WriteLine("F(object x)");
    static void F<T>(T x) => Console.WriteLine("F<T>(T x)");

    class Multiplier
    {
        private double _factor;
        public Multiplier(double factor) => _factor = factor;
        public double Multiply(double x) => x * _factor;
    }

    public delegate double Function(double x);
    static double[] Apply(double[] arr, Function f)
    {
        var result = new double[arr.Length];
        for (int i = 0; i < arr.Length; i++)
        {
            result[i] = f(arr[i]);
        }

        return result;
    }
    
    static async Task<int> RetrieveDocsHomePage()
    {
        const int sleepTime = 300;
        var func = (int num) =>
        {
            Thread.Sleep(sleepTime);
            return num;
        };
        int content = func(1);
        // Console.WriteLine($"{nameof(RetrieveDocsHomePage)}: Finished downloading.");
        return content;
    }
    
    public static void Main(string[] args)
    {
        Divide(10 , 3, out int quo, out int rem);
        Console.WriteLine("{0} {1}", quo, rem);
        int x = 0, y = 1;
        Swap(ref x, ref y);
        Console.WriteLine("x:{0}, y:{1}", x, y);
        
        F();
        F(1);
        F((double)1);
        F<double>(1);

        int[] a1 = new int[3];
        for (int i = 0; i < a1.Length; i++)
        {
            a1[i] = i * i;
        }

        for (int i = 0; i < a1.Length; i++)
        {
            Console.WriteLine($"a1[{i}] = {a1[i]}");
        }

        int[] a2 = new int[] { 1, 2, 3 };
        foreach (var item in a2)
        {
            Console.WriteLine($"item = {item}");
        }

        double[] a3 = { 0.0, 0.5, 1.0 };
        double[] squares = Apply(a3, (x) => x * x);
        var m = new Multiplier(2.0);
        double[] doubles = Apply(a3, m.Multiply);
        foreach (var VARIABLE in squares)
        {
            Console.Write("{0} ", VARIABLE);
        }
        Console.WriteLine();
        foreach (var VARIABLE in doubles)
        {
            Console.Write("{0} ", VARIABLE);
        }
        Console.WriteLine();

        var l = RetrieveDocsHomePage().Result;
        Console.WriteLine("get length:{0}", l);
        
        
        }
}

