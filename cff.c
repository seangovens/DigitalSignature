#include <stdio.h>
#include <stdlib.h>

int main() {
    
    return 0;
}



/* Taken from stack overflow http://stackoverflow.com/questions/24294192/computing-the-binomial-coefficient-in-c */
long long comb(int n,int k)
{
    long long ans=1;
    k=k>n-k?n-k:k;
    int j=1;
    for(;j<=k;j++,n--)
    {
        if(n%j==0)
        {
            ans*=n/j;
        }else
        if(ans%j==0)
        {
            ans=ans/j*n;
        }else
        {
            ans=(ans*n)/j;
        }
    }
    return ans;
}