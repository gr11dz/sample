using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OOP_implementation
{
    internal class NumberGuess
    {
        int randint;
        double score;
        //public int Max { get; set; }
        //public int Min { get; set; }
        public string Username { get; set; }


        public void GenerateRand(int minValue, int maxValue)
        {
            //Min = 0;
            //Max = 100

            Random rand = new Random();
            randint = rand.Next(minValue, maxValue + 1);
        }

        public void CalcScore(bool checkWin, int failed_attempts)
        {
            score = 0;

            if (checkWin)
            {
                score += 50;
            }

            score -= failed_attempts * 10;
            score += 100 - 0; //Max - Min

        }

        public void StartGame()
        {
            Console.WriteLine($"{'-' * 5} Welcome {Username} {'-' * 5}");
            Console.WriteLine($"{'-' * 5} Number Guessing Game {'-' * 5}");

            int guessed;
            int failed_attempts = 0;
            bool checkWin = false;
            GenerateRand(0, 100);

            Console.WriteLine("Press Enter to Play....");
            Console.ReadLine();
            Console.Clear();

            while (!checkWin)
            {
                Console.WriteLine("Guess a Number : ");
                guessed = Convert.ToInt32(Console.ReadLine());
                Console.Clear();

                if (guessed == randint)
                {
                    Console.WriteLine("You've Won!");
                    checkWin = true;
                    break;
                }else if(guessed > randint)
                {
                    Console.WriteLine("You need to guess lower!");
                    failed_attempts++;
                }
                else
                {
                    Console.WriteLine("You need to guess higher!");
                    failed_attempts++;
                }
                
                if (failed_attempts >= 3)
                {
                    Console.WriteLine("You have ran out of lives!");
                    break;
                }

                Console.WriteLine("Press Enter to Continue...");
                Console.ReadLine();
                Console.Clear();
            }

            CalcScore(checkWin, failed_attempts);

            Console.WriteLine($"Your Score : {score}");

        }

    }
}
