
#ifndef IMAGE_H
# define IMAGE_H

typedef struct {
    int red;
    int green;
    int blue;
    int alpha;
} pixel_t;

typedef struct {
    int width;
    int height;
    pixel_t *image;
}   image_t;

typedef struct image_lst_s image_lst_t;
struct image_lst_s{
    image_t     *image;
    image_lst_t *next;
};

image_lst_t *load_mfa(int fd);
void free_image_lst(image_lst_t *images);

#endif
