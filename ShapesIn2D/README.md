# The task is to develop a program that compares the areas and perimeters of two given shapes.

There are given two planar shapes in the input. A shape may be any of:
- triangle - the input consists of letter T followed by three decimal numbers (sides),
- rectangle - the input consists of letter R followed by two decimal numbers (sides), or
- square - the input consists of letter S followed by one decimal number (side).

The program computes the area and the perimeter of both input shapes and compares them. The result of the comparison is then printed to the standard output, the format is clear from the example runs below.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:
- the input shape is invalid (only Triangle/Rectangle/Square is valid),
- there was not enough decimal numbers to describe the dimensions of the input shape,
- a dimension is invalid, is not well-formatted, is negative, or zero,
- the three decimal numbers do not form a valid triangle (triangle inequality),
- both sides of a rectangle are the same (i.e., the shape is indeed a square).

### Sample program runs:
```
Obrazec #1
S 4.5
Obrazec #2
R 2 10.125
Obvod: ctverec #1 < obdelnik #2
Obsah: ctverec #1 = obdelnik #2

Obrazec #1
R 4 5
Obrazec #2
T 4.5 6 7.5
Obvod: obdelnik #1 = trojuhelnik #2
Obsah: obdelnik #1 > trojuhelnik #2

Obrazec #1

   T
 1
 1
 1
Obrazec #2
 S
 2
Obvod: trojuhelnik #1 < ctverec #2
Obsah: trojuhelnik #1 < ctverec #2

Obrazec #1
T 7.981 8.899 2.996
Obrazec #2
R 2.959 6.979
Obvod: trojuhelnik #1 = obdelnik #2
Obsah: trojuhelnik #1 < obdelnik #2

Obrazec #1
R 6.474 0.559
Obrazec #2
T 0.507 14.276 14.285
Obvod: obdelnik #1 < trojuhelnik #2
Obsah: obdelnik #1 = trojuhelnik #2

Obrazec #1
T 20 30 50
Nespravny vstup.

Obrazec #1
S -4
Nespravny vstup.

Obrazec #1
R 20 30
Obrazec #2
T 0.444 0.521 0.965
Nespravny vstup.

Obrazec #1
R 12 12
Nespravny vstup.

Obrazec #1
R 1 abcd
Nespravny vstup.
```

### Advice:
- The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
- Do not forget the newline (\n) after the last output line.
- Use double data type to represent the values. Do not use float, the precision of float is not always sufficient.
- The program can be developed without additional functions (i.e., in one big main). However, if divided into functions, the program is readable and easier to debug.
- All numeric values in the input fit into the range of double data type. The reference uses double and int data types to represent numbers.
- Please strictly adhere to the format of the output. The output must exactly match the output of the reference program. The comparison is completed by a machine, meaning an exact match is required. If your program provides output different from the reference, the program is considered malfunctioning. Be very careful since the comparison is sensitive even to whitespace characters (spaces, newlines, tabulators). Please note that all output lines are followed by a newline character (\n). The new line character must be present after the last line of the output and after the error messages. Download the enclosed archive. The archive contains a set of testing inputs and the expected outputs. Read Progtest FAQ to learn how to use input/output redirection and how to simplify testing of your programs.
- Use Heron's formula to compute the area of triangle.
- Your program will be tested in a restricted environment. The testing environment limits running time and available memory. The exact time and memory limits are shown in the reference solution testing log. However, neither time nor memory limit could cause a problem in this simple program. Next, the testing environment prohibits the use of functions which are considered "dangerous" (functions to execute other processes, functions to access the network, ... ). If your program uses such functions, the testing environment refuses to execute the program. Your program may use something like the code below:

```
int main ( int argc, char * argv [] )
{
  ...
  system ( "pause" ); /* prevent program window from closing */
  return 0; 
}
```

This will not work properly in the testing environment - it is prohibited to execute other programs. (Even if the function were allowed, this would not work properly. The program would infinitely wait for a key to be pressed, however, no one will press any key in the automated testing environment. Thus, the program would be terminated on exceeded time limit.) If you want to keep the pause for your debugging and you want the program to be accepted by the Progtest, use the following trick:

```
int main ( int argc, char * argv [] )
{
   ...
   #ifndef __PROGTEST__
     system ( "pause" ); /* this is ignored by Progtest */
   #endif /* __PROGTEST__ */
     return 0; 
}
```

