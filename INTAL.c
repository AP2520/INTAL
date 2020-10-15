#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "intal.h"

static void swap(char**, char**);
static void quickSort(char**, int, int);
static int partition(char**, int, int);
static int min(int, int);
static char* rem_zero(char*);
static char* reverse(char*, int);
static void destroy(char*);

static char* reverse(char *str, int n)
{
    char temp;
	for(int i=0;i<n/2;i++)
	{
		temp=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=temp;
	}
   	str[n]='\0';
	return str;
}

static char* rem_zero(char *str)
{
    int count = 0;
    int i;
    for(i=0; str[i]!='\0'; i++)
    {
        if(str[i] == '0')
            count++;
        else
            break;
    }
    if(strlen(str) == i)
    {
        char *temp = (char*)malloc(sizeof(char) * 2);
        strcpy(temp, "0");
        destroy(str);
        return temp;
    }
    else
    {
        char *temp = (char*)malloc(sizeof(char) * (strlen(str) - count + 1));
        int j = 0;
        for(i=count; str[i]!='\0'; i++)
            temp[j++] = str[i];
        temp[j] = '\0';
        destroy(str);
        return temp;
    }
}

static void destroy(char* a)
{
	if(a==NULL)
	{
		return;
	}
	else
	{
		free(a);
	}
}

static int min(int a, int b)
{
	if(a < b)
		return a;
	return b;
}

static void swap(char** a, char** b) 
{ 
   char* temp=*a;
   *a=*b;
   *b=temp;

}

static void quickSort(char** arr, int low, int high)
{

	if (low < high) 
    { 
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    }
}

