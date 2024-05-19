#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "utilities.h"
#include <stdbool.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	close(int keycode, t_param *param)
{
	(void)keycode;
	mlx_destroy_window(param->vars->mlx, param->vars->win);
	return (0);
}

int destroy(t_param *param)
{
	(void)param->vars;
	param->vars->hasWindow = false;
	if (param->vars->index >= param->vars->argc)
		param->vars->exit = true;
	return(0);
}

int createWindow(t_param *param) {
	if (param->vars->hasWindow == true)
		return (0);
	view_mfa(param);
	mlx_hook(param->vars->win, ON_DESTROY, 0, destroy, param);
	param->vars->hasWindow = true;
	param->vars->index += 1;
	return (0);
}

int will_exit(t_param *param) {
	if (param->vars->exit == true)
	{
		system("leaks -q retromfa");
		printf("test\n");
		fflush(stdout);
		exit(0);
	}
	else {
		createWindow(param);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	mlx_t	mlx;
	t_vars	vars;
	t_param	param;

	mlx = mlx_init();
	vars.mlx = mlx;
	vars.win = NULL;
	vars.exit = false;
	vars.index = 0;
	vars.argc = argc;
	vars.argv = argv;
	vars.hasWindow = false;
	param.vars = &vars;
	mlx_loop_hook(vars.mlx, will_exit, &param);
	mlx_loop(mlx);
	return(0);
}
