/*************************************************************************
	ARMFUNCTION
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com> 
License: GNU General Public License
Hardware: all
Date: 18062023
Update: 07012024
Comment:
	Tested ->  Atemga128, Atmega328, Atmega32U4, Atmega324, Atmega8535, Atmega88, STM32F446RE
	Very Stable
*************************************************************************/
/*** File Library ***/
#include "armfunction.h"
#include "armquery.h"
#include "armsystick.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdarg.h>
#include <math.h>

#define MAX_FUNCSTR_LEN (FUNCSTRSIZE + 1)
#define SUCCESS 0
#define ERROR_BUFFER_OVERFLOW 1
#define ERROR_FORMATTING 2
#define ERROR_INVALID_BUFFER 3

/*** File Variable ***/
static FUNC setup_func;
static ARM_FUNC setup_arm_func;

static char FUNCstr[MAX_FUNCSTR_LEN];
static uint32_t mem[4];
static uint32_t nen[4];
/*** SYSTEM ***/
void ARMFUNC_ArmParDisplay4x20(ARMLCD0* func_lcd);

ARM_FUNC* arm_func_inic(void);
/*** File Header ***/
unsigned int function_power(unsigned int x, unsigned int y);
RealNum_TypeDef function_divide(int numerator, int denominator);
RealNum_TypeDef function_realnumber(double real, unsigned int decimal);
/*** 0 ***/
int function_StringLength (const char string[]);
void function_Reverse(char* str);
unsigned int function_UintInvStr(RealNum_TypeDef num, unsigned int index);
unsigned int function_FloatInvStr(RealNum_TypeDef num, unsigned int index);
void function_swap(long *px, long *py);
/*** 1 ***/
uint16_t function_SwapByte(uint16_t num);
/*** 2 ***/
void function_copy(char to[], const char from[], size_t to_size);
void function_squeeze(char s[], char c);
void function_shellsort(int v[], int n);
char* function_resizestr(char *string, int size);
int function_trim(char s[]);
/*** 3 ***/
uint8_t function_bcd2dec(uint8_t num);
uint8_t function_dec2bcd(uint8_t num);
char* function_dectohex(int32_t num);
uint8_t function_bcd2bin(uint8_t val);
int function_twocomptoint8bit(int twoscomp);
int function_twocomptoint10bit(int twoscomp);
int function_twocomptointnbit(int twoscomp, uint8_t nbits);
/*** 4 ***/
int function_format_string(char *buffer, size_t size, const char *format, ...);
char* function_print_binary(unsigned int n_bits, unsigned int number);
/*** 5 ***/
char* function_i16toa(int16_t n);
char* function_ui16toa(uint16_t n);
char* function_i32toa(int32_t n);
char* function_ui32toa(uint32_t n);
char* function_ftoa(double num, unsigned int decimal);
/*** 6 ***/
long function_trimmer(long x, long in_min, long in_max, long out_min, long out_max);
int function_pmax(int a1, int a2);
int function_gcd_v1 (uint32_t a, uint32_t b);
long function_gcd_v2(long a, long b);
/*** 7 ***/
int function_StrToInt (const char string[]);
/*** 8 ***/
uint32_t function_triggerA(uint32_t hllh_io, uint8_t pin, uint32_t counter);
uint32_t function_triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter);
uint32_t function_read_value(void);
/********************************************************************/
// Function to convert an integer to a string
void int_to_string(int value, char* buffer, size_t buffer_size);
// Function to convert an unsigned integer to a string
void uint_to_string(unsigned int value, char* buffer, size_t buffer_size);
// Function to convert a string to an integer
int32_t string_to_int(const char* str);
// Function to convert a string to an unsigned integer
uint32_t string_to_uint(const char* str);
// Function to convert an integer to a hexadecimal string
void int_to_hex_string(unsigned int value, char* buffer, size_t buffer_size);
/*** COMMON ***/
void FUNC_var(void);

