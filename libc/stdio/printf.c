#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static void print(const char* data, size_t data_length)
{
	for ( size_t i = 0; i < data_length; i++ )
		putchar((int) ((const unsigned char*) data)[i]);
}

int printf(const char* format, ...)
{
	// Obtain the list of parameters.
    va_list parameters;
	va_start(parameters, format);

	size_t amount = 0;

	while (*format != '\0')
	{
		// Print normal characters.
		if (*format != '%')
		{
			print(format, sizeof(char));

			++amount;
			++format;
			continue;
		}

		// Found a format character '%', absorb it.
		++format;

		// Determine what format to print.
		if (*format == 'c')
		{
			// Character format.
			char c = (char)va_arg(parameters, int); // char promotes to int
			print(&c, sizeof(c));

			++amount;
			++format;
		}
		else if (*format == 's')
		{
			// String format.
			const char* data = va_arg(parameters, const char*);
			size_t data_length = strlen(data);
			print(data, data_length);

			amount += data_length;
			++format;
		}
		else if (*format == 'x')
		{
			// Hexadecimal format.
			const char* hexValues = "0123456789ABCDEF";
			const size_t data_length = 8;
			char hexResult[data_length];

			int val = va_arg(parameters, int);
			
			// Convert int to hex format.
			for (int i = data_length - 1; i >= 0; --i)
			{
				int hexIndex = val & 0xF;
				hexResult[i] = hexValues[hexIndex];
				val >>= 4;
			}

			print(hexResult, data_length);

			amount += data_length;
			++format;
		}
		else
		{
			// Backup the pointer and add print the character.
			--format;
			print(format, sizeof(char));
			++amount;
			++format;
		}
	}

	va_end(parameters);

	return amount;
}
