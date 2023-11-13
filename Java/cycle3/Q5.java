/*Write a Java program that reads a line of integers, and then displays each integer, and the
sum of all the integers (Use String Tokenizer class of java.util). */
import java.util.StringTokenizer;
import java.util.Scanner;
public class Q5{
    public static void main(String[] args)
    {
        System.out.println("Enter a line of integers seperated by whitespace : ");
        Scanner s = new Scanner(System.in);
        String str = s.nextLine();
        StringTokenizer tokenizer = new StringTokenizer(str);
        s.close();
        int sum = 0;
        while(tokenizer.hasMoreTokens())
        {
            String token = tokenizer.nextToken();
            int number = Integer.parseInt(token);
            System.out.println("Number : " + number); 
            sum += number;
        }
        System.out.println("Sum : " + sum);

    }
}