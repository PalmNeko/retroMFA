
#include "utilities.h"
#include "mlx.h"

int view_mfa(t_param *param)
{
    mlx_window_t	mlx_win;
	t_data			img;

	mlx_win = mlx_new_window(param->vars->mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(param->vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	mlx_put_image_to_window(param->vars->mlx, mlx_win, img.img, 0, 0);
    param->vars->win = mlx_win;
    return (0);
}