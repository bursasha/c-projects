# The task is to develop a program that processes sales and analyzes best selling products.

Assume we register all products sold in our store. We are interested in the products that are selling the best. Our program is able to display the N best selling products, where N is given as a parameter to our program (the first input value).

Each product is identified by its unique name (a string). The name is at most 99 characters long and does not contain any whitespace. A sold product is given in the input as + product-name. Next, there are analytic commands in the input, in particular:
- command # is designated to display the N best selling products. The listing is formatted according to the examples below. There is product name and the number of sold items for each product. The products are listed in an descending order (better selling products go first). Finally, there is a summary printed as the last line with the sum of the above sold items.
- command ? displays the summary only.

The output of the program may be a bit confusing when there are products with equal number of sold items:
- a simple case i presented in the first example run. There are eggs and flour in the listing, we sold 4 items of both. Therefore, these products share 2-nd and 3-rd place in the listing; the order is printed accordingly. Moreover, the relative position of flour/eggs is not given. The testing environment accepts all (here both) variants. Therefore, both listings would be accepted in this case:
```
1. Milk, 5x
2.-3. Eggs, 4x
2.-3. Flour, 4x
4. Beer, 3x

1. Milk, 5x
2.-3. Flour, 4x
2.-3. Eggs, 4x
4. Beer, 3x
```
- A more complex case is shown in the second example run. The program is to compute the top N=3 products. However, the listings are longer than 3 items in some cases, e.g.:
```
1.-4. Black_tea, 1x
1.-4. Caffeine, 1x
1.-4. C/C++_for_dummies, 1x
1.-4. Introduction_to_Algorithms, 1x
```
or:
```
1.-2. Black_tea, 2x
1.-2. Caffeine, 2x
3.-5. C/C++_for_dummies, 1x
3.-5. Energy_drink, 1x
3.-5. Introduction_to_Algorithms, 1x
```
- The listing is longer than N if there exist further products with sales equal to the sales of the displayed products.

The program must validate input data. If the input is invalid, the program must detect it, it shall output an error message (see below), and terminate. If displayed, the error message must be sent to the standard output (do not send it to the error output) and the error message must be terminated by a newline (\n). The following is considered invalid:
- the value of N is not an integer, is negative, or zero,
- the command is not recognized (valid commands are +, ? and #), 
- a product name is not valid (missing, 100 or more characters).

### Sample program runs:
```
Pocet sledovanych:
4
Pozadavky:
+ Fruits
+ Milk
+ Milk
+ Sugar
+ Butter
+ Beer
+ Vegetables
+ Milk
+ Beer
+ Milk
+ Beer
+ Sugar
+ Eggs
+ Milk
+ Eggs
+ Eggs
+ Eggs
#
1. Milk, 5x
2. Eggs, 4x
3. Beer, 3x
4. Sugar, 2x
Nejprodavanejsi zbozi: prodano 14 kusu
+ Flour
+ Flour
+ Flour
+ Flour
#
1. Milk, 5x
2.-3. Eggs, 4x
2.-3. Flour, 4x
4. Beer, 3x
Nejprodavanejsi zbozi: prodano 16 kusu
+ Flour
?
Nejprodavanejsi zbozi: prodano 17 kusu
+ Flour
#
1. Flour, 6x
2. Milk, 5x
3. Eggs, 4x
4. Beer, 3x
Nejprodavanejsi zbozi: prodano 18 kusu

Pocet sledovanych:
3
Pozadavky:
+ Introduction_to_Algorithms
+ Black_tea
#
1.-2. Black_tea, 1x
1.-2. Introduction_to_Algorithms, 1x
Nejprodavanejsi zbozi: prodano 2 kusu
+ Caffeine
?
Nejprodavanejsi zbozi: prodano 3 kusu
+ C/C++_for_dummies
#
1.-4. Black_tea, 1x
1.-4. Caffeine, 1x
1.-4. C/C++_for_dummies, 1x
1.-4. Introduction_to_Algorithms, 1x
Nejprodavanejsi zbozi: prodano 4 kusu
+ Black_tea
#
1. Black_tea, 2x
2.-4. Caffeine, 1x
2.-4. C/C++_for_dummies, 1x
2.-4. Introduction_to_Algorithms, 1x
Nejprodavanejsi zbozi: prodano 5 kusu
+ Energy_drink
+ Caffeine
#
1.-2. Black_tea, 2x
1.-2. Caffeine, 2x
3.-5. C/C++_for_dummies, 1x
3.-5. Energy_drink, 1x
3.-5. Introduction_to_Algorithms, 1x
Nejprodavanejsi zbozi: prodano 7 kusu
?
Nejprodavanejsi zbozi: prodano 7 kusu
+ Energy_drink
?
Nejprodavanejsi zbozi: prodano 6 kusu
+ Energy_drink
?
Nejprodavanejsi zbozi: prodano 7 kusu
+ Caffeine
?
Nejprodavanejsi zbozi: prodano 8 kusu
+ Energy_drink
+ Energy_drink
#
1. Energy_drink, 5x
2. Caffeine, 3x
3. Black_tea, 2x
Nejprodavanejsi zbozi: prodano 10 kusu
+ C/C++_for_dummies
#
1. Energy_drink, 5x
2. Caffeine, 3x
3.-4. C/C++_for_dummies, 2x
3.-4. Black_tea, 2x
Nejprodavanejsi zbozi: prodano 12 kusu

Pocet sledovanych:
3
Pozadavky:
* Avoiding_invalid_input_3-rd_edition
Nespravny vstup.
```

### Advice:
- The sample runs above list both the output of your program (boldface font) and user input (regular font). The bold/regular formatting is included here, in the problem statement page, to increase readability of the listing. Your program must output the text without any additional markup.
- Do not forget the newline (\n) after the last output line.
- The number of different products and the number of items sold may be arbitrarily high. There is not any explicit limit. If you need to store the list of sold items/products, you have to use dynamically allocated memory. Static allocation will not work.
- Product name as such is limited to 99 characters. Therefore, the name itself is may be stored into some fixed-size array (and it is recommended to do so).
- Structures are recommended for this assignment. For example, use structure to aggregate the name of a product and its sales.
- The program is tested with several tests. First, the program is tested for valid outputs. Next, the program is tested for correct memory usage (memory debugger is used). Finally, the efficiency of your program is tested.
- A basic solution does not have to be extremely fast. Such implementation passes the mandatory and some optional tests. The result will be at most 100 %.
- The first bonus test uses long inputs with many different products sold. However, the value of N is relatively small. The naive algorithm is not efficient enough to compute the result in given time; an improved algorithm must be used instead. Finally, there is second speed test. In addition to long inputs, the value of N is high. You may assume that the ? command is very frequent whereas command # is used with low frequency (long listings would slow down the program significantly).
- A program that passes all mandatory and optional tests with 100 % result may be submitted to code review (i.e., you do not need to pass bonus tests for code review).
- Use C programming language to solve the problem. Do not use C++ data structures, these are disabled in this assignment.
