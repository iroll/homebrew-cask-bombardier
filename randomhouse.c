#include "bombardier.h"

void rh(unsigned int numofblocks, unsigned char min, unsigned char max, unsigned char houses[WIDTH], unsigned int *sum)
{
    int i;
    
    *sum=0;
    
    if (numofblocks>=max*WIDTH)
    {
	for (i=0;i<WIDTH;i++) houses[i]=max;
    }
    else if (numofblocks<=min*WIDTH)
    {
	for (i=0;i<WIDTH;i++) houses[i]=min;
    }
    else
    {
	int sum=0;
	int diff;
	
	for (i=0;i<WIDTH;i++)
	{
	    houses[i]=min+(int) ((float) (max+1)*rand()/(RAND_MAX+(float) min));
	    sum+=houses[i];
	}
	diff=sum-numofblocks;
	while (diff!=0)
	{
	    i=(int)((float) (WIDTH)*rand()/(RAND_MAX));
	    if (diff<0)
	    {
		if (houses[i]<max)
		{
		    houses[i]++;
		    diff++;
		}
	    }
	    else
	    {
		if (houses[i]>min)
		{
		    houses[i]--;
		    diff--;
		}
	    }
	}
    }
    for (i=0;i<WIDTH;i++) *sum=*sum+houses[i];
}
