#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "image.h"

image_t *load_image(unsigned char *file_data, int width, int height, int type);

/**
 * NULL pointer 区切りのリスト
 */
image_lst_t *load_mfa(int fd)
{
    image_lst_t     *images;
    image_lst_t     *iter;
    unsigned char   *file_data;
    size_t          file_size;
    off_t           file_offset;
    ssize_t         read_len;

    // ファイルを全部読み込む
    file_offset = lseek(fd, 0, SEEK_END);
    if (file_offset == -1)
        return (NULL);
    file_size = file_offset;
    if (lseek(fd, 0, SEEK_SET) == -1)
        return (NULL);
    file_data = (unsigned char*)malloc(sizeof(unsigned char) * file_size);
    if (file_data == NULL)
        return (NULL);
    read_len = read(fd, file_data, file_size);
    if (read_len == -1)
        return (NULL);

    size_t index = 0;
    images = NULL;
    iter = NULL;
    image_lst_t *new_lst;
    int cnt = 0;
    (void)cnt;
    while (index + 4 < file_size) {
        new_lst = NULL;
        // 読み込み
        int type;

        type = -1;
        if (memcmp(file_data + index, (unsigned char []){0x04, 0x10, 0, 0}, 4) == 0)
            type = 0;
        else if (memcmp(file_data + index, (unsigned char []){0x06, 0x10, 0, 0}, 4) == 0)
            type = 1;
        if (type >= 0)
        {
            int width = 0;
            int height = 0;
            
            memcpy(&width, file_data + index - 4, 2);
            memcpy(&height, file_data + index - 2, 2);
            if (width > 0 && height > 0) {
                new_lst = (image_lst_t *)malloc(sizeof(image_lst_t));
                if (new_lst == NULL)
                    return (free(file_data), free_image_lst(images), NULL);
                new_lst->next = NULL;
                new_lst->image = load_image(file_data + index + 16, width, height, type);
                if (new_lst->image == NULL) {
                    free(new_lst);
                    free(file_data);
                    free_image_lst(images);
                    return (NULL);
                }
            }
        }
        if (new_lst != NULL) { // 追加
            if (images == NULL) {
                images = new_lst;
                iter = new_lst;
                // break;
            }
            else
            {
                iter->next = new_lst;
                iter = new_lst;
            }
        }
        index++;
    }
    free(file_data);
    return (images);
}

/**
 * file_data は 実際に画像データが入っている先頭ポインタを指し示すこと。
 * type =0 : 04
 * type != 0 : 06
 */
image_t *load_image(unsigned char *file_data, int width, int height, int type)
{
    image_t *image;
    int pad_len;
    int line_size;
    int pixel_size;

    if (type == 0)
        pixel_size = 3;
    else
        pixel_size = 2;


    pad_len = (2 - ((pixel_size * width) % 2)) % 2;
    line_size = pixel_size * width + pixel_size * pad_len;
    image = (image_t *)malloc(sizeof(image_t));
    if (image == NULL)
        return (NULL);
    image->image = (pixel_t *)malloc(sizeof(pixel_t) * (width * height));
    if (image->image == NULL)
        return (free(image), NULL);
    image->width = width;
    image->height = height;
    // BGRの読み込み
    for(int y = 0; y < height; y++) {
        unsigned char   *line_start = file_data + y *line_size;
        for (int x = 0; x < width; x++) {
            unsigned char *pixel_start;
            int index = (y * width + x);

            pixel_start = line_start + (pixel_size * x);
            if (type == 0) { // 4
                image->image[index].blue = *pixel_start;
                image->image[index].green = *(pixel_start + 1);
                image->image[index].red = *(pixel_start + 2);
            }
            else { // 6
                int value = 0;
                memcpy(&value, pixel_start, 2);
                image->image[index].red = 8 * (value % 32);
                value /= 32;
                image->image[index].green = 8 * (value % 32);
                value /= 32;
                image->image[index].blue = 8 * (value % 32);
            }
        }
    }
    file_data = file_data + (line_size * height);
    pad_len = (4 - width % 4) % 4;
    for(int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int data_index = y * (width + pad_len) + x;
            int index = y * width + x;

            unsigned char *pixel_start = file_data + data_index;
            image->image[index].alpha = *pixel_start;
        }
    }
    return image;
}