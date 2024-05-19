
#include <stdlib.h>
#include "image.h"

void    free_image_lst(image_lst_t *images)
{
    image_lst_t *tmp;

    while (images != NULL)
    {
        tmp = images->next;
        free(images->image->image);
        free(images->image);
        free(images);
        images = tmp;
    }
    return ;
}
