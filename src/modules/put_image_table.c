#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "utilities.h"

int put_image(t_data *display, image_t *image, int x, int y);

int put_image_table(t_data *display, image_lst_t *images, int start_row)
{
    int offset_y = 10;
    int offset_x = 10;
    int max_img_height = 0;
    int row = 0;

    while (images != NULL) {
        if (offset_x + images->image->width > display->width) {
            if (row >= start_row)
                offset_y += max_img_height + 10;
            offset_x = 10;
            max_img_height = 0;
            row += 1;
        }
        if (offset_y + images->image->height > display->height)
            break;
        if (row >= start_row)
            put_image(display, images->image, offset_x, offset_y);
        if (images->image->height > max_img_height)
            max_img_height = images->image->height;
        offset_x += images->image->width + 10;
        images = images->next;
    }
    return (0);
}

int put_image(t_data *display, image_t *image, int x, int y)
{
    for (int img_y = 0; img_y < image->height; img_y++)
    {
        for (int img_x = 0; img_x < image->width; img_x++) {
            int index = img_y * image->width + img_x;
            pixel_t *pixel = &(image->image[index]);
            unsigned int color;
            color = 0xFF - (unsigned int)pixel->alpha;
            color <<= 8;
            color += pixel->red;
            color <<= 8;
            color += pixel->green;
            color <<= 8;
            color += pixel->blue;
            put_pixel(display, x + img_x, y + img_y, color);
        }
    }
    return (0);
}