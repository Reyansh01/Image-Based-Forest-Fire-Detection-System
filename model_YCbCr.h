long int model_ycbcr(unsigned char *img, size_t img_size, unsigned char *color_img, int channels)
{
    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        //Y
        *pg = (uint8_t)fmin(0.2568 * *p + 0.5041 * *(p + 1) + 0.0979 * *(p + 2), 255.0);
        //Cb
        *(pg + 1) = (uint8_t)fmin(-0.1482 * *p - 0.2910 * *(p + 1) + 0.4392 * *(p + 2), 255.0);
        //Cr
        *(pg + 2) = (uint8_t)fmin(0.4392 * *p - 0.3678 * *(p + 1) - 0.0714 * *(p + 2), 255.0);
        if (channels == 4)
        {
            *(pg + 3) = *(p + 3);
        }
    }

    long int meanY = 0, meanCb = 0, meanCr = 0, countb = 0;
    long int countY = 0, countCb = 0, countCr = 0;
    long double Crstd, Crstdin;
    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        countY += *pg;
        countCb += *(pg + 1);
        countCr += *(pg + 2);
    }
    meanY = countY / pixels;
    meanCb = countCb / pixels;
    meanCr = countCr / pixels;
    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {
        Crstdin = pow((*(pg + 2) - meanCr),2);
        Crstd = pow(Crstdin/countb,1/2);
    }
    
    // printf("Mean of Y is : %d\n",meanY);
    // printf("Mean of Cb is : %d\n",meanCb);
    // printf("Mean of Cr is : %d\n",meanCr);
    
    long int fincountYCbCr = 0;
    for (unsigned char *p = img, *pg = color_img; p != img + img_size; p += channels, pg += channels)
    {   
        if (*pg >= *(pg + 1))
        {
            if (*pg >= meanY && *(pg + 1) >= meanCr)
            {
                if (*(pg + 1) >= *pg && *pg >= *(pg + 2) && *(pg + 1) >= *(pg + 2))
                {
                    if (*(pg + 2) <= 7.4*Crstd)
                    {
                        fincountYCbCr++;
                    }
                }
            }
        }
    }
    return fincountYCbCr;
}