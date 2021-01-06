float Q_rsqrt(float num)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = num * 0.5F;
    y = num;
    i = *(long *)&y;                   //floating point bit hack
    i = 0x5f3759df - (i >> 1);         //magic
    y = *(float *)&i;                  //back to float
    y = y * (threehalfs - x2 * y * y); //1st iter
    return y;
}

float Q_rsqrt2(float num)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = num * 0.5F;
    y = num;
    i = *(long *)&y;                   //floating point bit hack
    i = 0x5f3759df - (i >> 1);         //magic
    y = *(float *)&i;                  //back to float
    y = y * (threehalfs - x2 * y * y); //1st iter
    y = y * (threehalfs - x2 * y * y); //2nd iter
    return y;
}
