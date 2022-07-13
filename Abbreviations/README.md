# The task is to develop a program to search for abbreviations in a text.

The program is given an abbreviation, e.g., FIT. The abbreviation consists of uppercase letters A to Z. Following the abbreviation, there are problems to search for it. The problems are of two forms:
```
? N "text"
```

or
```
# N "text"
```

The text in quotes may contain any number of arbitrary characters (except for newline and quote), N is an integer. The program tries to find the abbreviation in the text, i.e., find the letters from the abbreviation somewhere in the text:
- we do not distinguish upper/lower case letters in the search,
- the order of the letters in the text must match the order of the letters in the abbreviation, and 
- at most N letters may be used from each word in the text.

For the example abbreviation FIT and input problem: 
```
# 1 "Faculty of Information Technology"
```

The abbreviation may be chosen in the following ways:
```
"Faculty of Information Technology"
"faculty oF Information Technology"
"Faculty of informatIon Technology"
...
```

However, the following choices are invalid:
```
"faculTy oF Information technology"
"Faculty of InformaTion technology"
```

In the first case, the order of letters is not preserved. In the second case, there are 2 letters chosen from the word Information, however, the limit is at most N=1 letter from a word.

In general, there may exist many ways to find the abbreviation in the text. If the input problem has the form:
```
? N "text"
```

then the program searches for the abbreviation (using the rules above) and prints out all possible choices. The letters of the abbreviation are emphasized - printed in upper case - whereas the other letters are printed in lower case. Finally, there is a line with the total number of possible choices.
If the input problem has the form:
```
# N "text"
```

then the program finds and counts the possible choices. The choices are not printed out, instead, only the counts are displayed. Moreover, the counts are printed for each where at most 1, 2, 3, ... , N letters may be chosen from a word in the text.

The input is to be processed line-by-line. The first line contains the abbreviation to search for. The letters in the abbreviation must be upper case letters, there must not be any extra additional characters. There is not any explicit limit on the length of the abbreviation. Following the abbreviation, there are the problems to solve. Each problem is delivered on a separate line. The format of the problem is described above. The problems are read and processed until the program reaches EOF in the standard input.

