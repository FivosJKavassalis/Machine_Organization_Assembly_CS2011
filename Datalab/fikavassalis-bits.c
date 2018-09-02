/*
 * CS:APP Data Lab 
 * 
 * Fivos Kavassalis -- fikavassalis
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
7. Use any data type other than int. This implies that you
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
the coding rules are less strict. You are allowed to use looping and
conditional control. You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
1. Define or use any macros.
2. Define any additional functions in this file.
3. Call any functions.
4. Use any form of casting.
5. Use any data type other than int or unsigned. This means that you
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
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
 This file is part of the GNU C Library.

 The GNU C Library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 The GNU C Library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with the GNU C Library; if not, see
 <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
 include it implicitly at the start of every compilation.  It must
 not itself include <features.h> or any other header that includes
 <features.h> because the implicit include comes before any feature
 test macros that may be defined in a source file before it first
 explicitly includes a system header.  GCC knows the name of this
 header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
 and complex.  If the GCC (4.9 and later) predefined macros
 specifying compiler intent are available, use them to determine
 whether the overall intent is to support these features; otherwise,
 presume an older compiler has intent to support these features and
 define these macros by default.  */
/* wchar_t uses Unicode 8.0.0.  Version 8.0 of the Unicode Standard is
 synchronized with ISO/IEC 10646:2014, plus Amendment 1 (published
 2015-05-15).  */
/* We do not support C11 <threads.h>.  */
/* 
 * evenBits - return word with all even-numbered bits set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int evenBits(void) {
	int temp = 0x55;
	temp = temp << 8 | temp; // extend constant so we have 1 in
	temp = temp << 16 | temp; // every even bit position
	return temp;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
     int i = 0x1;
     i = i << 31;
	return !(~(i ^ x)); // if x is Tmax, using xor with i (0x80000000) sets all bits to 1,
	                    // so then I invert this number to its one's complement (0x00000000) and
						// use ! to return 1, only in this case.
}
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	return ~(~(x & ~y) & ~(~x & y)); // Used Demorgan's Law, since it was illegal to do: (x & ~y) | (~x & y)
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	x = !!x; // will get either 1 (if at least one bit is 1) or 0 (if all bits are set to 0)
	x = ~x + 1; // will make all bits set to zero (if x is 0 from the above expression), or
				// all bits set to 1 (if x from expression above becomes 1)

	return (x & y) | (~x & z);

}
/* 
 * greatestBitPos - return a mask that marks the position of the
 *               most significant 1 bit. If x == 0, return 0
 *   Example: greatestBitPos(96) = 0x40
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4 
 */
int greatestBitPos(int x) {

	x = (x >> 1) | x; // set all bit positions after
	x = (x >> 2) | x; // leftmost 1, to 1
	x = (x >> 4) | x;
	x = (x >> 8) | x;
	x = (x >> 16)| x;

	return (x & ((~x >> 1) ^ (1 << 31))); // keep only the leftmost 1 by ignoring the rest bits
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
	int pwr2 = (1 << n); // this is 2^n
	int MSB = (x >> 31); // makes all bits 1 if MSB is of negative sign (1), or all bits 0 if
	                     // MSB is of positive sign (0) or zero
	int bias = pwr2 + ~0; // if x is negative, in order to round toward zero, we must add this bias
	return (x + (MSB & bias)) >> n; // If x is nonnegative it ignores the bias, since all
									// bits of MSB are set to zero. However, if x is negative the bias is used in order to
									// calculate the end result (rounding to 0)

}
/* 
 * isNonNegative - return 1 if x >= 0, return 0 otherwise 
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int isNonNegative(int x) {
	int sign = x >> 31; // sign bits all set to 0 if x is nonnegative
	return !sign; // use ! to return 1 if x is nonnegative and 0 if negative
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
	int tmin = 1 << 31;
	int NOTtmin = ~tmin;
	int maxNum = (x >> 31) ^ (NOTtmin); // To determine whether Tmax or Tmin should be returned (in case of overflow)
										 // depending on sign of x

	int two = x + x;
	// for overflow in case (x + x) has an overflow
	int val1 = ((x ^ two) >> 31);
	int NOTval1 = ~val1;

	int three = two + x;
	// for overflow in case (two + x) has an overflow
	int val = ((two ^ three) >> 31);
	int NOTval = ~val;

	// First overflow case
	int FirstOverflow = ((maxNum) & (val1 & NOTval));
	// Second overflow case
	int SecondOverflow = (((two >> 31) ^ (NOTtmin)) & (NOTval1 & val));
	// In case both overflow
	int BothOverflow = ((maxNum) & (val1 & val));

	return (FirstOverflow | SecondOverflow | BothOverflow | ((NOTval & NOTval1) & three));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {

	  int noSign = !((x + (~y)) >> 31); // without thinking of the signs x, y have, I get 1 if x > y
	  int signX = x >> 31;
	  int signY = y >> 31;
	  return ((!signX) & signY) | (noSign & ((!signX) | signY)); // the role of the first member of the "|", is
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // to always return 1 if x is positive and y is negative and
	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	 // return 0 only if x is negative and y is positive
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {

	int minLim = (x + (~0x30 + 1)) >> 31; // equivalent to : x - 0x30 (to see if x is greater or equal to 0x30)
	int maxLim = (0x39 + ((~x) + 1)) >> 31; // equivalent to : 0x39 - x (to see if x is less or equal to 0x39)

	return (!(minLim | maxLim));

}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples: trueFiveEighths(11) = 6
 *            trueFiveEighths(-9) = -5
 *            trueFiveEighths(0x30000000) = 0x1E000000 (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 4
 */
int trueFiveEighths(int x) {

	int a = x & 7; // calculate rest
	int x5 = a + a + a + a + a;
	int res = ((x5 + (((x >> 3) >> 31) & 7)) >> 3);
	return (x >> 3) + ((x >> 3) << 2) + res; // add with (5/8)*x to round to 0
}

/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {

	int log = ((!!(x >> 16)) << 4); // searching for leftmost 1 bit
	log += ((!!(x >> (log + 8))) << 3);
	log += ((!!(x >> (log + 4))) << 2);
	log += ((!!(x >> (log + 2))) << 1);
	log += (!!(x >> (log + 1)));

	return log;

}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {

	int exp = ((uf >> 23) & 0xff); // Isolate only the bits that belong to exp
	int mant = (uf & 0x7fffff); // Isolate only the bits that belong to mantissa
	if ((exp == 0xff) & (mant != 0)) // NaN case
		return uf;
	else
		return (uf ^ (1 << 31)); // switch sign
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {


	if (!x) // if x is 0
		return x;

	unsigned int res = 0x80000000 & x; // sign

	if (x & 0x80000000)
		x = -x; // change sign x to positive

	unsigned int a = x;
	unsigned int b = 0;
	while (a) // a is not 0
		a >>= 1, b++;

	res += ((b + 126) << 23);
	x <<= (31 - b);
	res += (x >> 7) & 0x007FFFFF;
	res += (0x40 & x) && (0x40 ^ (x & 0xff)); // round up
	return res;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {

	if (uf == 0 || uf == 0x80000000) // if x is 0
		return uf;
	if (((uf >> 23) & 0xff) == 0xff) // if exp bits are all 1 (either NaN or infinity)
		return uf;
	if (!((uf >> 23) & 0xff)) // if exp bits are all 0
		return (uf & (1 << 31)) | (uf << 1);

	return uf + (1 << 23); // equivalent of expression 2*f
}
