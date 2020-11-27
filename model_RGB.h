long int model_rgb(unsigned char *img, size_t img_size, unsigned char *color_img, int channels, long int pixels)
{
    long int countR = 0, countG = 0, countB = 0;
    long int meanR = 0, meanG = 0, meanB = 0, fincountRGB = 0;

    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        countR += *p;
        countG += *(p + 1);
        countB += *(p + 2);
    }
    meanR = countR / pixels;
    meanG = countG / pixels;
    meanB = countB / pixels;

    // printf("Mean of R is : %d\n", meanR);
    // printf("Mean of G is : %d\n", meanG);
    // printf("Mean of B is : %d\n", meanB);
    
    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        if (*p > *(p + 1) && *p > *(p + 2) && *(p + 1) > *(p + 2)) // R>G>B
        {
            if (*p > meanR && *(p + 1) > meanG && *(p + 2) < meanB) // R> mean R
            {
                fincountRGB++;
            }
        }
    }

    return fincountRGB;
}