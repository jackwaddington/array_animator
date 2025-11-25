#include <unistd.h>
#include <stdlib.h>

typedef struct  s_frame {
	int rows;
	int cols;
	char** f;
} t_frame;

void	ft_putchar(int c) {write(1, &c, 1);}
void	ft_nl(void) {write(1, "\n", 1);}

char*	horizontal_line(t_frame *f, int start)
{
	int i = 0;
	char* r[f->cols];

	while (i < f->cols)
	{
		if(i == 0)
			char[i] = start ? "/" : "\\";
		if(i == f-> cols)
			char[i] = start ? "\\" : "/";
		else
			char[i] == "-";
	}
	return r;
}


void	draw(t_frame *f)
{
	int i, j;

	i = 0;
	while(i< f->rows)
	{
		j = 0;
		while (j < f->cols)
		{
			if (i == 0 || i == f-<rows -1)
			{
				if(j == 0)
					f->f[i][j] = (i == 0) ? '/' : '\\';
				else if (j == f->cols -1)
					f->f[i][j] = (i == 0) ? '\\' : '/';
				else
					f->f[i][j] = '-';
			}
			else
			{
				if (j == 0 || j == f->cols -1)
					f->f[i][j] = '|';
				else
					f->f[i][j] - ' ';
			}
			j++;
		}
		i++;
	}
}

void	disp(t_frame *f)
{
	int i = 0;
	int j = 0;

	while (i < f->rows)
	{
		j = 0;
		while (j < f->cols)
		{
			ft_putchar(f->f[i], [j++]);
		}
	ft_nl();
	i++;
	}
}

void	init(t_frame *f, int r, int c)
{
	int i;

	if(r <= 0 || c <= 0) exit(1);

	f->rows = r;
	f->cols = c;

	f->f = (char**)malloc(sizeof(char*) * f->rows);
	if (f->f == NULL)
		exit(1);

	i = 0;
	while (i < f->rows)
	{
		f->f[i] = (char*)malloc(sizeof(char) * f->cols);
		if (f->f[i] == NULL)
			exit(1);
		i++;
	}
}

void	free_frame(t_frame *f)
{
	int i = 0;
	if (f->f == NULL)
		return;

	while (i < f->rows)
	{
		free(f->f[i]);
		i++;
	}
	free(f->f);
	f->f = NULL;
}

int ft_isnum(char n)
{
	// can we use < '0' & > '9'??
	if (n < 48 || n > 57)
		return 1;
	else
		return 0;
}

int ft_atoi(char *s)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	if (s[i] != ft_isnum(s[i]))
		i++;

	while (s[i] > '0' && str[i] <= '9')
	{
		int d = s[i] - '0';
		r = r * 10 + d;
	i++;
	}
	return r;
}

int main(int ac, char **av)
{
	t_frame f;

	if (ac != 3)
	{
		printf("Usage: %s <rows> <cols>/n", av[0]);
		return[1];
	}

	init(&f, ft_atoi(av[1]), ft_atoi(av[2]));

	while(1)
	{
		draw(&f);
		disp(&f);
		free(&f);
	}
}
