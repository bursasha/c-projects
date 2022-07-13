# The task is to develop function (just a function, not a whole program), which compares two strings.
The required function has the following interface:
```
int sameWords ( const char * a, const char * b );
```

The parameters are two strings to compare. The parameters are read-only (note the const qualifier).

A program that passes all mandatory and optional tests with 100 % result may be submitted to code review (i.e., you do not need to pass bonus tests for code review).

The return value is either 1 (match) or 0 (no match). The strings match if they are composed of the same words. That is, each word in the first string is at least once present in the second string and vice versa. Case insensitive comparison is used when comparing the words.

Words in this assignment are composed of characters where function isalpha returns nonzero. All other characters are considered word separators.

Submit a source file with the implementation of the required function sameWords. Further, the source file must include your auxiliary functions which are called from sameWords. The function will be called from the testing environment, thus, it is important to adhere to the required interface. Use the sample code below as a basis for your development, complete sameWords and add your required auxiliary functions. There is an example main with some test in the sample below. These values will be used in the basic test. Please note the header files as well as main is nested in a conditional compile block (#ifdef/#endif). Please keep these conditional compile block in place. They are present to simplify the development. When compiling on your computer, the headers and main will be present as usual. On the other hand, the header and main will "disappear" when compiled by Progtest. Thus, your testing main will not interfere with the testing environment's main.

Your function will be executed in a limited environment. There are limits on both time and memory. The exact limits are shown in the test log of the reference. The time limits are set such that a correct implementation of the naive solution passes all mandatory tests. Thus, the solution may be awarded nominal 100% percent. The algorithm must be improved to pass the bonus test. There are long strings with many words being tested in the bonus test.

The implementation must use C strings. C++ strings (std::string) and STL is forbidden. If used, the program will not compile. 

The attached archive contains an outline of the implementation and a few test cases.
