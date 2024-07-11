#include "./include/grayConvolution.h"
#include <stdio.h>
#include <stdlib.h>

Kernel* createGaussianKernel(int size, float sigma) {
    // Allocate memory for the kernel
    Kernel* kernel = (Kernel*)malloc(sizeof(Kernel));
    kernel->sizeX = kernel->sizeY = size;
    kernel->data = (float*)malloc(size * size * sizeof(float));
    // Fill the kernel with the Gaussian function
    float sum = 0.0;
    int i, j;
    int half = size / 2;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            float x = i - half;
            float y = j - half;
            float value = exp(-(x*x + y*y) / (2 * sigma * sigma));
            kernel->data[i*size + j] = value;
            sum += value;
        }
    }
    // Normalice the kernel
    for (i = 0; i < size*size; i++) {
        kernel->data[i] /= sum;
    }
    return kernel;
}

Kernel* createLaplacianKernel() {
    // Allocate memory for the kernel
    Kernel* kernel = (Kernel*)malloc(sizeof(Kernel));
    kernel->sizeX = kernel->sizeY = 3;
    kernel->data = (float*)malloc(3 * 3 * sizeof(float));
    // Fill the kernel with the Laplacian function
    float laplacian[9] = {
        0,  1, 0,
        1, -4, 1,
        0,  1, 0
    };
    memcpy(kernel->data, laplacian, 9 * sizeof(float));
    return kernel;
}

void applyFilter(const Image* img, const Kernel* kernel, Image* out) {
    // Check if the input image and the output image are valid
    if (!img || !img->data || !kernel || !kernel->data || !out || !out->data) return;
    // Get the size of the kernel
    int size = kernel->sizeX;
    int half = size / 2;
    // Apply the filter
    int i, j, k, l;
    for (i = 0; i < img->height; i++) {
        for (j = 0; j < img->width; j++) {
            float sum = 0.0;
            for (k = 0; k < size; k++) {
                for (l = 0; l < size; l++) {
                    int x = j + k - half;
                    int y = i + l - half;
                    if (x >= 0 && x < img->width && y >= 0 && y < img->height) {
                        sum += img->data[y*img->width + x] * kernel->data[l*size + k];
                    }
                }
            }
            out->data[i*out->width + j] = (unsigned char)sum;
        }
    }
}


void freeImage(Image* img) {
    if (img) {
        (img->data) ? free(img->data) : free(img);
    }
}

void freeKernel(Kernel* kernel) {
    if (kernel) {
        (kernel->data) ? free(kernel->data) : free(kernel);
    }
}
