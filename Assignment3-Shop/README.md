# Assignment3-Shop
Finding the maximum amount spent on shopping variously priced products. Used three ways to achieve that: recursive, recursive with memorization, iterative with dynamic programming.

Compile:  
gcc -c -o shop.o shop.c  
gcc -c -o shoprec.o shoprec.c  
gcc -c -o shopmem.o shopmem.c  
gcc -c -o shopdp.o shopdp.c  
gcc -o shoprec shop.o shoprec.o  
gcc -o shopmem shop.o shopmem.o  
gcc -o shopdp shop.o shopdp.o  

1) Recursive Execution:  
./shoprec AMOUNT
2) Recursive with Memorization Execution:  
./shopmem AMOUNT
3) Iterative with Dynamic Programming Execution:  
./shopdp AMOUNT
