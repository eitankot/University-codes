/**
 * This code calculate the max and min of the heart rate.
 */
import java.util.Scanner;
public class HeartRate
{
    public static void main (String [] args)
    {
        final int CONST = 220;
        final int MAX_HEART_RATE = 85;
        final int MIN_HEART_RATE = 65;
        
        Scanner scan = new Scanner (System.in);
        System.out.println ("This program calculates your target heart rate while exercising ");
        System.out.print ("Enter your age: ");
        int age = scan.nextInt(); // scanner
        int heartRate = CONST - age;
        int highestHeartRate = (int)(heartRate*((double)(MAX_HEART_RATE)/100)); // calculate the highest by the percent of the heart rate.
        int lowestHeartRate = (int)(heartRate*((double)(MIN_HEART_RATE)/100)); // calculate the lowest by the percent of the heart rate.
        
        System.out.println("Your estimated target heart rate zone is " + lowestHeartRate + " – " + highestHeartRate + " beats per minute.");       

    } // end of method main
} //end of class HeartRate