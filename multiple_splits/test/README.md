# PixelStrip - Animated Color Mixer

A C program that creates an animated 80-pixel strip with color-mixing effects using ANSI terminal colors.

## Features

- **Fixed 80-pixel display** - Always displays exactly 80 characters
- **Multiple split points** - Define 1-20 split points via command-line arguments
- **RGB color system** - Each split gets a unique color from a predefined palette
- **Additive color mixing** - When pixels from different splits overlap, colors mix like light:
  - Red + Green = Yellow
  - Green + Blue = Cyan
  - Red + Blue = Magenta
  - Red + Green + Blue = White
- **Walking animation** - Each split sends 'X' characters walking left and right from its position

## Compilation

```bash
make        # Compile the project
make clean  # Remove object files
make fclean # Remove object files and executable
make re     # Rebuild from scratch
```

## Usage

```bash
./pixelstrip <split_pos1> [split_pos2] [split_pos3] ... <cycles>
```

### Arguments

- **split_pos1, split_pos2, etc.** - Position(s) of split points (0-79)
  - Must provide at least 1 split position
  - Maximum 20 splits allowed
- **cycles** - Number of animation cycles
  - Use `0` for infinite loop (press Ctrl+C to stop)
  - Any positive number for that many cycles

### Examples

**Single split at position 40, run for 100 cycles:**
```bash
./pixelstrip 40 100
```

**Three splits at positions 20, 40, and 60, run indefinitely:**
```bash
./pixelstrip 20 40 60 0
```

**Five splits for 500 cycles:**
```bash
./pixelstrip 10 25 40 55 70 500
```

## How It Works

1. **Initialization**: Each split point is assigned:
   - A position on the 80-pixel strip
   - An RGB color from the palette
   - Two walking positions (x goes left, y goes right)

2. **Animation Loop**:
   - Clear the pixel buffer
   - For each split, draw 'X' at its current positions
   - Mix colors when multiple splits occupy the same pixel
   - Update positions (x moves left, y moves right)
   - Reset to center when reaching strip boundaries

3. **Rendering**:
   - Active pixels display as colored 'X'
   - Inactive pixels display as '-'
   - Uses ANSI escape codes for RGB colors

## Technical Details

### Structures

```c
typedef struct s_color {
    int r, g, b;  // RGB values (0-255)
} t_color;

typedef struct s_split {
    int position;   // Center position
    int x, y;       // Left and right walking positions
    t_color color;  // RGB color
} t_split;

typedef struct s_pixel {
    t_color color;  // Accumulated color
    int active;     // Number of splits touching this pixel
} t_pixel;
```

### Color Palette

The program includes 20 predefined colors:
- Primary: Red, Green, Blue
- Secondary: Yellow, Magenta, Cyan
- Tertiary: Orange, Purple, Spring Green, Rose, Lime, Sky Blue
- Light variants of primary and secondary colors
- Additional: Brown, Teal

## Requirements

- GCC compiler
- Terminal with ANSI color support (most modern terminals)
- Unix-like environment (Linux, macOS)

## Notes

- The animation uses `usleep(50000)` for 50ms delay between frames
- Colors are mixed additively (like light, not paint)
- The display uses `\r` (carriage return) to update in place
- All 80 positions are always rendered (active pixels as 'X', inactive as '-')

## Project Structure

```
.
├── Makefile          # Build configuration
├── pixelstrip.h      # Header with structures and prototypes
├── pixelstrip.c      # Main implementation
└── README.md         # This file
```

## Author

Created as a coding challenge to explore:
- Dynamic memory allocation
- Color theory and mixing
- ANSI terminal graphics
- Multi-object state management in C
