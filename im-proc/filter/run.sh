#!/bin/sh
# ./heat-equation 10 ../data/barbara.ppm heat-10.ppm
# ./heat-equation 50 ../data/barbara.ppm heat-50.ppm
# ./heat-equation 100 ../data/barbara.ppm heat-100.ppm
# valgrind ./heat-equation 100 ../data/barbara.ppm heat-100.ppm

# ./anisotropic-diffusion 100 10 0 ../data/barbara.ppm anisotropic-100-10-0.ppm
# ./anisotropic-diffusion 100 10 1 ../data/barbara.ppm anisotropic-100-10-1.ppm
# ./anisotropic-diffusion 100 10 2 ../data/barbara.ppm anisotropic-100-10-2.ppm
# valgrind ./anisotropic-diffusion 100 10 2 ../data/barbara.ppm anisotropic-100-10-2.ppm

# ./median 1 ../data/barbara-impulse.ppm median-1.ppm
# ./median 2 ../data/barbara-impulse.ppm median-2.ppm
# ./median 3 ../data/barbara-impulse.ppm median-3.ppm
# valgrind ./median 3 ../data/barbara-impulse.ppm median-3.ppm


# ./bilateral 3 30 ../data/barbara.ppm bilateral-3-30.ppm
# ./bilateral 3 100 ../data/barbara.ppm bilateral-3-100.ppm
# ./bilateral 10 30 ../data/barbara.ppm bilateral-10-30.ppm
# ./bilateral 10 100 ../data/barbara.ppm bilateral-10-100.ppm
# valgrind ./bilateral 10 100 ../data/barbara.ppm bilateral-10-100.ppm

# ./nlmeans 5 ../data/barbara.ppm nlmeans-5.ppm
# ./nlmeans 10 ../data/barbara.ppm nlmeans-10.ppm
./nlmeans 10 ../data/barbara-gaussian-10.ppm nlmeans-gau10-10.ppm

# ./butterworth ../data/lena-gray.ppm lp.ppm lp 32 2 0 0 0
# ./butterworth ../data/lena-gray.ppm hp.ppm hp 32 2 0 0 0
# ./butterworth ../data/lena-gray.ppm br.ppm br 128 2 64 0 0
# ./butterworth ../data/lena-gray.ppm bp.ppm bp 64 2 64 0 0
# ./butterworth ../data/lena-sin.ppm no.ppm no 1 2 0 0 8
# valgrind --leak-check=full --show-leak-kinds=all ./butterworth ../data/lena-sin.ppm no.ppm no 1 2 0 0 8
pvisu *.ppm