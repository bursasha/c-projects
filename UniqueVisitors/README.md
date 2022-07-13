# The task is to develop a program that processes log and analyzes unique visits.

Assume we register all visits to our WWW server. In particular, we register the users that access our server. Each user is given an unique id - an integer in the range [ 0 ; 99999 ]. The program is given the information on user access via the registration command, the command has the form + id, e.g.,
```
+ 123
+ 456
+ 123
+ 123
+ 789
```

Here, user 123 accessed our server in positions 0, 2 and 3, user 456 accessed the server in position 1 and user 789 accessed the server in position 4.

Next, we need to compute the unique users that accessed our server in a given range of time, For the sake of simplicity, we consider the position instead of time. The computation is requested by the analyze command. The command has the form ? from to where from and to are integer positions from where / to where compute the unique users. For the example above, a request ? 0 4 results in answer 3 / 5 (3 unique users in the range of length 5).

The input of the program is a list of commands to register mixed with commands to analyze the stored data. The program processes the input, stores the registrations and answers the analyze requests. The processing terminates when there is an error in the input or when all data are processed (EOF). There is at most 1000000 registration commands in the input.

The output of the program is:
- the information on the visit # for the registration command,
- the information on unique users / total range length for the analyze command.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The registration command is considered invalid, if:
- user id is missing,
- id is not an integer, 
- id is not in the range [ 0 ; 99999 ], or 
- there is more than 1000000 visits registered with the registration command.

The analyze command is invalid, if:
- from or to is missing, 
- from / to are not integers, 
- from is smaller than 0, 
- to is greater or equal to the number of visits registered so far, or 
- from is greater than to.

Obviously, the input is also rejected if the command is neither registration nor analyze.

### Sample program runs:
```
Pozadavky:
+ 10
> prvni navsteva
+ 20
> prvni navsteva
+ 99999
> prvni navsteva
+ 5
> prvni navsteva
+ 20
> navsteva #2
+ 25
> prvni navsteva
+ 10
> navsteva #2
? 0 6
> 5 / 7
? 0 5
> 5 / 6
? 1 6
> 5 / 6
? 1 5
> 4 / 5
? 2 6
> 5 / 5
? 2 5
> 4 / 4
? 2 4
> 3 / 3
? 2 3
> 2 / 2
? 2 2
> 1 / 1
+ 5
> navsteva #2
+ 10
> navsteva #3
+ 5
> navsteva #3
+ 20
> navsteva #3
? 0 10
> 5 / 11
? 7 10
> 3 / 4
? 1 11
Nespravny vstup.

Pozadavky:
+ 10
> prvni navsteva
+ 20
> prvni navsteva
+ 30
> prvni navsteva
? 2 1
Nespravny vstup.

Pozadavky:
+ 12
> prvni navsteva
* 33
Nespravny vstup.
```

### Advice:
- The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
- Do not forget the newline (\n) after the last output line.
- The problem is somewhat simplified. There is only a limited number of ids (0 to 99999), moreover, there is a limited number of registration commands in the input (at most 1000000). If you need to save the list of all visits, use a statically allocated array of a fixed size.
- The program is tested with several tests. First, the program is tested for valid outputs. Next, the program is tested for correct memory usage (memory debugger is used). Finally, the efficiency of your program is tested.
- A basic solution does not have to be extremely fast, even naive (quadratic) algorithm may be used to establish the number of unique users. Such program passes the mandatory and some optional tests. The result will be at most 100 %. The first bonus test uses long inputs with many registration commands. Moreover, the unique users are to be searched in long ranges. The naive algorithm is not efficient enough to compute the result in given time; an improved algorithm must be used instead.
- Finally, there is second speed test. In addition to long inputs, there are many analyze commands in the test. The input data must be pre-processed to avoid repeated computation in the subsequent searches.
- A program that passes all mandatory and optional tests with 100 % result may be submitted to code review (i.e., you do not need to pass bonus tests for code review).
