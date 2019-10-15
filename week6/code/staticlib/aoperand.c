int max(int *a,int n)
{
	int max,i;
	max = a[0];
	for(i=1;i<n;i++)
	{
		if(a[i]>max)
		{
			max = a[i];
		}
	}
	
	return max;
}

int sum(int *a,int n)
{
	int sum=0,i;
	
	for(i=0;i<n;i++)
	{
		sum += a[i];
	}
	
	return sum;
}
