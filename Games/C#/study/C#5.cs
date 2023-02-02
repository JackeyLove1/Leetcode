[System.AttributeUsage(System.AttributeTargets.Class | System.AttributeTargets.Struct)]
public class AuthorAttribute : System.Attribute
{
    public string name { get; set; }
    public double version { get; set; }

    public AuthorAttribute(string name)
    {
        this.name = name;
        version = 1.0;
    }
}

[Author("Jacky", version = 1.1)]
class FirstClass{}

class Sample
{
    static void Main()
    {
        var ls = new List<string>();
        const int N = 5;
        for (var i = 0; i < N; i++)
        {
            ls.Add(i.ToString());
        }

        foreach (var s in ls)
        {   
            Console.WriteLine($"{s} ");
        }

        Dictionary<string, int> dic = new Dictionary<string, int>();
        dic.Add("one", 1);
        dic.Add("two", 2);
        foreach (var kv in dic)
        {
            Console.WriteLine($"{kv.Key}:{kv.Value}");
        }
    }
}