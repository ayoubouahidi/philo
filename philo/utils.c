#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		count++;
		i++;
	}
	return (count);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static long	fornotminette(long result, int cmpt, int cmpmoins)
{
	if (cmpt > 1)
		return (0);
	if (cmpmoins == 1)
		result = result * -1;
	return (result);
}

static long	fornotminette1(long result, int cmpt, int cmpmoins, int *err)
{
	if (cmpt > 1)
		return (0);
	if (cmpmoins == 1)
		result = result * -1;
	(void)err;
	return (result);
}

long	ft_atoi(const char *str)
{
	int		i;
	int		cmpt;
	long	result;
	int		cmpmoins;

	cmpmoins = 0;
	result = 0;
	cmpt = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32 && str[i] != '\0'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		cmpt++;
		cmpmoins += (str[i] == '-');
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i] - 48);
		i++;
	}
	result = fornotminette(result, cmpt, cmpmoins);
	return (result);
}

long	ft_atoi_err(const char *str, int *err)
{
	int		i;
	int		cmpt;
	long	result;
	int		cmpmoins;

	cmpmoins = 0;
	result = 0;
	cmpt = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32 && str[i] != '\0'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		cmpt++;
		cmpmoins += (str[i] == '-');
		i++;
	}
	while (str[i] >= 48 && str[i] <= 57)
	{
		result = result * 10 + (str[i++] - 48);
		if (((result > 2147483647) && !cmpmoins)
			|| ((result > 2147483648) && cmpmoins))
			*err = 1;
	}
	return (fornotminette1(result, cmpt, cmpmoins, err));
}


