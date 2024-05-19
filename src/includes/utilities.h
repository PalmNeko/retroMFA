
#ifndef UTILITIES_H
# define UTILITIES_H

# include "stdbool.h"

typedef void *mlx_t;
typedef void *mlx_window_t;

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct	s_vars {
	void	*mlx;
	void	*win;
	bool	exit;
	int		argc;
	char	**argv;
	int		index;
	bool	hasWindow;
}				t_vars;

typedef struct {
	t_vars *vars;
}	t_param;

int 	view_mfa(t_vars *param);
void	put_pixel(t_data *data, int x, int y, int color);

#endif
