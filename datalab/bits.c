/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
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
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


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

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

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
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
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
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {

  int not_x = ~x;         // 按位取反x
    int not_y = ~y;         // 按位取反y
    int and_x_not_y = x & not_y;    // x和y的非共同位
    int and_not_x_y = not_x & y;    // y和x的非共同位
    int result = ~(~and_x_not_y & ~and_not_x_y);  // 按位取反结果
    return result;
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 1000000000000 32 bit 
  return 1 << 31;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
    int neg_x = ~(x + 1);  // 计算-x的值
    int sum = x + 1;     // 计算x+1的值
    int is_tmax = !(neg_x ^ x);  // 判断~x+1是否等于x
    int is_not_zero = !!sum;       // 判断x+1是否为0
    return is_tmax & is_not_zero;  // 如果两个条件都成立，返回1；否则返回0
}

/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // 构造一个数，其中所有的奇数位都是 1，其他位都是 0
  int A = 0xA;
  int AA = A | (A<<4);
  int AAAA = AA | (AA << 8);
  int mask = AAAA | (AAAA << 16);
  // 将这个数和给定的数进行按位与运算，判断结果是否等于这个数
  int result = (x&mask) ^ mask;
  return !result;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
//3
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
  //1 leading 0
  int a = x >> 6;
  int cond1 = !a; //1
  //2 11xxxx
  int b = x >>4 ;
  int cond2 = !(b^ 0b11);
  //3 xxxx -A <0
  int c = x & (0xF);
  int res = c + (~(0xA)+1);
  int cond3 = (res >> 31);
  return cond1 & cond2 & cond3;
}

/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int mask = ((!!x) << 31) >> 31; // x == 0，mask = 0x00000000；x != 0，mask = 0xffffffff
  int result = (~mask & z) | (mask & y); // x == 0，result = z；x != 0，result = y
  return result;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int cond1 = !(x ^ y); //x == y
  int signX = (x>>31) & 1; // 符号位
  int signY = (y>>31) & 1;
  // overflow
  // x+ y-
  int cond2 = !((!signX) & (signY));
  // x- y+
  int cond3 = signX & (!signY);

  int res = (x + (~y)+1) >> 31;
  int res2 = res& 0b1;
  return cond1 | (cond2 & (cond3 | res2));
   
  
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  int negX = ~x + 1;
  int sign = (negX | x) >> 31;
  return sign + 1;
}
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
  int iszero = !x;
  int sign = x >> 31; // 获取符号位（0或-1）
  int mask = ((!!x)<<31)>>31;
  x = (sign & (~x)) | ((~sign) & x); // 如果x为负，则将其取反
  int bit16,bit8,bit4,bit2,bit1,bit0; // 初始化位计数器
  bit16 = (!!(x >> 16)) << 4; // 检查前16位
  x >>= bit16; // 将x向右移动16位
  bit8 = (!!(x >> 8)) << 3; // 检查接下来的8位
  x >>= bit8 ; 
  bit4 = (!!(x >> 4)) << 2; // 检查接下来的4位
  x >>= bit4 ; 
  bit2 = (!!(x >> 2)) << 1; // 检查接下来的2位
  x >>= bit2 ; 
  bit1 = !!(x >> 1); // 检查最后一位
  x >>= bit1;
  bit0 = x;
  int res = bit0+bit1+bit2+bit4+bit8+bit16+1;
  return iszero | (mask & res); // 加1来考虑符号位
}
//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  //expr ,s ,frac
  unsigned s = (uf>>31) &(0x1);
  unsigned expr = (uf>>23)&(0xFF);
  unsigned frac = (uf & 0x7FFFFF);
  //0
  if (expr == 0 && frac == 0){
    return uf;
  }
  // inifity
  if(expr == 0xFF){
    return uf;
  }
  //denormalize
  if(expr == 0){
    frac <<= 1;
    return (s << 31) | frac;
  }
  //normalzie
  expr++;
  // E = expr-127
  return(s <<31) | (expr<<23) | (frac);
}
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  //expr ,s ,frac
  int sign = uf >> 31; // 获取符号位
  int exp = ((uf >> 23) & 0xFF) - 127; // 获取指数部分
  int frac = (uf & 0x7FFFFF) | 0x800000; // 获取尾数部分，并添加隐藏的1
  int result;

  // 处理特殊情况
  if (exp < 0) {
    return 0;
  } else if (exp >= 31) {
    return 0x80000000u;
  }

  // 计算结果
  if (exp > 23) {
    result = frac << (exp - 23);
  } else {
    result = frac >> (23 - exp);
  }

  // 处理符号位
  if (sign) {
    result = -result;
  }

  return result;

}
/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
    if (x < -126) {
    return 0; // 返回0，因为值太小，无法表示为规格化数或非规格化数
  } else if (x > 127) {
    return 0x7F800000; // 返回+INF，因为值太大
  }

  int exp = x + 127; // 计算指数部分的值
  unsigned result = exp << 23; // 将指数部分左移23位
  return result; // 返回浮点表示
}
