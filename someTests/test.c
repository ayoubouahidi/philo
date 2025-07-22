#include <stdio.h>
#include <string.h>
char    *ft_strncpy(char *dest, char *src, unsigned int n)
{
    unsigned int    i;

    i = 0;
    while (i < n && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    while (i < n)
    {
        dest[i] = '\0';
        i++;
    }
    return (dest);
}


int main(void)
{
	char src[5] = "hello";
	char dest[10];
	printf("strncpy ==> %s \nadam ==> %s\n", ft_strncpy(dest, src, 1), strncpy(dest, src, 1));
    
    return 0;
}