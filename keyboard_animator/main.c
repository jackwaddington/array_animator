char *["1234567890-=];
char *["qwertyuiop[]"];
char *["zxcvbnm,./"];

typedef s_data{
	char	*keyboard[];
	int	row;
	int	pos;
} t_data;

int	is_key(int i, int j, t_data d)
{
	if(keyboard[i, j] = c)
	{
		d->row = i;
		d->pos = j;
		return 1;
	}
	return 0;
}

int	find_char(char c, char *keyboard, t_data d)
{
	int i = 0; // row
	int j = 0; // pos

	while(i < 3)
	{
		while(j < strlen(keyboard[i])
		{
			if(is_key(i, j, d)
				return;
			else
				i++;
			j++;
		}

		if (keyboard[i, j] == c){
			d->row = i;
			d->pos = j;
			i = 0;
			return;
		}
	}
}





int	main(int ac, char *av)
{
	int i;
	t_data d;

	while(av[i++])
	{
		check_pos(av[i++], d);
		disp.char(d);
	}
}




