float Q_rsqrt(float num)
{
    float numHalf = num * 0.5F;
    
    int i = *(int *)&num;                   //floating point bit hack
    i = 0x5f3759df - (i >> 1);         //magic
    num = *(float *)&i;                  //back to float
    num = num * (1.5F - numHalf * num * num); //1st iter
    return num;
}

float Q_rsqrt2(float num)
{
    float numHalf = num * 0.5F;
    
    int i = *(int *)&num;                   //floating point bit hack
    i = 0x5f3759df - (i >> 1);         //magic
    num = *(float *)&i;                  //back to float
    num = num * (1.5F - numHalf * num * num); //1st iter
    num = num * (1.5F - numHalf * num * num); //2nd iter
    return num;
}
