Abstract

In this project, I attempt to translate basic constructs of Fortran90
into equivalent C++ constructs using recursive-descent parsing of
Fortran90 language. I will discuss these constructs in some detail and
how they differ in Fortran90 and C++, the details of how I translate
these constructs, known issues in the project so far and what further
work can be done to improve or advance in this program.

Fortran90 Introduction

Fortran90 is programming is a general-purpose high level programming
language that well suited with numeric computation and scientific
computing. Almost all constructs in Fortran90 are still quite similar to
constructs used in post-modern high level programming languages used
today. In this project, I have attempted to translate the following
Fortran90 constructs into equivalent C++.

\(i) Expressions

Fortran90 offers typical arthmetic operators with precedence levels
similar to high level programming languages in use today. The arithmetic
operators are '+', '-', '\*', '/' are stated in increasing order of
precedence. C++ using the same order of precedence with these operators.
However, Expressions enclosed in parenthese can be used to alter the
precedence of operators in expressions if necessary and both languages
support such feature.

\(ii) 'if' 'else' construct

Fortran90 offers the popular 'if else' construct which is offered by
almost every other general puporse programming language out there. The
initial 'if' clause can be followed by 'else if' clauses and can end
with an 'else' clause with no condition. 'if else' in C++ works in a
similar way.

\(iii) Loops

Fortran 90 offers two types of loops. One is the basic counting loop
that iterates from an initial given value to the final given value.
Other is a general purpose loop in which you use keywords 'cycle' to
perform another iteration and 'exit' to break out of the loop. In this
project, I only cover the basic counting loop and attempt to translate
it into a 'for' loop.

\(iv) Arrays

Fortran 90 can represent arrays quite flexibly such that you cannot do
similarly in popular general purpose programming languages like C++.
While declaring arrays in Fortran90, programmer can indicate 'from' and
'to' values of indexes. For example, one can declare an array starting
from index -10 to +10. If the programmar won't specify the 'from' and
'to' indexes, Fortran90 will allocate the array starting from index
position 1. In C++, the first element in the arrays are always accessed
in index position 0.

\(v) Variable Decleration

Variable decleration is straight forward and similar to how it is done
in C++. The only difference is in use of keywords. In Fortran90, all
variables to be used in the program must be declared first and the
compiler won't allow declerations after we began using assignment
statements, if else, loop statements etc..

Translatation strategy

\(i) Arrays

Since C++ is very strict of index position for arrays, hence, the major
component of this project is to successfully translate the array index
positions in Fortran90 to C++. I used the technique of calculating so
called difference of 'from' and 'to' indexes to calculate the size of
arrays and whenever such arrays are accessed after their decleration. I
subtract 'from' index value from the accessing index value and I get the
equivalent index position to use in C++.

For example, if in Fortran90 an array is declared from index 2 to index
8, in C++, such an array is declared from index 0 to index 6. If I
access the 2^nd^ element in Fortran90, the index will be 3. This will
translate to 1 for use in C++ code. Moreover, I only cover
one-dimensional arrays in this project.

\(ii) Loops

In the project, I only cover the basic counting loop used in Fortran90.
I attempt to translate this loop into an equivalent For loop in C++. In
the basic Fortran90 counting loop, the structure is of the following
form

DO control-var = initial, final \[, step\]

statements

END DO

The equivalent For loop that I translate to of the form

FOR (control-var = initial; control-var &lt;= final; control-var =
control-var + step) {

statements

}

One tricky detail in this counting loop is that if the initial value is
greater than final value that the loop counts negatively. For example,
if initial = 10 and final = 1 then the loop will count negatively. If
these values are given in identifiers then it is impossible to know at
compile time that wether this loop will count negatively or positvely.
Hence, I have ignored this aspect of the counting loop.

\(iii) Evaluation of conditional statements

Fortran90 does not use short-circuit evaluation of conditional
statements. It evaluates all the conditional expressions even if it
isn't necessary for the evaluation of resulting boolean value. C++ uses
the short-circuit evaluation and stops evaluating as soon as we know the
value of the expression. The only major consequence of this difference
is that if functions are called in evaluating the expression and these
functions change the data and then equivalent program in C++ may avoid
executing these functions and the final program output may alter. Since,
I am not covering functions in this project, I have ignored this aspect
of the language.

Known Issues

The 'symbolReader' will not recognize float/real values e.g 0.1, 10e2,
0.1e-2 etc.. The symbolReader program is implemented in such a way that
I was not able to figure out how to recognize real constants. Although
they can be expressed in a regular expression. I priortized spending my
time to translate the constructs rather than worrying about getting the
constants to work. Hence, the translator will only recognize integer
constants.

At the end of the Fortran90 program, you must leave a blank space or a
new line. Otherwise, the symbolReader will not recognize the last token.

The exact intendation and spacing in Fortran90 maynot be exactly the
same in the translated C++ code.

Fortran90 is not case-senstive and C++ is. Hence, whenever my
'symbolReader' object returns a symbol, it is always converted to
lower-case. Hence, when writing upper-case letters in comments. The
translater will convert the comments to lower-case because the
'symbolReader' reads all the symbols as part of the program. It is not a
crucial detail and can be easily fixed but its not it was not crucial
enough to worry about.

Possible Enhancements/Improvements

First of all, we should be able to recognize floating/real constant
values because this is the essence of Fortran language. Almost every
non-trivial Fortran program contains some floating/real valued
constants.

We need to cover functions. Functions are an essential part of any well
written program that performs non-trivial tasks.

Multi-dimensional arrays needs to be covered. Dealing with
multi-dimensional data is common task to deal with in scientific
programming.

Other subtle details such as non-short circuit evaluation of conditional
statements, negative counting do-loops.


