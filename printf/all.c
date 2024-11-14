/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matus <matus@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:22:57 by matus             #+#    #+#             */
/*   Updated: 2024/11/13 22:57:33 by matus            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar_fd(char c, int fd)
{
 	return (write(fd, &c, 1));
}

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int ft_print_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		ft_putstr("(null)");
		return (6);
		
	}
	while(str[i])
	{
		ft_print_char(str[i++]);
	}
	return(i);
}

int	ft_putnbr(int n)
{
	int	counter;
	counter = 0;
	if (n == -2147483648)
	{
		counter += ft_putstr("-2147483648");
	}
	else
	{
		if (n < 0)
		{
			counter += ft_putchar_fd('-', 1);
			n = (n * (-1));
		}
		if (n > 9)
		{
			counter += ft_putnbr(n / 10);
			
		}
		counter += ft_putchar_fd((n % 10) + 48, 1);
	}
	return(counter);
}

int	ft_uint_len(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n >= 1)
	{
		len++;
		n /= 10;
	}
	return (len);
}

int	ft_unint(unsigned int n, int fd)
{
	int count;
	int	len;
	int i;

	count = 0;
	i = 1;
	len = ft_uint_len(n);
	if (len > i)
	{
		count += ft_unint(n / 10, fd);
	}
	count += ft_putchar_fd((n % 10) + 48, fd);
	i++;
	return (count);
}

int	ft_print_int(int n)
{
	int	count;
	count = 0;
	
	count += ft_putnbr(n);
	return(count);
}

int ft_print_uint(unsigned int n)
{
	int count;
	count = 0;
	
	count += ft_unint(n, 1);
	return (count);
}

int	ft_adrr(unsigned long n, int ident)
{
	int	count;
	count = 0;
	if (n >= 16)
	{
		count += ft_adrr(n / 16, ident);
		count += ft_adrr(n % 16, ident);
	}
	else
	{
		
		if (n < 10)
		{
			count += ft_putnbr(n);
		}
		else if (n >= 10 && ident == 0)
		{
			count += ft_putchar_fd((n - 10) + 97, 1);
		}
		else
		{
			count += ft_putchar_fd((n - 10) + 65, 1);
		}
	}
	return(count);
}

int	ft_print_ptr(unsigned long n, int ident)
{
	int count;
	
	count = 0;
	if (n == 0)
	{
		count += ft_print_str("(nil)");
	}
	else
	{
		count += ft_print_str("0x");
		count += ft_adrr(n, ident);
	}
	return(count);
}

int ft_print_hex(unsigned int n, int ident)
{
	return(ft_adrr(n, ident));
}

int	ft_print_input(const char *spec, va_list ap)
{
	int	counter;
	
	counter = 0;
	if (*spec == 'c')
		counter += ft_print_char(va_arg(ap, int));
	else if(*spec == 's')
		counter += ft_print_str(va_arg(ap, char *));
	else if(*spec == 'd' || *spec == 'i')
		counter += ft_print_int(va_arg(ap, int));
	else if(*spec == 'u')
		counter += ft_print_uint(va_arg(ap, unsigned int));
	else if(*spec == 'p')
	 	counter += ft_print_ptr(va_arg(ap, unsigned long), 0);
	else if(*spec == 'x')
	 	counter += ft_print_hex(va_arg(ap, unsigned int), 0);
	else if(*spec == 'X')
	 	counter += ft_print_hex(va_arg(ap, unsigned int), 1);
	else if (*spec == '%')
		counter += ft_print_char('%');
	return (counter);
}

int	ft_printf(const char *input, ...)
{
	va_list	arg;
	int	count;
	int i;
	
	va_start(arg, input);
	count = 0;
	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '%')
		{
			count += ft_print_input(&input[++i], arg);
		}
		else
		{
			count += ft_print_char(input[i]);
		}
		i++;
	}
	va_end(arg);
	return (count);
}


// int main()
// {
// 	int x = 550;
// 	char y[60] = "ahoooj pico vole";
//    	int *ptr = &x;
// 	char *point = y;
// 	ft_printf("This is string without spec ");
// 	ft_printf("This is print with spec c : %c %c \n" , 86, 53);
// 	ft_printf("this is print with spec s : %s\n", "STRING%%abs%ahoj123");
// 	ft_printf("%d %i \n", INT_MIN, INT_MAX);
// 	ft_printf("unsigned int : %u ", UINT_MAX);
// 	ft_printf("pointer %p\n%p : \n", (void *)point, (void *)ptr);
// 	ft_printf("%x\n%X\n%x", 15, 155, 1);
// 	ft_printf("%%, %%%% \n\n");
// 	printf("\n \n");
// 	printf("This is orig printf without spec");
// 	printf("This is orig printf with spec c : %c %c\n" , 86, 53);
// 	printf("this is orig printf with spec s : %s\n", "OSTRING%%abs%ahoj123");
// 	printf("%d %i \n", INT_MIN, INT_MAX);
// 	printf("unsigned int : %u \n ", UINT_MAX);
// 	printf("pointer %p\n%p : \n", (void *)point, (void *)ptr);
// 	printf("%x\n%X\n%x", 15, 155, 1);
// 	printf("%%, %%%% \n\n");
// 	return (0);
// }