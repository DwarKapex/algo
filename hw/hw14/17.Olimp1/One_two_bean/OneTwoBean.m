using System;

class VideoSharp
{
    static int GCD(int a, int b) {
        while (a > 0 && b > 0) {
        if (a > b)
            a %= b;
        else
            b %= a;
        }
        return a+b;
    }

    static void Main()
    {
        string[] line = Console.ReadLine().Split('+', '/');
        int a = int.Parse(line[0]);
        int b = int.Parse(line[1]);
        int c = int.Parse(line[2]);
        int d = int.Parse(line[3]);

        int x = a*d + b*c;
        int y = b*d;
        
        int gcd = GCD(x,y);

        Console.WriteLine(x/gcd,"/",y/gcd);
    }
}
