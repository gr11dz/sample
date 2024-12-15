
using System;

class Programme
{
    static void Main(string[] args)
    {
        Random randint = new Random();

        int randnum;
        int min = 1;
        int max = 100;
        int failed_attempts = 0;
        bool game_win = false;
        randnum = randint.Next(min, max + 1);

        int guessed = 0;

        Console.WriteLine("-----------Number Guess-----------\n");
        while (!game_win)
        {
            Console.Clear();
            Console.Write("Guess A Number : ");
            guessed = Convert.ToInt32(Console.ReadLine());
            Console.Clear();

            if (guessed == randnum)
            {
                game_win = true;
                Console.WriteLine("You've Won!!");
                break;
            }else if (guessed > randnum)
            {
                failed_attempts++;
                Console.WriteLine("You need to guess Lower!");
            }
            else
            {
                failed_attempts++;
                Console.WriteLine("You need to guess Higher!");
            }
            
            if (failed_attempts >= 3)
            {
                Console.WriteLine("Too many Attempts!");
                break;
            }

            Console.WriteLine("Press Enter to Continue...");
            Console.ReadLine();
        }

    }
}
