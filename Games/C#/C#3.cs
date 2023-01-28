using System;
using System.Text;
using System.Collections;
using System.Numerics;

StringBuilder builder = new();
builder.Append("Hello");
builder.Append(", World!");
Console.WriteLine(builder.ToString());

Console.Write("Hello ");
await Task.Delay(500);
Console.WriteLine("World!");

public class Person
{
    public string Name { get; set; }
    public int Age { get; set; }
    
    public Person(string name, int age)
    {
        Name = name;
        Age = age;
    }

    public override string ToString()
    {
        return base.ToString();
    }
}

public class Programs
{
    public static void Main()
    {
        Person p = new Person("name", 123);
        Console.WriteLine(p);
    }
}