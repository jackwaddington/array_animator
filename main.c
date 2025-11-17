#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#define SPINNER_CHARS "|/|\\"
#define SPINNER_LEN 4

typedef struct s_data {
	int	strip_len;
	int	r_trim;
	int	l_trim;
	int	split;
	int	cycles;
	int	x;
	int	y;
	char	disp[81];
	int	spinner_index;
} t_data;

void	info()
{
	printf("Usage: ./a.out <strip_len> <r_trim> <l_trim> <split_pos> <cycles>\n");
	printf("----------------------------------------------------------------\n");
	printf("1 - strip length (1 - 80)\n");
	printf("2 - left trim position\n");
	printf("3 - right trim position\n");
	printf("4 - split position\n");
	printf("5 - number of cycles. 0 = inf.\n");
}

int	validate_strip_len(char *a, t_data *d)
{
	int strip_len = atoi(a);

	if (strip_len < 1 || strip_len > 80)
	{
		printf("Error: Strip length must be between 1 - 80.\n");
		return 0;
	}
	d->strip_len = strip_len;
	printf("strip_len = %d\n", strip_len);
	return 1;
}

int	validate_right_trim(char *a, t_data *d)
{
	int r_trim = (d->strip_len - (atoi(a)));

	if (r_trim > d->strip_len)
	{
		printf("Error: Right trim (%d) must be between 3 and strip length (%d) -2 .\n", r_trim, d->strip_len);
		return 0;
	}
	d->r_trim = r_trim;
	printf("r_trim = %d\n", r_trim);
	return 1;
}	

int	validate_left_trim(char *a, t_data *d)
{
	int l_trim = (atoi(a));

	if (l_trim > d->strip_len)
	{
		printf("Error: Left trim (%d) must be between 0 and strip length - 1.\n", l_trim);
		return 0;
	}
	d->l_trim = l_trim;
	printf("l_trim = %d\n", l_trim);
	return 1;
}

int	validate_split_pos(char *a, t_data *d)
{
	int split = atoi(a);

	if (split <= d->l_trim || split >= d->r_trim)
	{
		printf("Error: Split position (%d) is outside the valid trim range (%d to %d).\n", split, d->l_trim, d->r_trim);
		return 0;
	}
	d->split = split;
	printf("split = %d\n", split);
	return 1;
}

int	validate_cycles(char *a, t_data *d)
{
	long cycles = atol(a); // Use atol for safety

	if (cycles > INT_MAX || cycles < 0)
	{
		printf("Error: Cycles must be between 0 and INT_MAX.\n");
		return 0;
	}
	d->cycles = (int)cycles;
	printf("cycles = %ld\n", cycles);
	return 1;
}

int	validate_input(char *av[], t_data *d)
{
	if(!validate_strip_len(av[1], d))
		return 0;
	if(!validate_left_trim(av[2], d))
		return 0;
	if(!validate_right_trim(av[3], d))
		return 0;
	if(!validate_split_pos(av[4], d))
		return 0;
	if(!validate_cycles(av[5], d))
		return 0;
	d->x = d->split;
       	d->y = d->split;
	d->spinner_index = 0;
	return 1;
}

void	set_string(t_data *d)
{
	// INIT STRING
	// set default value to '-' with null terminated string
	memset(d->disp, '-', sizeof(d->disp));
	d->disp[d->strip_len] = '\0';
	
	// DRAWING LOOP
	for (int i = 0; i < d->strip_len; i++)
	{
		// make the ends blank
		if (i < d->l_trim || i>= d->r_trim)
			d->disp[i] = ' ';

		// walk the 'x'
		if (i == d->x)
			d->disp[i] = '/';

		// walk the 'y'
		if (i == d->y)
			d->disp[i] = '\\';

		// mark the split
		if (i == d->split)
			d->disp[i] = SPINNER_CHARS[d->spinner_index];
	}

	// MOVEMENT LOGIC
	// update position of 'x'

	d->x--;
	if (d->x < d->l_trim)
		d->x = d->split;

	// update position of 'y'
	d->y++;
	if (d->y >= d->r_trim)
		d->y = d->split;

	d->spinner_index = (d->spinner_index + 1) % SPINNER_LEN;

}


void	display(t_data *d)
{
	printf("%s\n", d->disp);
	fflush(stdout);
	usleep(300000);
}

int main(int ac, char* av[])
{
	t_data d;
    
	if (ac != 6)
	{
		info();
		return (1);
	}

	if (!validate_input(av, &d))
		return (1);

	if (d.cycles == 0)
	{
		printf("Running indefinitely. Press Ctrl+C to stop.\n");
		while (1)
		{
			set_string(&d);	
			display(&d);
			d.cycles++;
		}
	}
	else
	{
		printf("Running for %d cycles.\n", d.cycles);
		while(d.cycles > 0)
		{
			set_string(&d);
			display(&d);
			d.cycles--;
		}
	}	
    printf("\nFinished.\n");
	return (0);	
}
