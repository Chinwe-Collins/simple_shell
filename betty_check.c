#include <stdio.h>
#include <unistd.h>
/**
 * main - Entry point
 *
 * Return: Always zero if successful
 */
int main(void)
{
	write(1, "Hello world\n", 12);
	return (0);
}
