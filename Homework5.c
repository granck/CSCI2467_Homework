/**
 * Garrick Ranck
 * System Programming Concepts
 * Homework 5
 **/

/**
 * The sys/types.h header includes the definition for size_t
 * The size_t type is used to define the size of an object
 **/
 #include <sys/types.h>

/**
 * The string.h header includes the definition for strnlen
 * The strnlen function gets the size of the string passed into it
 * 	and returns a value of type size_t. A second parameter determines the
 * 	max size to return. If the string exceeds this limit, it returns the maxlength value.
 **/
#include <string.h>

/**
 * The lines containing "size_t" and "strnlen", and everything contained within the curly brackets
 * is a function declaration.
 *
 * size_t refers to the return type of the function
 *	strnlen(...) is the defined name of the function and the parameters it will take
 *		These parameters include a constant character pointer to a string as well as a
 *		value of size_t defining the max length of a string that the function should try to
 *		calculate.
 *
 *	We don't need to create a prototype for the strnlen because it is already included in the
 *	headers listed above.(assuming we would implement this in a class with a main.)
 **/
size_t
strnlen(const char *str, size_t maxlen)
{

	/**
	 * Creates another pointer of type character to use in the for loop
	 * This will allow us to manipulate the pointer without repercussions, since
	 * the original will continue to point to the beginning of the character string.
	**/
	const char *cp;				
	
	/**
	 * The first clause in the for loop assigns the character pointer we made to the 
	 * pointer passed into the function.
	 *
	 * The second clause is the condition to be satisfied.
	 *	It makes two calculations. The first is whether our maxlength variable is not equal to 0
	 *	The second is whether the particular value pointed to by our character pointer is not a
	 *		null terminater.
	 *	If either of these conditions fail to satisfy, the for loop exits
	 *
	 *	The final clause increments the value of the character pointer and decrements the value
	 *		of maxlen. This does 2 things. First, it positions the character pointer to be ready
	 *		to read the next byte in the string(or the next letter). Secondly, it subtracts from
	 *		the maxlen variable, pushing it closer to 0. If it reaches 0, the function has reached
	 *		the maximum amount of characters it is allowed to read from the string.
	 *
	 *	The for loop does not perform any statements outside of these conditions.
	 **/
	for(cp = str; maxlen != 0 && *cp != '\0'; cp++, maxlen--)
		;
	
	/**
	 * Upon exiting the for loop, one of two things will be true.
	 * 1. We've reached the end of the string
	 * 2. We've reached the maxlength that the function is allowed to return
	 *
	 * In either case, we will be returning a value that is type casted to size_t.
	 * The value that is returned is calcuated simply by subtracting the original pointer(str)
	 * refering to the beginning of the string, from the copied pointer (cp) 
	 * that refers to the end of the string or the farthest location it can reached.
	 * This value is the length of the string not including the null terminater character.
	 *
	 * This will always be greater than or equal to 0 if no errors occur
	 **/
		return(size_t)(cp - str);
}
