#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "utilities.h"
#include "image.h"
#include <stdbool.h>

__attribute__((destructor))
static void destructor() {
    if (system("leaks -q retromfa > /dev/null") != 0)
		fprintf(stderr, "leaks!\n");
	return ;
}

int destroy(t_vars *vars)
{
	vars->win = NULL;
    free_image_lst(vars->img_data);
	vars->print_row = 0;
	vars->hasWindow = false;
	if (vars->index >= vars->argc)
		vars->exit = true;
	return(0);
}

int createWindow(t_vars *vars) {
	if (vars->hasWindow == true)
		return (0);
	if (view_mfa(vars) != 0)
	{
		if (vars->hasWindow == true)
			mlx_destroy_window(vars->mlx, vars->win);
		perror(NULL);
		exit(0);
	}
	mlx_hook(vars->win, ON_DESTROY, 0, destroy, vars);
	vars->hasWindow = true;
	vars->index += 1;
	return (0);
}

int will_exit(t_vars *vars) {
	if (vars->exit == true)
	{
		fflush(stdout);
		exit(0);
	}
	else {
		createWindow(vars);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	mlx_t	mlx;
	t_vars	vars;

	if (argc == 1)
		return (fprintf(stderr, "usage: %s mfafiles...\n", argv[0]), 0);
	mlx = mlx_init();
	if (mlx == NULL)
		return (fprintf(stderr, "failed mlx_init()\n"), 0);
	vars.mlx = mlx;
	vars.win = NULL;
	vars.exit = false;
	vars.index = 1;
	vars.argc = argc;
	vars.argv = argv;
	vars.img_data = NULL;
	vars.print_row = 0;
	vars.hasWindow = false;
	mlx_loop_hook(vars.mlx, will_exit, &vars);
	mlx_loop(mlx);
	return(0);
}
