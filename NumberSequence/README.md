# The task is to develop a program that analyzes a sequence of integers.

Assume a sequence of non-negative integers (0, 1, 2, ... ). The sequence starts with number zero, the numbers a re in an ascending order, and the numbers are adjacent to each other (no extra spaces or leading zeros). The beginning of the sequence is:

01234567891011121314151617181920...

The notation is not very readable for humans. To simplify further understanding, we colored the numbers like:

01234567891011121314151617181920...

The task of the program is to find the number and the particular digit in the given position in the sequence. For example:
- there is digit 0 of the number 0 in position 0, 
- there is digit 2 of number 12 in position 15,
- there is digit 1 of number 710 in position 2021, ...

To make the program universal, we consider the sequences where the numbers are in various bases. For example, if the base i s 2, the (colored) sequence may look like:

01101110010111011110001001...

For example, there is digit 0 of number 110 in position 14 for the binary sequence.

Your program will be given a list of problems to solve in its standard input. Each problem consists of two decimal integers: the first number determines the position in the sequence, the second number is the base. The program computes the digit/number for each such problem and displays the result; the format is shown below. The program terminates when there are no further problems in the input, i.e., when the EOF is reached.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The input is considered invalid, if:
- a position in the sequence is invalid (not an integer, negative position), 
- the base is invalid (not an integer, outside of closed interval [ 2 ; 36 ] ).

### Sample program runs:
```
Pozice a soustava:
0 10
0
^
3 10
3
^
9 10
9
^
10 10
10
^
11 10
10
 ^
12 10
11
^
13 10
11
 ^
189 10
99
 ^
190 10
100
^
191 10
100
 ^
192 10
100
  ^
193 10
101
^

Pozice a soustava:
42 10
26
^
666 10
258
  ^
1889 10
666
 ^
12345 10
3363
   ^
1000000 10
185185
^
1234321 10
224238
   ^
   
Pozice a soustava:
abc 10
Nespravny vstup.

Pozice a soustava:
12 37
Nespravny vstup.
```

### Advice:
- The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
- Do not forget the newline (\n) after the last output line.
- The program is tested with several tests where the program is tested for additional functions. A basic solution does not have to be extremely fast, moreover, the basic solution may ignore all bases except base 10 (for example, it may report an error if base is different from 10). Such a solution passes all mandatory tests and some optional tests. The result will be at most 75 %.
- An improved solution must handle the base parameter correctly. However, the solution does not have to be extremely fast (naive algorithm is still fine). Your program will be awarded nominal 100 % points if it passes the "various base" test (and all previous tests).
- Finally, there is a bonus speed test. There are big numbers in the input (sequence position is very high). The program does not have enough time to iterate over all intermediate numbers in the sequence. Instead, your program must use some smart algorithm that skips over some/all the intermediate numbers. If passed, the program is awarded more than the nominal 100 % points.
- The basic solution may use int data type to represent the values. However, the bonus test inputs big values that exceed the range of int. You need to use long or long long to pass the bonus test.
- Use lowercase letters to display digits in bases over 10. For example, ff is a valid result for 255 in base 16.
- Do not generate/store the sequence 01234567891011... into a big string/array. It would be laborious, it would require a lot of memory, it would be slow, and it would require nontrivial programming. But most importantly, it is not needed. It may be a good idea to generate the intermediate numbers (e.g., in a for-loop), however, do not store them. In fact, you even do not need to convert the individual intermediate numbers into string.
