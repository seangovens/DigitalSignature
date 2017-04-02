int * cff_encode(char * mess, size_t len_m, int e, int k) {
    mpz_t m;
    mpz_init(m);
    mpz_import(m, len_m, 1, sizeof(mess[0]), 0, 0, mess);
    int a[k];
    
    for (int i = 0, q = 0; i < k; i++) {
        long long choose = comb(e - q, k - i);
        while (mpz_cmp_si(m, choose) {
            mpz_sub_ui(m, m, choose);
            q++;
        }
        a[i] = q;
        q++;
    }
    
    return a;
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