/*** FUNC Procedure & Function Definition ***/
FUNC FUNC_enable( void )
{
	FUNC_var();
	/*** TOP ***/
	setup_func.power = function_power;
	setup_func.divide = function_divide;
	setup_func.realnumber = function_realnumber;
	setup_func.stringlength = function_StringLength;
	setup_func.reverse = function_Reverse;
	setup_func.swap = function_swap;
	/***********/
	// 1
	setup_func.SwapByte = function_SwapByte;
	// 2
	setup_func.copy = function_copy;
	setup_func.squeeze = function_squeeze;
	setup_func.shellsort = function_shellsort;
	setup_func.resizestr = function_resizestr;
	setup_func.trim = function_trim;
	// 3
	setup_func.bcd2dec = function_bcd2dec;
	setup_func.dec2bcd = function_dec2bcd;
	setup_func.dectohex = function_dectohex;
	setup_func.bcd2bin = function_bcd2bin;
	setup_func.twocomptoint8bit = function_twocomptoint8bit;
	setup_func.twocomptoint10bit = function_twocomptoint10bit;
	setup_func.twocomptointnbit = function_twocomptointnbit;
	// 4
	setup_func.format_string = function_format_string;
	setup_func.print_binary = function_print_binary;
	// 5
	setup_func.i16toa = function_i16toa;
	setup_func.ui16toa = function_ui16toa;
	setup_func.i32toa = function_i32toa;
	setup_func.ui32toa = function_ui32toa;
	setup_func.ftoa = function_ftoa;
	// 6
	setup_func.trimmer = function_trimmer;
	setup_func.pmax = function_pmax;
	setup_func.gcd_v1 = function_gcd_v1;
	setup_func.gcd_v2 = function_gcd_v2;
	// 8
	setup_func.strToInt = function_StrToInt;
	// 9
	setup_func.triggerA = function_triggerA;
	setup_func.triggerB = function_triggerB;
	setup_func.value = function_read_value;
	// 10
	setup_func.arm = arm_func_inic();

	return setup_func;
}

FUNC* func(void){ return &setup_func; }

