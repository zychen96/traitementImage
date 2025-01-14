/**
 * @file padding.c
 * @brief zoom the input image @param ims by factor of @param f by using fourier transformation
 * @param ims the input image
 * @param f the zoom factor
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <bcl.h>
#include <string.h>
#include <stdbool.h>
#include <fft.h>

void usage(const char *s)
{
    fprintf(stderr, "Usage: %s <ims> \n", s);
    exit(EXIT_FAILURE);
}

void paddingChannel(int factor, pnm ims, pnm imd, int rows, int cols, int start_row, int end_row, int start_col, int end_col , int channel){
    int output_cols = cols*factor;
    int output_rows = rows*factor;
    int output_size = output_rows * output_cols;
    unsigned short * data = pnm_get_channel(ims,NULL,channel);
    fftw_complex *fft_ims = forward(rows, cols, data);
    fftw_complex *zoom_fft_ims = malloc(output_size * sizeof(fftw_complex));

    for (int i = 0; i < output_size; i++)
    {
        zoom_fft_ims[i] = 0;
    }

    int counter =0;
    for (int i = start_row; i <end_row; i++)
    {
        for (int j = start_col; j <end_col; j++)
        {
            zoom_fft_ims[i * output_cols + j] = fft_ims[counter];
            counter++;
        }
    }
    unsigned short *output_data = backward(output_rows, output_cols, zoom_fft_ims,factor);
    pnm_set_channel(imd, output_data, channel);
    free(fft_ims);
    free(zoom_fft_ims);
    free(data);
}

void process(int factor, pnm ims, char * filename)
{
    int rows = pnm_get_height(ims);
    int cols = pnm_get_width(ims);

    int output_rows = rows * factor;
    int output_cols = cols * factor;
    pnm imd = pnm_new(output_cols, output_rows, PnmRawPpm);
   
    int start_row = (output_rows - rows)%2 ==0 ? (output_rows - rows)/2 : (output_rows - rows)/2 + 1;
    int end_row = start_row + rows;
    int start_col = (output_cols - cols)%2 ==0 ? (output_cols - cols)/2 : (output_cols - cols)/2 + 1;
    int end_col = start_col + cols;
    for(int channel = PnmRed; channel<=PnmBlue;channel ++)
        paddingChannel(factor, ims, imd, rows, cols, start_row, end_row, start_col, end_col, channel);
    
    pnm_save(imd, PnmRawPpm, filename);
    pnm_free(imd);
    
    fftw_cleanup();
}

#define PARAM 3
int main(int argc, char *argv[])
{
    if (argc != PARAM + 1)
        usage(argv[0]);

    //load pnm images
    int factor = atoi(argv[1]);
    pnm ims = pnm_load(argv[2]);
    char * filename = argv[3];
    process(factor, ims, filename);

    pnm_free(ims);
    return EXIT_SUCCESS;
}
