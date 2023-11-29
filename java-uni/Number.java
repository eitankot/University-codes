
/**
 * This code takes a number from the user and does a selected operation on the number.
 */
import java.util.Scanner;
public class Number
{
    public static void main (String [] args)
    {
        final int SIGN = 1;
        final int REVERSE = 2;
        final int REVERSE_SIGN = 3;
        Scanner scan = new Scanner (System.in); // scanner
        int firstDigitNumber;
        int secondDigitNumber;
        int thirdDigitNumber;
        int fourthDigitNumber;
        System.out.println("This is number operation tool.");
        System.out.println("enter a 4 digit number: ");
        int number = scan.nextInt(); 
        
        final int MAX_POSITIVE_NUMBER = 9999 ;
        final int MAX_NEGATIVE_NUMBER = -9999;
        final int MIN_NEGATIVE_NUMBER = -1000;
        final int MIX_POSITIVE_NUMBER = 1000;
        if ((MIN_NEGATIVE_NUMBER < number && number < MIX_POSITIVE_NUMBER) || (number > MAX_POSITIVE_NUMBER || number < MAX_NEGATIVE_NUMBER)) // check if the number is Illegal
        {
            System.out.println("Illegal number – you must enter a 4 digit number");
        }
        else
        {
            System.out.println("1. Reverse sign. \n2. Reverse number. \n3. Reverse sign and number.\nPlease choose an option: ");
            int optionNumber = scan.nextInt();
            switch (optionNumber)
            {
                case SIGN:
                    number *= -1; // multiple by -1 to get reverse sign
                    System.out.println(number);
                    break;
                case REVERSE:
                    firstDigitNumber = number/1000; // gets the first number of the reverse
                    number = number%1000;
                    secondDigitNumber = number / 100; // gets the second number of the reverse
                    number = number%100;
                    thirdDigitNumber = number / 10; // gets the third number of the reverse
                    fourthDigitNumber = number%10; // gets the fourth number of the reverse
                    number = (fourthDigitNumber*1000 + thirdDigitNumber*100 + secondDigitNumber*10 + firstDigitNumber); // Gets the total number.
                    System.out.println("The result is: " + number);
                    break;
                case REVERSE_SIGN: 
                    firstDigitNumber = number/1000; // gets the first number of the reverse
                    number = number%1000;
                    secondDigitNumber = number / 100;// gets the second number of the reverse
                    number = number%100;
                    thirdDigitNumber = number / 10; // gets the third number of the reverse
                    fourthDigitNumber = number%10; // gets the fourth number of the reverse
                    number = (fourthDigitNumber*1000 + thirdDigitNumber*100 + secondDigitNumber*10 + firstDigitNumber);// Gets the total number.
                    number *= -1; // multiple by -1 to get reverse sign
                    System.out.println("The result is: " + number);
                    break;
                default:
                    System.out.println("Illegal option – you must choose 1, 2 or 3");
                    break;
            }
        }
    }// end of method main
} //end of class NumberOperation