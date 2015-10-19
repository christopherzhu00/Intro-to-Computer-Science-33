/* 
 * CS:APP Data Lab 
 * 
 * Christopher Zhu 104455996
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	/* First we find the inverse of x if it's negative. Then we check 4 bits at a time to see if there are still 1's remaining. Afterwards, we check the first 
		4 bits that we first neglected in and check for the last one. We add one at the end since 0 will still need 1 bit*/
	int sign = x >> 31;
	int holder = 0;

	int replacement = x;
	x = (x & ~sign) | ((~x) & sign);
	int mask = 0xF;
	
	replacement = x;
	
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	x = x >> 4;
	holder += (0x4 & (!!(x & ~0) << 2));
	
	replacement = (replacement >> holder) & mask;
	
	holder += (1 & !!(replacement&mask));
	replacement = replacement >> 1;
	holder += (1 & !!(replacement&mask));
	replacement = replacement >> 1;
	holder += (1 & !!(replacement&mask));
	replacement = replacement >> 1;
	holder += (1 & !!(replacement&mask));
	holder++;
  return holder;
}
/* 
 * sm2tc - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: sm2tc(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int sm2tc(int x) {
	/* Utilizes the fact that the difference between a signed number and the two's complement is that the sign stays the same (aka most leading bit)
		and is the rest of the bits are complement with an additional 1 to change it from one's complement to two's complement*/
  int sign = x >> 31;
  int min = sign << 31;
  int complement = sign ^ x;
  int additionalOne = sign & 1;
  
  return complement + additionalOne + min;
}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	/* shifts x to the right 31 times in order to determine its appropriate sign and then use the NOT operator on the sign which is either 1 if negative
	and 0 if positive since positive numbers should return 1 and negative numbers should return 0*/
  int sign = x >> 31;
  return !(sign);
}

/*
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
	/*We store the bits on the right that we are going to shift and then store the bits on the left that we are going to shift.
		After using OR operand on our new front and end we will get the correct number with its bits shifted to the right*/
  int frontMask = ((1 << n) + (~1) + 1);
  int shiftN = (32 + (~n) + 1);
  int endMask = (~(frontMask << shiftN));
  
  int newFront = (frontMask & x) << shiftN;
  int newEnd = (endMask & (x >> n));
  return (newFront | newEnd);

}
/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
	/* Create a case to handle rounding to 0 for negative numbers by utilizing 2^n-1 by utilizing ~0 as a way to represent -1 and then 
		masking that with either 0x00000000 or 0xFFFFFFFF depending on the sign.*/ 
	int check = ~0 + (1 << n);
	int roundingCase = check & (x >> 31);
	return (x + roundingCase) >> n;
}
/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
/* Creates a mask the verify the odd bits by cleverly using shifting and the OR operand. Then use the XOR operand with the result of using the AND operand comparing x and the mask. The XOR should return all 0's if the odd bits are 1 or have some 1's if some of the odd bits are 0.
 Therefore by tactfully using the ! operand we can reverse the answer and return 1 if all odd-numbered bits are set to 1. */
	int maskOddBits = 0xAA | (0xAA << 8);
	maskOddBits = maskOddBits | (maskOddBits << 16);
	return ! (maskOddBits ^ (x & maskOddBits));
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
/* Makes use of the fact that XOR means that both x&y is false and ~x&~y is false for it to be satisfied.
~x&~y checks the special case where both bits are 0 in order to produce 1 when using & */ 
  return ~(x & y) & ~(~x & ~y); 
}
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
/* Makes use of the fact that by adding the minimum by itself will result in 0 since it would overflow while adding any other number will result in a number that is not 0. 
Therefore, we use the OR operator with !x in order to check special case where x is 0 since the only other case where x+x=0 is when x is 0 or x is the minimum. */
	return !( (!x) | (x + x) );
}
