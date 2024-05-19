#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "utilities.h"
#include "image.h"
#include "mlx.h"

int keypress_event(int keycode, t_vars *param);
int put_mfa(t_vars *param);

int view_mfa(t_vars *vars)
{
    mlx_window_t	mlx_win;
    image_lst_t     *images;
    int             fd = 0;
    char            *filename;

    vars->print_row = 0;
	mlx_win = mlx_new_window(vars->mlx, 1920, 1080, vars->argv[vars->index]);
    vars->win = mlx_win;
    vars->hasWindow = true;
    filename = vars->argv[vars->index];
    fd = open(filename, O_RDONLY);
    if (fd == -1)
        return (-1);
    images = load_mfa(fd);
    if (images == NULL && errno != 0)
        return (-1);
    vars->img_data = images;
    put_mfa(vars);
    mlx_hook(mlx_win, 2, 1L<<0, keypress_event, vars);
    close(fd);
    return (0);
}

int put_mfa(t_vars *vars) {

	t_data			img;

    if (vars->win == NULL)
        return (0);
    mlx_clear_window(vars->mlx, vars->win);
    img.width = 1920;
    img.height = 1080;
    img.img = mlx_new_image(vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    put_image_table(&img, vars->img_data, vars->print_row);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img, 0, 0);
    mlx_destroy_image(vars->mlx, img.img);
    return (0);
}

int keypress_event(int keycode, t_vars *param)
{
    if (keycode == KEY_W) {
        if (param->print_row > 0)
            param->print_row -= 1;
        put_mfa(param);
    }
    else if (keycode == KEY_S) {
        if (param->print_row < INT_MAX)
            param->print_row += 1;
        put_mfa(param);
    }
    return (0);
}