void FUNC_var(void)
{
	FUNCstr[FUNCSTRSIZE] = '\0';
	mem[0] = 0; nen[0] = 0;
}
ARM_FUNC* arm_func_inic(void)
{
	setup_arm_func.dispar4x20 = ARMFUNC_ArmParDisplay4x20;

	return &setup_arm_func;
}
/*** FUNC Procedure & Function Definition***/
void ARMFUNC_ArmParDisplay4x20(ARMLCD0* func_lcd)
{
#ifdef STM32F4
	#ifdef _ARMLCD_H_
		static uint16_t toggle = 0;
		func_lcd->gotoxy(0,0);
		func_lcd->string_size("sysclk:",7);
		func_lcd->string_size( function_ui32toa( getsysclk()), 10);
		func_lcd->gotoxy(1,0);
		func_lcd->string_size("pllclk:",7);
		func_lcd->string_size( function_ui32toa( getpllclk()), 10);
		if(toggle & 1){
			func_lcd->gotoxy(2,0);
			func_lcd->string_size("ahb:",4); func_lcd->string_size( function_ui32toa( gethpre() ), 4);
			func_lcd->string_size("apb1:",5); func_lcd->string_size( function_ui32toa( gethppre1() ), 3);
			func_lcd->gotoxy(3,0);
			func_lcd->string_size("apb2:",5); func_lcd->string_size( function_ui32toa( gethppre2() ), 3);
			func_lcd->string_size("rtc:",4); func_lcd->string_size( function_ui32toa( getrtcpre() ), 3);
		}else{
			func_lcd->gotoxy(2,0);
			func_lcd->string_size("M:",2); func_lcd->string_size( function_ui32toa( getpllm() ), 6);
			func_lcd->string_size("N:",2); func_lcd->string_size( function_ui32toa( getplln() ), 6);
			func_lcd->gotoxy(3,0);
			func_lcd->string_size("P:",2); func_lcd->string_size( function_ui32toa( getpllp() ), 2);
			func_lcd->string_size("Q:",2); func_lcd->string_size( function_ui32toa( getpllq() ), 7);
		}
		func_lcd->gotoxy(3,15);
		func_lcd->string_size(function_ui32toa(toggle),5);
		toggle++;
		_delay_ms(6000);
	#endif
#endif
}
// Function to calculate power of a base number
unsigned int function_power(unsigned int base, unsigned int power) {
    unsigned int result = 1;
    for (unsigned int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}
// Function to handle division and return a Real structure
RealNum_TypeDef function_divide(int numerator, int denominator) {
    RealNum_TypeDef result = {0, 1, 0, 0, 1, 0.0, 0.0}; // Default result

    // Handle case for division by zero
    if (denominator == 0) {
        result.sign = 0; // Indicate invalid result due to division by zero
        return result;
    }

    // Handle the sign of the result
    result.sign = ((numerator < 0) ^ (denominator < 0)) ? -1 : 1;
    result.Numerator = (uint32_t)(numerator < 0 ? -numerator : numerator);
    result.Denominator = (uint32_t)(denominator < 0 ? -denominator : denominator);

    // Calculate quotient and remainder
    result.Quotient = result.Numerator / result.Denominator;
    result.Remainder = result.Numerator % result.Denominator;

    // Calculate fractional part
    result.Fpart = (double)result.Remainder / result.Denominator;

    // Calculate the complete number
    result.Number = result.Quotient + result.Fpart;

    return result;
}
// Function to process real numbers and extract integer/fractional parts
RealNum_TypeDef function_realnumber(double real, unsigned int decimal) {
    RealNum_TypeDef result = {0, 1, 0, 0, 1, 0.0, 0.0, 1};
    // Set the original input number
    result.Number = real;
    // Handle sign of the number
    result.sign = (real < 0) ? -1 : 1;
    // Convert number to absolute value to work with positive parts
    double abs_real = fabs(real);
    // Extract the integer part of the number
    result.Quotient = (unsigned int)abs_real;
    // Extract the fractional part of the number
    result.Fpart = abs_real - result.Quotient;
    // Limit decimal to avoid overflow in precision calculation
    if (decimal > 9) { decimal = 9; } // Clamp the decimal value to a safe range

    // Calculate precision as a power of 10 for the specified decimal places
    result.Precision = function_power(10, decimal);

    // Calculate remainder and set denominator if fractional part exists
    if (result.Precision > 0 && result.Fpart > 0) {
        result.Remainder = (unsigned int)(result.Fpart * result.Precision);
        result.Denominator = result.Precision;
    } else {
        // No fractional part or precision is zero, set remainder to 0
        result.Remainder = 0;
        result.Denominator = 1;
    }

    // Calculate the numerator: (integer part * denominator) + remainder
    result.Numerator = (result.Quotient * result.Denominator) + result.Remainder;

    return result;
}
// Function to calculate the length of a string
int function_StringLength(const char string[]) {
    if (string == NULL) {
        return 0;  // Return 0 for NULL pointer (or handle this as needed)
    }
    if (*string == '\0') {
    	return 0;  // Return 0 for '\0' pointer (or handle this as needed)
    }

    int count = 0;
    while (string[count] != '\0') {
        count++;
    }
    return count;
}
/****
// Function to reverse a string
void function_Reverse(char* str) {
    if (str == NULL){ return; }
    if (*str == '\0'){ return; }
    if (*str == '\0'){ str[0]='E'; str[1]='r'; str[2]='r'; str[3]='o'; str[4]='r'; str[5]='\0'; return; }

    size_t i = 0;
    size_t j = strlen(str) - 1;

    while (i < j) {
        char temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
*****/
/*****/
void function_Reverse(char* str) {
    if (str == NULL){ return; } // Check for null pointer
    if (*str == '\0'){ return; }

    int n = strlen(str);
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}
/*****/
void function_swap(long *px, long *py) {
    // Check for NULL pointers to avoid dereferencing NULL
    if (px == NULL || py == NULL) {
        return; // Simply return if either pointer is NULL
    }

    // Swap the values
    long temp = *px;
    *px = *py;
    *py = temp;
}
uint16_t function_SwapByte(uint16_t num) {
    uint16_t tp;
    tp = (uint16_t)(num << 8);
    return (num >> 8) | tp;
}
void function_copy(char to[], const char from[], size_t to_size) {
    // Check for NULL pointers
    if (to == NULL || from == NULL) {
        return;
    }

    int i = 0;

    // Copy each character while checking the destination size
    while (i < to_size - 1 && (to[i] = from[i]) != '\0') {
        ++i;
    }

    // Ensure the destination string is null-terminated
    to[i] = '\0';
}
void function_squeeze(char s[], char c) {
    if (s == NULL) {
        return; // Handle NULL input gracefully
    }

    int i, j;
    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (s[i] != c) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0'; // Null-terminate the string after squeezing
}
void function_shellsort(int v[], int n) {
    int gap, i, j;

    // Start with a gap and reduce it each iteration
    for (gap = n / 2; gap > 0; gap /= 2) {
        // Perform gapped insertion sort for this gap size
        for (i = gap; i < n; i++) {
            // Save the element to be compared
            int temp = v[i];
            // Perform the comparisons and swaps within the gap
            for (j = i - gap; j >= 0 && v[j] > temp; j -= gap) {
                v[j + gap] = v[j];  // Move element up if it's larger than temp
            }
            v[j + gap] = temp;  // Place temp in the correct position
        }
    }
}
char* function_resizestr(char *string, int size)
{
    int i;
    if (!string) return NULL;  // Check for null pointer

    FUNCstr[size] = '\0';  // Terminate the string at the specified size

    for(i = 0; i < size; i++){
        if(*(string + i) == '\0'){
            for(; i < size; i++){
                FUNCstr[i] = ' ';  // Fill remaining spaces with ' '
            }
            break;
        }
        FUNCstr[i] = *(string + i);  // Copy character by character
    }
    return FUNCstr;  // Return the resized string
}
int function_trim(char s[])
{
    int n;
    for (n = function_StringLength(s) - 1; n >= 0; n--) {
        if (s[n] != ' ' && s[n] != '\t' && s[n] != '\n') {
            break;  // Found the last non-whitespace character
        }
    }

    s[n + 1] = '\0';  // Trim the string by placing the null terminator
    return n >= 0 ? n : 0;  // Ensure it returns 0 if the string was all whitespace
}
/******/
uint8_t function_bcd2dec(uint8_t num)
{
	return ((num / 16 * 10) + (num % 16));
}
uint8_t function_dec2bcd(uint8_t num)
{
	return ((num / 10 * 16) + (num % 10));
}
uint8_t function_bcd2bin(uint8_t val)
{
	return (val & 0x0f) + (val >> 4) * 10;
}
char* function_dectohex(int32_t num) {
    int32_t remainder;
    uint8_t j = 0;

    if (num == 0) {
        FUNCstr[j++] = '0';  // Handle case when number is zero
    } else {
        while (num && j < FUNCSTRSIZE - 1) {  // Prevent buffer overflow
            remainder = num % 16;
            FUNCstr[j++] = (remainder < 10) ? (char)(48 + remainder) : (char)(55 + remainder);  // Convert to '0'-'9' or 'A'-'F'
            num = num / 16;
        }
    }

    FUNCstr[j] = '\0';  // Null-terminate the string
    function_Reverse(FUNCstr);  // Reverse the string since it's generated in reverse order
    return FUNCstr;  // Return the hexadecimal string
}
int function_twocomptoint8bit(int twoscomp) {

    // Check if the byte represents a negative number (sign bit is 1)
    if (twoscomp & 0x80) {
        // Convert two's complement to negative integer
        return (int)(twoscomp - 256);
    } else {
        // For positive values, return the number directly
        return (int)(twoscomp & 0x7F);  // Mask with 0x7F to ensure it stays 7-bit positive
    }
}
int function_twocomptoint10bit(int twoscomp) {
    // Check if the number is negative (sign bit is 1)
    if (twoscomp & 0x200) {
        // For negative numbers, subtract 1024 (since 10-bit two's complement range is -512 to 511)
        return twoscomp - 1024;
    } else {
        // For positive numbers, mask the 9 least significant bits (ignoring the sign bit)
        return twoscomp & 0x1FF;
    }
}
int function_twocomptointnbit(int twoscomp, uint8_t nbits) {
    unsigned int sign_bit = (1 << (nbits - 1));  // Mask for the sign bit
    unsigned int value_mask = sign_bit - 1;      // Mask for the remaining bits

    // Check if the sign bit is set
    if ((unsigned int)twoscomp & sign_bit) {
        twoscomp &= value_mask;  // Clear the sign bit
        twoscomp -= sign_bit;    // Subtract to get the correct negative value
    } else {
        twoscomp &= value_mask;  // For positive numbers, just mask out extra bits
    }

    return twoscomp;
}
/******/
int function_format_string(char *buffer, size_t size, const char *format, ...) {
    // Check for valid buffer and size
    if (buffer == NULL || size == 0) {
        return ERROR_INVALID_BUFFER; // Buffer is invalid
    }

    va_list args;
    va_start(args, format);

    // Use vsnprintf to format the string and get the number of characters that would be written
    int written = vsnprintf(buffer, size, format, args);

    va_end(args);

    // Check for errors
    if (written < 0) {
        return ERROR_FORMATTING; // Formatting error
    } else if ((size_t)written >= size) {
        buffer[size - 1] = '\0'; // Ensure null-termination
        return ERROR_BUFFER_OVERFLOW; // Buffer was too small
    }

    return SUCCESS; // Successful formatting
}
/******/
char* function_i16toa(int16_t n) {
    uint8_t i = 0;
    int16_t sign = n;

    // Handle negative values
    if (sign < 0) {
        n = -n;
    }

    // Convert integer to string in reverse order
    do {
        FUNCstr[i++] = (char)(n % 10 + '0');
    } while ((n /= 10) > 0);

    // Add the negative sign if the number was negative
    if (sign < 0) {
        FUNCstr[i++] = '-';
    }

    FUNCstr[i] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct order
    function_Reverse(FUNCstr);

    return FUNCstr; // Return the formatted string
}
char* function_ui16toa(uint16_t n) {
    uint8_t i = 0;

    // Handle the special case for zero
    if (n == 0) {
        FUNCstr[i++] = '0';
    } else {
        // Convert integer to string in reverse order
        do {
            FUNCstr[i++] = (char)(n % 10 + '0');
        } while ((n /= 10) > 0);
    }

    FUNCstr[i] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct order
    function_Reverse(FUNCstr);

    return FUNCstr; // Return the formatted string
}
char* function_i32toa(int32_t n) {
    uint8_t i = 0;
    int32_t sign = n;

    // Handle negative values
    if (sign < 0) {
        n = -n;
    }

    // Special case for zero
    if (n == 0) {
        FUNCstr[i++] = '0';
    } else {
        // Convert integer to string in reverse order
        do {
            FUNCstr[i++] = (char)(n % 10 + '0');
        } while ((n /= 10) > 0);
    }

    // Add the negative sign if the number was negative
    if (sign < 0) {
        FUNCstr[i++] = '-';
    }

    FUNCstr[i] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct order
    function_Reverse(FUNCstr);

    return FUNCstr; // Return the formatted string
}
char* function_ui32toa(uint32_t n) {
    uint8_t i = 0;

    // Handle the special case for zero
    if (n == 0) {
        FUNCstr[i++] = '0';
    } else {
        // Convert integer to string in reverse order
        do {
            FUNCstr[i++] = (char)(n % 10 + '0');
        } while ((n /= 10) > 0);
    }

    FUNCstr[i] = '\0'; // Null-terminate the string

    // Reverse the string to get the correct order
    function_Reverse(FUNCstr);

    return FUNCstr; // Return the formatted string
}
char* function_print_binary(unsigned int n_bits, unsigned int number) {
    // Check for valid number of bits
    if (n_bits > 32) n_bits = 32; // Cap at 32 bits for uint32_t

    unsigned int i;
    unsigned int c = 0;

    // Generate binary representation
    for (i = (1U << (n_bits - 1)); i; i >>= 1, c++) {
        FUNCstr[c] = (number & i) ? '1' : '0';
    }

    FUNCstr[c] = '\0'; // Null-terminate the string
    return FUNCstr; // Return the formatted string
}
unsigned int function_UintInvStr(RealNum_TypeDef num, unsigned int index)
{
	unsigned int start = index;
	for( FUNCstr[index++] = (char)(num.Quotient % 10 + '0') ; (num.Quotient /= 10) > 0 ; FUNCstr[index++] = (char)(num.Quotient % 10 + '0') );
	FUNCstr[index] = '\0'; function_Reverse(FUNCstr + start); return index;
}
unsigned int function_FloatInvStr(RealNum_TypeDef num, unsigned int index)
{
	unsigned int start = index;
	for( ; (num.Precision /= 10) > 0 ; FUNCstr[index++] = (char)(num.Remainder % 10 + '0'), num.Remainder /= 10 );
	FUNCstr[index] = '\0'; function_Reverse(FUNCstr + start); return index;
}
char* function_ftoa(double num, unsigned int decimal)
{
	RealNum_TypeDef number = function_realnumber(num, decimal);
	unsigned int k = 0;
	if(number.Precision > 1){
		if (number.sign < 0) FUNCstr[k++] = '-';
		k = function_UintInvStr(number, k);  FUNCstr[k++] = '.'; FUNCstr[k] = '\0';
		function_FloatInvStr(number, k);
	}else{
		if (number.sign < 0) FUNCstr[k++] = '-';
		function_UintInvStr(number, k);
	}
	return FUNCstr;
}
/******/
long function_trimmer(long x, long in_min, long in_max, long out_min, long out_max) {
    // Check for valid input range to prevent division by zero
    if (in_max == in_min) {
        // Return a value that makes sense; could be either out_min or out_max
        return (out_min + out_max) / 2; // Midpoint of output range
    }

    // Calculate the scaled value, ensuring we do not overflow
    long mapped_value = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

    // Clamp the result to the output range
    if (mapped_value < out_min) {
        return out_min;
    } else if (mapped_value > out_max) {
        return out_max;
    }

    return mapped_value; // Return the mapped value
}
int function_pmax(int a1, int a2) {
    return (a1 > a2) ? a1 : a2;
}
int function_gcd_v1(uint32_t a, uint32_t b) {
    while (b != 0) {
        uint32_t temp = b;  // Store the current value of b
        b = a % b;          // Incorrectly assigns b, should use temp
        a = temp;           // Assign the previous b to a
    }
    return a;               // Return the GCD
}
long function_gcd_v2(long a, long b) {
    long r;

    // Swap if a is less than b
    if (a < b) {
        function_swap(&a, &b);
    }

    // Handle case when b is zero directly
    if (b == 0) {
        return a; // If b is zero, GCD is a
    }

    // Euclidean algorithm
    while ((r = a % b) != 0) {
        a = b;
        b = r;
    }

    return b; // Return the GCD
}
/******/
int function_StrToInt(const char string[]) {
    int i = 0;
    int result = 0;
    bool isNegative = false;

    // Skip leading whitespaces
    while (string[i] == ' ') {
        i++;
    }

    // Check for negative sign
    if (string[i] == '-') {
        isNegative = true;
        i++;
    } else if (string[i] == '+') {
        i++; // Optional: handle '+' as well
    }

    // Convert string to integer
    for (; string[i] >= '0' && string[i] <= '9'; ++i) {
        int intValue = string[i] - '0';

        // Check for overflow
        if (result > (INT_MAX - intValue) / 10) {
            // Handle overflow as you prefer (e.g., return INT_MAX or some error code)
            return isNegative ? INT_MIN : INT_MAX; // Example handling
        }

        result = result * 10 + intValue;
    }

    return isNegative ? -result : result;
}
/********************************************************************/
// Function to convert a signed integer to a string
void int_to_string(int value, char* buffer, size_t buffer_size) {
    if (buffer_size > 0) {
        snprintf(buffer, buffer_size, "%d", value);
    }
}
// Function to convert an unsigned integer to a string
void uint_to_string(unsigned int value, char* buffer, size_t buffer_size) {
    if (buffer_size > 0) {
        snprintf(buffer, buffer_size, "%u", value);
    }
}
// Function to convert a string to a signed integer
int32_t string_to_int(const char* str) {
    return (int32_t)strtol(str, NULL, 10);
}
// Function to convert a string to an unsigned integer
uint32_t string_to_uint(const char* str) {
    return (uint32_t)strtoul(str, NULL, 10);
}
// Function to convert an integer to a hexadecimal string
void int_to_hex_string(unsigned int value, char* buffer, size_t buffer_size) {
    if (buffer_size > 0) {
        snprintf(buffer, buffer_size, "0x%X", value);
    }
}
// Function to convert a floating-point number to a string
void float_to_string(float value, char* buffer, size_t buffer_size) {
    if (buffer_size > 0) {
        snprintf(buffer, buffer_size, "%.2f", value); // Adjust the format as needed
    }
}
/******/
// triggerA
uint32_t function_triggerA(uint32_t ll_io, uint8_t pin, uint32_t counter)
{
    mem[3] = 0;
    if(mem[0] == 0){
        if( ll_io & (1 << pin) ){
            mem[1] = counter;
            mem[2] = 0;
            mem[0] = 1;
        }
    }
    else if(mem[0] == 1){
        if( ll_io & (1 << pin) ){
            if( counter != mem[1] ){
                mem[2]++;
                mem[1] = counter;
            }
        }
        else{
            mem[3] = mem[2];
            mem[0] = 0;
        }
    }
    return mem[3];
}
// triggerB
uint32_t function_triggerB(uint32_t hl_io, uint32_t lh_io, uint8_t pin, uint32_t counter)
{
    nen[3] = 0;

    switch(nen[0]){ // Start value
        case 0:
            if( hl_io & (1 << pin) ){
                nen[1] = counter;
                nen[2] = 0;
                nen[0] = 1;
            }
        break;

        case 1:
            if( counter != nen[1] ){
                nen[2]++;
                nen[1] = counter;
            }
            if( lh_io & (1 << pin) ){
                nen[3] = nen[2];
                nen[0] = 0;
            }
        break;
    }

    return nen[3];
}

uint32_t function_read_value(void){ return mem[2];}
/*** Not Used ***/
unsigned int function_mayia(unsigned int xi, unsigned int xf, uint8_t nbits)
{
	unsigned int diff;
	unsigned int trans;
	unsigned int mask = (unsigned int)(pow(2, nbits) - 1);
	xi &= mask; xf &= mask; diff = xf ^ xi; trans = diff & xf;
	return (trans << nbits) | diff;
}
// Function to check leap year
uint8_t function_leap_year_check(uint16_t year) {
    uint8_t i;
    if (!(year % 400)) i = 1;
    else if (!(year % 100)) i = 0;
    else if (!(year % 4)) i = 1;
    else i = 0;
    return i;  // Added return statement
}
/***EOF***/

/******
1º Sequence
2º Scope
	- Library Scope
	- File Scope
	- Function Scope
	- Precedence Scope
3º Pointer and Variable
4º Casting
******/

