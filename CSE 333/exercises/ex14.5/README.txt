Author: Deepesh Singh (dsingh01@uw.edu)

*** SUMMARY ***
When an object is declared but NOT defined, the () operator is used.
Otherwise, the constructor is used.


*** DETAILS ***
I was really interested in the ability to overload operators
in C++, and I wanted to test its limits and what I could do.

Originally, I began with researching online to see what I could find
as I was hoping I could use any character/number/symbol as an
operator. It turned out this was not the case as I could only overload
operators that exist in C++ (with some exceptions) and not create new ones.

This led me to search all the operators that I could overload and I found
out I could overload the ->, [], and () operator. Out of the three,
I decided to pick the () operator and to see how and when that would be used
versus a constructor that had the same method signature.

Using the Vector class we wrote to for ex9 with the additions of the new
operators, I found that if a variable is declared but not defined on one line,
and then defined, it will use the operator. Otherwise, if they are on the same
line, the constructor will be used. This happens for any form of constructor.
However, if you print the values, you will find that when the operator was
used to instantiate a Vector, none of the values were actually inputted into
the fields, and instead, the default constructor was used to instantiate
the object.