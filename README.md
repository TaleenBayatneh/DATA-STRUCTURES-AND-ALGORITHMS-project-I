# Polynomial ADT with Linked Lists

A C program that implements a **Polynomial Abstract Data Type (ADT)** using **linked lists**, supporting arithmetic operations such as **addition, subtraction, and multiplication**.  

Polynomials are read from an input file, stored in a stack, and manipulated through an **interactive menu-driven interface**.

---

## Project Overview

- **Linked List Representation** → Each polynomial is a linked list of terms (`coefficient`, `exponent`).  
- **Stack Storage** → Multiple polynomials stored in a stack structure.  
- **File I/O Support** → Load polynomials from an input file, save results to output file.  
- **Arithmetic Operations** → Add, subtract, and multiply polynomials.  
- **User Interaction** → Simple command-line menu for navigation.  

---

## Features

- Load polynomials from file  
- Display polynomials on screen  
- Perform addition, subtraction, multiplication  
- Save results to file  
- Error checking and input validation  
- Proper memory management with dynamic allocation  

---

## Menu Operations

1. Load polynomials from file  
2. Print all loaded polynomials  
3. Add two polynomials  
4. Subtract two polynomials  
5. Multiply two polynomials  
6. Print results to screen  
7. Save results to file  
8. Exit  

---

## File Format

### Input File Example (`polynomials.txt`):
```txt
31x^5 - 2x^3 + x^2 + 4
-3x^4 - x^2
8x^2 - 9
```


Each line represents one polynomial.  
Terms can appear in any order and may have positive or negative coefficients.  

---

 ## Implementation Details

- Language: C
- Data Structures: Singly linked lists, stack
- Algorithms: Polynomial addition, subtraction, multiplication
- Memory Management: Dynamic allocation & freeing of nodes
