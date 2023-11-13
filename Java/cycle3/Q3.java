//Write a Java program that displays the number of characters, lines and words in a text
//file.
import java.io.*;
public class Q3
{
    public static void main(String[] args)
    {
        try(BufferedReader reader = new BufferedReader(new FileReader("File2.txt")))
        {
            String data;
            int countline =0;int countwords=0;int countchar = 0;
            while((data = reader.readLine()) != null)
            {
                countline++;
                countchar += data.length();
                String[] words = data.split("\\s+");
                countwords += words.length;
            }
            System.out.println("Character Count :" + countchar);
            System.out.println("Word Count :" + countwords);
            System.out.println("Line Count :" + countline);
        }
        catch(FileNotFoundException e)
        {
            System.out.println("File Not found error!");
            e.printStackTrace();
        }
        catch(IOException e)
        {
            System.out.println("File not read properly!");
            e.printStackTrace();
        }
    }
}