The output is the input text with the emphasized letters of the abbreviation and the number of ways the abbreviation may be chosen. The output lines with the emphasized abbreviations may be printed in any arbitrary order. The exact formatting of the output is clear from the example runs.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The following is considered invalid:
- the first input line did not contain the abbreviation, was empty (zero length), or the abbreviation contained some other character in addition to upper case letters,
- the problem type was not recognized (# and ?),
- number N is missing, is invalid, zero, or negative,
- the text is missing, is not enclosed in quotes, or a quote is missing.

### Example program runs:
```
Zkratka:
FIT
Problemy:
? 1 "Faculty of Information Technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
> 4
? 2 "Faculty of Information Technology"
"Faculty of InformaTion technology"
"Faculty of Information Technology"
"Faculty of informatIon Technology"
"faculty oF InformaTion technology"
"faculty oF Information Technology"
"faculty oF informatIon Technology"
"faculty of inFormatIon Technology"
> 7
? 2 "FIT"
> 0
? 3 "FIT"
"FIT"
> 1
? 2   "Fibonacci   test"  
"FIbonacci   Test"
"FIbonacci   tesT"
"FibonaccI   Test"
"FibonaccI   tesT"
> 4
? 2   "  Fibonacci   test   "  
"  FIbonacci   Test   "
"  FIbonacci   tesT   "
"  FibonaccI   Test   "
"  FibonaccI   tesT   "
> 4
? 3 "Flux field inspection and particle affiliation department"
"Flux fIeld inspecTion and particle affiliation department"
"Flux fIeld inspection and parTicle affiliation department"
"Flux fIeld inspection and particle affiliaTion department"
"Flux fIeld inspection and particle affiliation deparTment"
"Flux fIeld inspection and particle affiliation departmenT"
"Flux field InspecTion and particle affiliation department"
"Flux field Inspection and parTicle affiliation department"
"Flux field Inspection and particle affiliaTion department"
"Flux field Inspection and particle affiliation deparTment"
"Flux field Inspection and particle affiliation departmenT"
"Flux field inspectIon and parTicle affiliation department"
"Flux field inspectIon and particle affiliaTion department"
"Flux field inspectIon and particle affiliation deparTment"
"Flux field inspectIon and particle affiliation departmenT"
"Flux field inspection and partIcle affiliaTion department"
"Flux field inspection and partIcle affiliation deparTment"
"Flux field inspection and partIcle affiliation departmenT"
"Flux field inspection and particle affIliaTion department"
"Flux field inspection and particle affIliation deparTment"
"Flux field inspection and particle affIliation departmenT"
"Flux field inspection and particle affilIaTion department"
"Flux field inspection and particle affilIation deparTment"
"Flux field inspection and particle affilIation departmenT"
"Flux field inspection and particle affiliatIon deparTment"
"Flux field inspection and particle affiliatIon departmenT"
"flux FIeld inspecTion and particle affiliation department"
"flux FIeld inspection and parTicle affiliation department"
"flux FIeld inspection and particle affiliaTion department"
"flux FIeld inspection and particle affiliation deparTment"
"flux FIeld inspection and particle affiliation departmenT"
"flux Field InspecTion and particle affiliation department"
"flux Field Inspection and parTicle affiliation department"
"flux Field Inspection and particle affiliaTion department"
"flux Field Inspection and particle affiliation deparTment"
"flux Field Inspection and particle affiliation departmenT"
"flux Field inspectIon and parTicle affiliation department"
"flux Field inspectIon and particle affiliaTion department"
"flux Field inspectIon and particle affiliation deparTment"
"flux Field inspectIon and particle affiliation departmenT"
"flux Field inspection and partIcle affiliaTion department"
"flux Field inspection and partIcle affiliation deparTment"
"flux Field inspection and partIcle affiliation departmenT"
"flux Field inspection and particle affIliaTion department"
"flux Field inspection and particle affIliation deparTment"
"flux Field inspection and particle affIliation departmenT"
"flux Field inspection and particle affilIaTion department"
"flux Field inspection and particle affilIation deparTment"
"flux Field inspection and particle affilIation departmenT"
"flux Field inspection and particle affiliatIon deparTment"
"flux Field inspection and particle affiliatIon departmenT"
"flux field inspection and particle aFfIliaTion department"
"flux field inspection and particle aFfIliation deparTment"
"flux field inspection and particle aFfIliation departmenT"
"flux field inspection and particle aFfilIaTion department"
"flux field inspection and particle aFfilIation deparTment"
"flux field inspection and particle aFfilIation departmenT"
"flux field inspection and particle aFfiliatIon deparTment"
"flux field inspection and particle aFfiliatIon departmenT"
"flux field inspection and particle afFIliaTion department"
"flux field inspection and particle afFIliation deparTment"
"flux field inspection and particle afFIliation departmenT"
"flux field inspection and particle afFilIaTion department"
"flux field inspection and particle afFilIation deparTment"
"flux field inspection and particle afFilIation departmenT"
"flux field inspection and particle afFiliatIon deparTment"
"flux field inspection and particle afFiliatIon departmenT"
> 66
# 4 "figure fits the first filter of floating firmware in the field width transistor to instance"
> limit 1: 238
> limit 2: 321
> limit 3: 324
> limit 4: 324
# 1 "Stay fit!"
> limit 1: 0
#
Nespravny vstup.

Zkratka:
Hello
Nespravny vstup.
```

### Advice:
- The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
- Do not forget the newline (\n) after the last output line.
- Words in the text are separated by one or more spaces. Other characters (letters, digits, punctuation, ...) are considered to form/be part of a word.
- The order of the output lines (with the input text and emphasized letters of the abbreviation) is not set, the testing environment accepts them in any order. For example, the following output is valid for the example run:
```
"Flux fIeld inspecTion and particle affiliation department"
"Flux fIeld inspection and parTicle affiliation department"
...
"flux field inspection and particle afFiliatIon deparTment"
"flux field inspection and particle afFiliatIon departmenT"
```

or
```
"flux field inspection and particle afFiliatIon departmenT"
"flux field inspection and particle afFiliatIon deparTment"
...
"Flux fIeld inspection and parTicle affiliation department"
"Flux fIeld inspecTion and particle affiliation department"
```

or any other of the remaining 544344939077443064003729240247842752644293064388798874532860126869671081148415999999999999998 orders.

- Use fgets or getline functions to read the input. Subsequently, use sscanf to parse the problem type and the integer. Conversion %n may be helpful here.
- The program is tested with several tests. First, the program is tested for valid outputs. Next, the program is tested for correct memory usage (memory debugger is used). Finally, the efficiency of your program is tested.
- A basic solution is expected to use brute-force algorithm with exponential time complexity. Caution: the exponential complexity implies a reasonably good implementation. Any unnecessary overhead may slow down the program significantly. A sensible implementation passes the mandatory and some optional tests. The result will be at most 100 %. 
- The bonus test uses longer abbreviations and longer texts to search in. Bonus tests only input problems of type #; the printing of all choices would be very long (and time demanding).
- The counts of the choices may be quite high. Data type int works fine for the mandatory and optional tests. However, long int or long long is needed when trying to pass the bonus test.
- A program that passes all mandatory and optional tests with 100 % result may be submitted to code review (i.e., you do not need to pass bonus tests for code review).
- There is quite a lot of memory available to your program (~100 MiB for inputs of size a few KiB).
