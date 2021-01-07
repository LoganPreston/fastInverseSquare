#include <stdint.h>
#include <math.h>

float basicInverseSqrt(float num)
{
    return 1 / sqrt(num);
}

float Q_rsqrt_short(float num)
{
    int i = *(uint32_t *)&num; //floating point bit hack, use uint32_t or int, rather than long. Long takes time
    i = 0x5f375a86 - (i >> 1); //magic - change from 0x*9df to 0x*a86, per Christ Lomont study
    num = *(float *)&i;        //back to float

    return num;
}

float Q_rsqrt(float num)
{
    const float numHalf = num * 0.5F;
    const float threehalfs = 1.5F;

    int i = *(uint32_t *)&num;                        //floating point bit hack, use uint32_t or int, rather than long. Long takes time
    i = 0x5f375a86 - (i >> 1);                        //magic - change from 0x*9df to 0x*a86, per Christ Lomont study
    num = *(float *)&i;                               //back to float
    num = num * (threehalfs - (numHalf * num * num)); //1st iter
    return num;
}

float Q_rsqrt_two_iter(float num)
{
    const float numHalf = num * 0.5F;
    const float threehalfs = 1.5F;

    int i = *(uint32_t *)&num;                        //floating point bit hack, use uint32_t or int, rather than long. Long takes time
    i = 0x5f375a86 - (i >> 1);                        //magic - change from 0x*9df to 0x*a86, per Christ Lomont study
    num = *(float *)&i;                               //back to float
    num = num * (threehalfs - (numHalf * num * num)); //1st iter
    num = num * (threehalfs - (numHalf * num * num)); //2nd iter
    return num;
}

/*
original

float Q_rsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;                     //evil floating point bit hack
    i = 0x5f3759df - (i >> 1);           //what the fuck?
    y = y * (threehalfs - (x2 * y * y)); //1st iteration
    //y=y*(threehalfs-(x2*y*y));         //2nd iteration,this can be removed

    return y;
}
*/
