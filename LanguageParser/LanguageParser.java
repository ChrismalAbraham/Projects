import java.util.Scanner;
import java.util.Arrays;

public class ExpEvaluator{
    private String s;
    private int currIndex;
    private int n; //size of string
    private char inputToken;
    
    
    public ExpEvaluator(String s){
        this.s = s;
        currIndex = 0;
        n = s.length();
        nextToken();
    }
    
    void nextToken(){
        
        char c;
        do {
            if (currIndex == n)
                {
                //throw new RuntimeException("out of bound");
                inputToken = '$';//means end of string
                return ;
                }
            c = s.charAt(currIndex++);
            //System.out.println("char:" + c);
            } 
        while (Character.isWhitespace(c));
        
        inputToken = c;
        
    }
    
    int checknextToken(){
        
        char c;
        do {
            if (currIndex == n)
                {
                //throw new RuntimeException("out of bound");
                inputToken = '$';//means end of string
                return 0;
                }
            c = s.charAt(currIndex++);
            System.out.println("char:" + c);
            } 
        while (Character.isWhitespace(c));
        
        inputToken = c;
        return c;
        
    }
    
    void match(char token){
        if (inputToken == token)
        {
            nextToken();
        }
        else 
        {
            throw new RuntimeException("Syntax Error Detected");
        }
    }
    
    int eval(){
        int x = exp();
        if (inputToken == '$')
        {
            return x;
        }
        else
        {
            throw new RuntimeException("Syntax Error Detected");
        }
    }
    
    int exp(){
        int x = term();
        while (inputToken == '+' || inputToken == '-')
        {
            char op = inputToken;
            nextToken();
            int y = term();
            x = apply(op, x, y); //apply the operator on the 2 operands
        }
        return x;
    }
    
    int term(){
        int x = factor();
        while (inputToken == '*' || inputToken == '/')
        {
            char op = inputToken;
            nextToken();
            int y = factor();
            x = apply(op, x ,y);
        }
        return x;
    }
    
    int factor(){
        int x;
        switch (inputToken)
        {
            case '=':
                nextToken();
                x = exp();
                match(';');
                return x;
            case '(':
                nextToken();
                x = exp();
                match(')');
                return x;
            case '0':
                x = 0;
                
                
            case '1':
                x = 1;
                
            case '2':
                x = 2;
                
            case '3':
                x = 3;
                
            case '4':
                x = 4;
                
            case '5':
                x = 5;
                
            case '6':
                x = 6;
                
            case '7':
                x = 7;
                
            case '8':
                x = 8;
                
            case '9':
                x = 9;
                
            x = inputToken - '0';
            nextToken();
            return x;
            default:
                throw new RuntimeException("Syntax Error Detected");
        }
        
    }
    
    static int apply(char op, int x, int y){
        int z = 0;
        switch (op)
        {
            case '+':
                z = x + y; 
                break;
            case '-':
                z = x - y;
                break;
            case '*':
                z = x * y;
                break;
            case '/':
                z = x / y;
                break;
        }
        return z;
    } 
    
     public static void main(String []args){
        for ( int i = 0; i < 10; i++)
        {
            Scanner readString = new Scanner(System.in);  
            System.out.println("Enter Expresion in the form char = expresion; char = expresion; ");
            String expresion = readString.nextLine();  
            int stringlen = expresion.length();
            
            
            int[] teststring = new int[10];
            char counter = ';';
            char counter2 = '=';
            int t = 0;
            int e = 0;
            
            for (int b = 0; b < stringlen; b++)
            {
                if (expresion.charAt(b) == counter)
                {
                    teststring[t] = b;
                    t++;
                }
                
            }
            for (int b = 0; b < stringlen; b++)
            {
                if (expresion.charAt(b) == counter2)
                {
                    e++;
                }
                
            }
            //System.out.println(Arrays.toString(teststring));
            
            if (t > e)
            {
                throw new RuntimeException("Syntax Error Detected: Missing equal sign or uninitialized variable");
            }
            if (e > t)
            {
                throw new RuntimeException("Syntax Error Detected: Missing  semicolon");
            }
            System.out.println("Your Expresion was: " + expresion);  
            if (t == 0)
            {
                throw new RuntimeException("Syntax Error Detected: Missing semicolon");
            }
            if (t >= 1)
            {
                ExpEvaluator e1 = new ExpEvaluator(expresion.substring(1, (teststring[0] + 1)));
                System.out.println(expresion.substring(0,1) + " = " + e1.exp());
            }
            if (t >= 2)
            {
                ExpEvaluator e2 = new ExpEvaluator(expresion.substring((teststring[0] + 3),(teststring[1] + 1)));
                System.out.println(expresion.substring((teststring[0] + 2), (teststring[0] + 3)) + " = " + e2.exp());
            }
            if (t >= 3)
            {
                
                ExpEvaluator e3 = new ExpEvaluator(expresion.substring((teststring[1] + 3), (teststring[2] + 1)));
                System.out.println(expresion.substring((teststring[1] + 2), (teststring[1] + 3)) + " = " + e3.exp());
            }
            if (t >= 4)
            {
                ExpEvaluator e3 = new ExpEvaluator(expresion.substring((teststring[1] + 3), (teststring[2] + 1)));
                System.out.println(expresion.substring((teststring[2] + 2), (teststring[2] + 3)) + " = " + e3.exp());
            }
            if (t == 5)
            {
                ExpEvaluator e3 = new ExpEvaluator(expresion.substring((teststring[1] + 3), (teststring[2] + 1)));
                System.out.println(expresion.substring((teststring[3] + 2), (teststring[3] + 3)) + " = " + e3.exp());
            }
        }
     }
}