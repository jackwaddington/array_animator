#include "pixelstrip.h"

void	print_usage(void)
{
	printf("Usage: ./pixelstrip <split_pos1> <split_pos2> ... <cycles>\n");
	printf("----------------------------------------------------------------\n");
	printf("Split positions: 0-79 (at least 1 required)\n");
	printf("Cycles: number of animation cycles (0 = infinite)\n");
	printf("Example: ./pixelstrip 20 40 60 1000\n");
	printf("         (3 splits at positions 20, 40, 60, running 1000 cycles)\n");
}

int	validate_and_parse(int ac, char *av[], t_data *d)
{
	if (ac < 3)
	{
		printf("Error: Need at least 1 split position and cycle count.\n");
		return (0);
	}

	// Last argument is cycles
	d->cycles = atoi(av[ac - 1]);
	if (d->cycles < 0)
	{
		printf("Error: Cycles must be >= 0.\n");
		return (0);
	}

	// Everything else is split positions
	d->num_splits = ac - 2;  // exclude program name and cycles
	
	if (d->num_splits > MAX_SPLITS)
	{
		printf("Error: Maximum %d splits allowed.\n", MAX_SPLITS);
		return (0);
	}

	// Allocate splits array
	d->splits = malloc(sizeof(t_split) * d->num_splits);
	if (!d->splits)
	{
		printf("Error: Memory allocation failed.\n");
		return (0);
	}

	return (1);
}

void	init_splits(t_data *d, char *av[])
{
	int i;
	int pos;

	i = 0;
	while (i < d->num_splits)
	{
		pos = atoi(av[i + 1]);  // skip program name
		
		// Validate position
		if (pos < 0 || pos >= STRIP_LEN)
		{
			printf("Warning: Split position %d out of range (0-79), clamping.\n", pos);
			if (pos < 0)
				pos = 0;
			if (pos >= STRIP_LEN)
				pos = STRIP_LEN - 1;
		}
		
		d->splits[i].position = pos;
		d->splits[i].x = pos;
		d->splits[i].y = pos;
		i++;
	}
	
	printf("Initialized %d split(s) at positions: ", d->num_splits);
	i = 0;
	while (i < d->num_splits)
	{
		printf("%d ", d->splits[i].position);
		i++;
	}
	printf("\n");
}

void	assign_colors(t_data *d)
{
	// Predefined color palette for splits
	t_color colors[] = {
		{255, 0, 0},      // Red
		{0, 255, 0},      // Green
		{0, 0, 255},      // Blue
		{255, 255, 0},    // Yellow
		{255, 0, 255},    // Magenta
		{0, 255, 255},    // Cyan
		{255, 128, 0},    // Orange
		{128, 0, 255},    // Purple
		{0, 255, 128},    // Spring Green
		{255, 0, 128},    // Rose
		{128, 255, 0},    // Lime
		{0, 128, 255},    // Sky Blue
		{255, 128, 128},  // Light Red
		{128, 255, 128},  // Light Green
		{128, 128, 255},  // Light Blue
		{255, 255, 128},  // Light Yellow
		{255, 128, 255},  // Light Magenta
		{128, 255, 255},  // Light Cyan
		{192, 64, 0},     // Brown
		{64, 192, 192}    // Teal
	};
	int num_colors = 20;
	int i;

	i = 0;
	while (i < d->num_splits)
	{
		d->splits[i].color = colors[i % num_colors];
		i++;
	}
}

void	clear_pixels(t_data *d)
{
	int i;

	i = 0;
	while (i < STRIP_LEN)
	{
		d->pixels[i].color.r = 0;
		d->pixels[i].color.g = 0;
		d->pixels[i].color.b = 0;
		d->pixels[i].active = 0;
		i++;
	}
}

t_color	mix_colors(t_color c1, t_color c2)
{
	t_color result;

	// Additive color mixing (like light)
	result.r = c1.r + c2.r;
	result.g = c1.g + c2.g;
	result.b = c1.b + c2.b;

	// Clamp to 255
	if (result.r > 255) result.r = 255;
	if (result.g > 255) result.g = 255;
	if (result.b > 255) result.b = 255;

	return (result);
}

void	update_splits(t_data *d)
{
	int i;
	t_split *s;

	i = 0;
	while (i < d->num_splits)
	{
		s = &d->splits[i];

		// Draw left-moving character
		if (s->x >= 0 && s->x < STRIP_LEN)
		{
			if (d->pixels[s->x].active == 0)
				d->pixels[s->x].color = s->color;
			else
				d->pixels[s->x].color = mix_colors(d->pixels[s->x].color, s->color);
			d->pixels[s->x].active++;
		}

		// Draw right-moving character
		if (s->y >= 0 && s->y < STRIP_LEN)
		{
			if (d->pixels[s->y].active == 0)
				d->pixels[s->y].color = s->color;
			else
				d->pixels[s->y].color = mix_colors(d->pixels[s->y].color, s->color);
			d->pixels[s->y].active++;
		}

		// Draw center point
		if (s->position >= 0 && s->position < STRIP_LEN)
		{
			if (d->pixels[s->position].active == 0)
				d->pixels[s->position].color = s->color;
			else
				d->pixels[s->position].color = mix_colors(d->pixels[s->position].color, s->color);
			d->pixels[s->position].active++;
		}

		// Update positions
		s->x--;
		if (s->x < 0)
			s->x = s->position;

		s->y++;
		if (s->y >= STRIP_LEN)
			s->y = s->position;

		i++;
	}
}

void	render_pixels(t_data *d)
{
	int i;
	t_pixel *p;

	i = 0;
	while (i < STRIP_LEN)
	{
		p = &d->pixels[i];
		
		if (p->active > 0)
		{
			// ANSI color code: \033[38;2;R;G;Bm for RGB foreground color
			printf("\033[38;2;%d;%d;%dmX\033[0m", p->color.r, p->color.g, p->color.b);
		}
		else
		{
			printf(" ");
		}
		i++;
	}
}

void	display(t_data *d)
{
	// Move cursor to beginning of line
	printf("\n");
	render_pixels(d);
	fflush(stdout);
	usleep(50000);  // 50ms delay
}

void	cleanup(t_data *d)
{
	if (d->splits)
		free(d->splits);
}

int main(int ac, char *av[])
{
	t_data d;
	int cycle_count;

	if (ac < 3)
	{
		print_usage();
		return (1);
	}

	if (!validate_and_parse(ac, av, &d))
	{
		print_usage();
		return (1);
	}

	init_splits(&d, av);
	assign_colors(&d);

	if (d.cycles == 0)
	{
		printf("Running indefinitely. Press Ctrl+C to stop.\n");
		printf("\n");  // Make space for animation line
		cycle_count = 0;
		while (1)
		{
			clear_pixels(&d);
			update_splits(&d);
			display(&d);
			cycle_count++;
		}
	}
	else
	{
		printf("Running for %d cycles.\n", d.cycles);
		printf("\n");  // Make space for animation line
		cycle_count = d.cycles;
		while (cycle_count > 0)
		{
			clear_pixels(&d);
			update_splits(&d);
			display(&d);
			cycle_count--;
		}
	}

	printf("\n\nFinished.\n");
	cleanup(&d);
	return (0);
}
