/**
 * @brief Brief description of the struct or function.
 *
 * Detailed description of the struct or function.
 * You can provide more information here.
 *
 * @param paramName Description of the parameter.
 * @return Description of the return value.
 */

#ifndef GRAYCONVOLUTION_H
#define GRAYCONVOLUTION_H

#include <stdint.h>

#define MAX_UINT8 255
#define MIN_UINT8 0

#define MAX_UINT16 65535
#define MIN_UINT16 0

typedef struct {
    int width, height;
    unsigned char* data;
} Image;

typedef struct {
    int sizeX, sizeY;
    float* data;
} Kernel;

/**
 * @brief allocates memory for a kernel and fills it with the filter values
 * @param img input image
 * @param kernel kernel to apply
 * @param out output image
 */
void applyFilter(const Image* img, const Kernel* kernel, Image* out);

#endif 