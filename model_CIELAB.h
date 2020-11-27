long int model_cielab(unsigned char *img, size_t img_size, unsigned char *color_img, unsigned char *color_img_XYZ, int channels)
{
    for (unsigned char *p = img, *pglab = color_img, *pgXYZ = color_img_XYZ, *pgXXYYZZ = color_img_XYZ, *pgCIE = color_img_XYZ; p != img + img_size; p += channels, pglab += channels, pgXYZ += channels)
    {
        *pglab = (*p / 255);
        *(pglab + 1) = (*p / 255);
        *(pglab + 2) = (*p / 255);
        if (*pglab > 0.04045)
        {
            *pglab = pow(((*pglab + 0.055) / 1.055), 2.4);
        }
        else
        {
            *pglab = *pglab / 12.92;
        }
        if (*(pglab + 1) > 0.04045)
        {
            *(pglab + 1) = pow(((*(pglab + 1) + 0.055) / 1.055), 2.4);
        }
        else
        {
            *(pglab + 1) = *(pglab + 1) / 12.92;
        }
        if (*(pglab + 2) > 0.04045)
        {
            *(pglab + 2) = pow(((*(pglab + 2) + 0.055) / 1.055), 2.4);
        }
        else
        {
            *(pglab + 2) = *(pglab + 2) / 12.92;
        }
        *pglab = *pglab * 100;
        *(pglab + 1) = *(pglab + 1) * 100;
        *(pglab + 2) = *(pglab + 2) * 100;

        *pgXYZ = *pglab * 0.4124 + *(pglab + 1) * 0.3576 + *(pglab + 2) * 0.1805;
        *(pgXYZ + 1) = *pglab * 0.2126 + *(pglab + 1) * 0.7152 + *(pglab + 2) * 0.0722;
        *(pgXYZ + 2) = *pglab * 0.0193 + *(pglab + 1) * 0.1192 + *(pglab + 2) * 0.9505;

        *pgXXYYZZ = *pgXYZ / 95.047;
        *(pgXXYYZZ + 1) = *(pgXYZ + 1) / 100.0;
        *(pgXXYYZZ + 2) = *(pgXYZ + 2) / 108.883;

        if (*pgXXYYZZ > 0.008856)
        {
            *pgXXYYZZ = pow(*pgXXYYZZ, 1.3);
        }
        else
        {
            *pgXXYYZZ = (7.787 * *pgXXYYZZ) + (16 / 116);
        }
        if (*(pgXXYYZZ + 1) > 0.008856)
        {
            *(pgXXYYZZ + 1) = pow(*(pgXXYYZZ + 1), 1.3);
        }
        else
        {
            *(pgXXYYZZ + 1) = (7.787 * *(pgXXYYZZ + 1)) + (16 / 116);
        }
        if (*(pgXXYYZZ + 2) > 0.008856)
        {
            *(pgXXYYZZ + 2) = pow(*(pgXXYYZZ + 2), 1.3);
        }
        else
        {
            *(pgXXYYZZ + 2) = (7.787 * *(pgXXYYZZ + 2)) + (16 / 116);
        }

        *pgCIE = (116 * *pgXXYYZZ) - 16;
        *(pgCIE + 1) = 500 * (*pgXXYYZZ - *(pgXXYYZZ + 1));
        *(pgXXYYZZ + 2) = 200 * (*(pgXXYYZZ + 1) - *(pgXXYYZZ + 2));
    }

    long int fincountCIE = 0;
    long double countL = 0, countA = 0, countB = 0;
    long double meanL = 0, meanA = 0, meanB = 0;

    for (unsigned char *p = img, *pgCIE = color_img_XYZ; p != img + img_size; p += channels, pgCIE += channels)
    {
        countL += *pgCIE;
        countA += *(pgCIE + 1);
        countB += *(pgCIE + 2);
    }
    meanL = countL / pixels;
    meanA = countA / pixels;
    meanB = countB / pixels;

    for (unsigned char *p = img, *pgCIE = color_img_XYZ; p != img + img_size; p += channels, pgCIE += channels)
    {
        if (*pgCIE >= meanL)
        {
            if (*(pgCIE + 1) >= meanA)
            {
                if (*(pgCIE + 2) >= meanB)
                {
                    if (*(pgCIE + 2) >= *(pgCIE + 1))
                    {
                        fincountCIE++;
                    }
                }
            }
        }
    }
    return fincountCIE++;
}