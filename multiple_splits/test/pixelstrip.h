#ifndef PIXELSTRIP_H
# define PIXELSTRIP_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define STRIP_LEN 80
# define MAX_SPLITS 20

// RGB color structure
typedef struct s_color {
	int r;
	int g;
	int b;
} t_color;

// Pixel structure - holds accumulated color
typedef struct s_pixel {
	t_color color;
	int active;  // how many splits are touching this pixel
} t_pixel;

// Split point structure
typedef struct s_split {
	int position;      // center position of split
	int x;            // left-moving position
	int y;            // right-moving position
	t_color color;    // RGB color for this split
} t_split;

// Main data structure
typedef struct s_data {
	t_pixel pixels[STRIP_LEN];  // the display buffer
	t_split *splits;             // array of split points
	int num_splits;              // number of splits
	int cycles;                  // animation cycles
} t_data;

// Function prototypes
void	print_usage(void);
int		validate_and_parse(int ac, char *av[], t_data *d);
void	init_splits(t_data *d, char *av[]);
void	assign_colors(t_data *d);
void	clear_pixels(t_data *d);
void	update_splits(t_data *d);
void	render_pixels(t_data *d);
void	display(t_data *d);
void	cleanup(t_data *d);
t_color	mix_colors(t_color c1, t_color c2);

#endif
