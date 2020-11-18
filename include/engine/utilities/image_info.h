#ifndef FROGGER_IMAGEINFO
#define FROGGER_IMAGEINFO
#pragma once

struct interface_texture typedef interface_texture_t;
struct interface_renderer typedef interface_renderer_t;

typedef struct image_info
{
    int width;
    int height;
    int comp;
    int length;
    //image pointer to loaded image in memory
    unsigned char *image;
    //image pointer to loaded image in gpu (shpuld not be here)
    interface_texture_t* texture;

}image_info_t;

//loads tecture into the gpu (should not be here)
void load_texture(image_info_t *img_info, interface_renderer_t *renderer);

//loads image from disk via stb_image (should not be here)
int load_image(image_info_t *img, const char* path);

#endif // !FROGGER_IMAGEINFO