static int partition(char** arr, int low, int high)
{
	char* pivot= (char*)malloc(sizeof(char)*1001);
    strcpy(pivot,arr[high]);
    
    int i = low - 1; 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (intal_compare(arr[j],pivot)==-1) 
        { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    destroy(pivot);
    return (i + 1);
}

int intal_compare(const char* intal1, const char* intal2)
{
	
	if(strlen(intal1) > strlen(intal2))
		return 1;
	else if(strlen(intal1) < strlen(intal2))
		return -1;
	for(int i=0; i<strlen(intal1); i++)
	{
		if(intal1[i] > intal2[i])
			return 1;
		if(intal1[i] < intal2[i])
			return -1;
	}
	
	return 0;
}

char* intal_add(const char* intal1, const char* intal2)
{
    if(intal1 == NULL || intal2 == NULL)
		return NULL;
	char *a = (char*)malloc(sizeof(char)*1001);
    char *b = (char*)malloc(sizeof(char)*1001);
    strcpy(a, intal1);
    strcpy(b, intal2);
    
    if(strcmp("0", a) == 0)
    {
        destroy(a);
        return b;
    }
    if(strcmp("0", b) == 0)
    {
        destroy(b);
        return a;
    }
    if(strlen(a) > strlen(b))
    {
        strcpy(a, intal2);
        strcpy(b, intal1);
    }
    
    int l1 = strlen(a);
    int l2 = strlen(b);
    char *res = (char*)malloc(sizeof(char) * (l2 + 2));
    
    int carry = 0;
    int i, sum=0, k=0;
    for(i = l1-1; i>=0; i--)
    {
        sum = (a[i] - '0') + b[i+l2-l1] - '0' + carry;
        res[k++] = '0' + (sum%10);
        
        carry = sum/10;
    }
    for(i = l2-l1-1; i>=0; i--)
    {
        sum = (b[i] - '0') + carry;
        res[k++] = '0' + (sum%10);
        carry = sum/10;
    }
    if(carry>0)
        res[k++] = '0' + carry;
    res[k] = '\0';
    res = reverse(res, strlen(res));
    destroy(a);
    destroy(b);
    return res;
}

int intal_max(char **arr, int n)
{
	int max = 0;
	for(int i=1; i<n; i++)
	{
		if(intal_compare(arr[i], arr[max]) == 1)
			max = i;
	}
	return max;
}

int intal_min(char **arr, int n)
{
	int min = 0;
	for(int i=1; i<n; i++)
	{
		if(intal_compare(arr[i], arr[min]) == -1)
			min = i;
	}
	return min;
}

char* intal_diff(const char* intal1, const char* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
	char *a = (char*)malloc(sizeof(char) * 1000);
	char *b = (char*)malloc(sizeof(char) * 1000);
	strcpy(a, intal1);
	strcpy(b, intal2);
	if(strcmp(a, "0") == 0)
	{
		destroy(a);
		return b;
	}		
	if(strcmp(b, "0") == 0)
	{
		destroy(b);
		return a;
	}	
	if(intal_compare(intal1, intal2) == -1)
	{
		strcpy(a, intal2);
		strcpy(b, intal1);
	}
	int l1 = strlen(a);
	int l2 = strlen(b);
	int d = l1 - l2;
	int carry = 0, k = 0,i;
	char *res = (char*)malloc(sizeof(char) * (l1+1));
	for(i = l2-1; i>=0; i--)
	{
		int sub = (a[i+d] - '0') - (b[i] - '0') - carry;
		if(sub < 0)
		{
			sub = sub + 10;
			carry = 1;
		}
		else
			carry = 0;
		res[k++] = sub + '0';
	}
	for(i = d-1; i>=0; i--)
	{
		if(a[i] == '0' && carry == 1)
		{
			res[k++] = '9';
			continue;
		}
		int sub = a[i] - '0' - carry;
		if(i>0 || sub>0)
			res[k++] = sub + '0';
		carry = 0;
	}
	res[k] = '\0';
	char *diff = (char*)malloc(sizeof(char) * (l1+1));
	diff = reverse(res, k);
	diff = rem_zero(diff);
	destroy(a);
	destroy(b);
	return diff;
}

char* intal_multiply(const char* intal1, const char* intal2)
{
	if(intal1==NULL || intal2==NULL)
		return NULL;
	if(strcmp("0", intal1) == 0 || strcmp("0", intal2) == 0)
	{
		char *ans = (char*)malloc(sizeof(char)*2);
		strcpy(ans, "0");
		return ans;
	}
	int l1 = strlen(intal1);
	int l2 = strlen(intal2);
	char *a = (char*)malloc(1001 * sizeof(char));
	char *b = (char*)malloc(1001 * sizeof(char));
	strcpy(a, intal1);
	strcpy(b, intal2);
	
	if(strcmp("1", a) == 0)
		return b;
	if(strcmp("1", b) == 0)
		return a;
	int l = l1 + l2;
	int r = l - 1;
	char *ans = malloc(sizeof(char) * (l + 1));
	int i, j, sum;
	for(i=0; i<l; i++)
		ans[i] = '0';
	ans[i] = '\0';
	for(i = l2-1; i>=0; i--)
	{
		int carry = 0;
		int offset = 0;
		for(j = l1-1; j>=0; j--)
		{
			sum = (a[j] - '0') * (b[i] - '0') + carry + (ans[r-offset] - '0');
			carry = sum/10;
			ans[r-offset] = sum%10 + '0';
			offset++;
		}
		if(carry > 0)
			ans[r-offset] = '0' + carry;
		r--;
	}
	ans = rem_zero(ans);
	destroy(a);
	destroy(b);
	return ans;
}

int intal_search(char **arr, int n, const char* key)
{
	int i=0;
	for(i=0; i<n; i++)
	{
		if(intal_compare(arr[i], key) == 0)
			return i;
		i++;
	}
	return -1;
}

char* intal_fibonacci(unsigned int n)
{
	char **dp = (char**)malloc(sizeof(char*) * (n+1));
	for(int i=0; i<=n; i++)
		*(dp + i) = (char*)malloc(sizeof(char) * 10000);
	strcpy(dp[0], "0");
	strcpy(dp[1], "1");
	for(int i=2; i<=n; i++)
		dp[i] = intal_add(dp[i-1], dp[i-2]);
		
	char* res = (char*)malloc((strlen(dp[n]) + 1) * sizeof(char));
  	strcpy(res, dp[n]);
  	
  	for(int i = 0; i < n + 1; ++i)
    	destroy(dp[i]);
  	free(dp);
  	return res;
}

char* intal_factorial(unsigned int n)
{
	char *one = (char*)malloc(sizeof(char) * 2);
	strcpy(one, "1");
	
	if(n < 2)
		return one;
		
	char **tbl = (char**)malloc(sizeof(char*) * (n+1));
	for(int i=0; i<=n; i++)
		tbl[i] = (char*)malloc(sizeof(char) * 10000);
	strcpy(tbl[0], "1");
	strcpy(tbl[1], "1");

	char *mul = (char*)malloc(sizeof(char) * 1000);
	for(int i=2; i<=n; i++)
	{
		sprintf(mul, "%d", i);
		tbl[i] = intal_multiply(tbl[i-1], mul);
	}
	destroy(mul);
	char* res = (char*)malloc((strlen(tbl[n]) + 1) * sizeof(char));
  	strcpy(res, tbl[n]);
  
	for(int i = 0; i < n + 1; i++)
		destroy(tbl[i]);
	free(tbl);
	return res;
}

char* intal_pow(const char* arr,unsigned int n)
{
    if(n==0)
    {
    	char *one = (char*)malloc(sizeof(char) * 2);
    	strcpy(one, "1");
        return one;
    }
    char* res=(char*)malloc(sizeof(char)*1001);
    strcpy(res,intal_pow(arr,n/2));
    strcpy(res,intal_multiply(res,res));
    if(n % 2 != 0)
        strcpy(res,intal_multiply(res,arr));
    return res;
}

char* intal_bincoeff(unsigned int n, unsigned int k)
{
	if(n == k || k == 0)
	{
		char *one = (char*)malloc(sizeof(char) * 2);
		strcpy(one, "1");
		return one;
	}
	char **dp = (char**)malloc(sizeof(char*) * (k+1));
	for(int i=0; i<=k; i++)
	{
		dp[i] = (char*)malloc(sizeof(char) * 1001);
		strcpy(dp[i], "0");
	}
	strcpy(dp[0], "1");
	for(int i=1; i<=n; i++)
	{
		for(int j = min(i, k); j>0; j--)
			dp[j] = intal_add(dp[j], dp[j - 1]);
	}
	char* res = (char*)malloc((strlen(dp[k]) + 1) * sizeof(char));
  	strcpy(res, dp[k]);
  
	for(int i = 0; i < k + 1; i++)
		destroy(dp[i]);
	free(dp);
	return res;
}

void intal_sort(char **arr, int n)
{
	if(arr==NULL || n==1)
		return;
	quickSort(arr,0,n-1);
}

int intal_binsearch(char **arr, int n, const char* key)
{
	int low = 0;
	int high = n-1;
	
	while(low <= high)
	{
		int mid = (low + high)/2;
		if(intal_compare(*(arr + mid), key) == 0)
			return mid;
		else if(intal_compare(*(arr + mid), key) == -1)
			low = mid + 1;
		else
			high = mid - 1;
	}	
	return -1;
}

char* coin_row_problem(char **arr, int n)
{	 	
  	char *curr = (char*)malloc(sizeof(char) * 1001);
  	if(n == 0)
  	{
  		strcpy(curr, "0");
  		return curr;
  	}
  	if(n == 1)
  	{
  		char *res = (char*)malloc(sizeof(char) * (strlen(arr[0]) + 1));
  		strcpy(res, arr[0]);
  		destroy(curr);
  		return res;
  	}
  	char *prev = (char*)malloc(sizeof(char) * 1001);
  	char *next = (char*)malloc(sizeof(char) * 1001);
  	char *temp = (char*)malloc(sizeof(char) * 1001);
  	strcpy(prev, "0");
  	strcpy(curr, arr[0]);
  	for(int i=2; i<=n; i++)
  	{
  		temp = intal_add(prev, arr[i-1]);
  		if(intal_compare(temp, curr) == 1)
  			strcpy(next, temp);
  		else
  			strcpy(next, curr);
  		strcpy(prev, curr);
  		strcpy(curr, next);
  	}
  	free(prev);
  	return curr;
}

char* intal_mod(const char* intal1, const char* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
	if(intal_compare(intal1, intal2) == -1)
	{
		char *res = (char*)malloc(sizeof(char) * 1001);
		strcpy(res, intal1);
		return res;
	}
	if(intal_compare(intal1, intal2) == 0)
	{
		char *zero = (char*)malloc(sizeof(char) * 2);
		strcpy(zero, "0");
		return zero;
	}
	char *a = (char*)malloc(sizeof(char) * 1001);
	char *b = (char*)malloc(sizeof(char) * 1001);
	strcpy(a, intal1);
	strcpy(b, intal2);
	char *temp = (char*)malloc(sizeof(char) * 1001);
	strcpy(temp, intal2);
	char *res = (char*)malloc(sizeof(char) * 1001);
	strcpy(res, intal1);
	while(intal_compare(res, temp) >= 0)
	{
		while(strlen(res) != strlen(temp))
			strcat(temp, "0");
		
		if(intal_compare(res, temp) == -1)
			temp[strlen(temp)-1] = '\0';
		
		res = intal_diff(res, temp);
		strcpy(temp, b);
	}
	
	destroy(a);
	destroy(b);
	destroy(temp);
	return res;
}

char* intal_gcd(const char* intal1, const char* intal2)
{
	char *a = (char*)malloc(sizeof(char) * 1001);	
	char *b = (char*)malloc(sizeof(char) * 1001);
	strcpy(a, intal1);
	strcpy(b, intal2);
	if(strcmp(a, "0") == 0)
	{
		destroy(a);
		return b;
	}
	char *temp = (char*)malloc(sizeof(char) * 1001);
	while(strcmp(b, "0") != 0)
	{
		temp = intal_mod(a, b);
		strcpy(a, b);
		strcpy(b, temp);
	}
	destroy(b);
	destroy(temp);
	return a;
}