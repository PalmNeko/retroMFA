#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include "utilities.h"
#include "image.h"
#include "mlx.h"

int view_mfa(t_vars *vars)
{
    mlx_window_t	mlx_win;
	t_data			img;
    // image_lst_t     *images;
    // int             fd = 0;

	mlx_win = mlx_new_window(vars->mlx, 1920, 1080, "Hello world!");
    img.width = 1920;
    img.height = 1080;
	img.img = mlx_new_image(vars->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    // // ファイルを開く TODO:
    // images = load_mfa(fd);
    // if (images == NULL && errno != 0)
    //     ;// destroy window and image.
    // put_image_table(&img, images);
    // free_image_lst(images);
	mlx_put_image_to_window(vars->mlx, mlx_win, img.img, 0, 0);
    // mlx_destroy_image(vars->mlx, img.img);
    // ファイルを閉じる TODO:
    // close(fd);
    vars->win = mlx_win;
    return (0);
}