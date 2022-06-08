// Online C# Editor for free
// Write, Edit and Run your C# code using C# Online Compiler

using System;
using System.Collections.Generic;

public class HelloWorld
{
    public static int recursive(int n)
    {
        switch (n)
        {
            case 0:
                return 1;
            case < 0:
                Console.WriteLine("Wrong input");
                return -1;
            default:
                return n * recursive(n - 1);
        }
    }

    public static void Main(string[] args)
    {
        Console.WriteLine(recursive(4));
        Console.ReadKey();
    }
}