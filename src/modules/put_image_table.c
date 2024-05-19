
#include <stdlib.h>
#include "image.h"
#include "utilities.h"

int put_image_table(t_data *display, image_lst_t *images)
{
    (void)display;
    while (images != NULL) {
        // 画像を高さと幅を調整しながら描画する。
        images = images->next;
    }
    return (0);
}