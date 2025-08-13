#include<iostream>
using namespace std;

int n;
void mergesort(int *a,int l,int r);

int main(){
    cin >> n;
    int arr[n];
    for(int i =0;i<n;i++) cin >> arr[i];

    mergesort(arr, 0, n-1);

    for(int i=0;i<n;i++) cout << arr[i] <<" ";
    return 0;
}

 void mergesort(int *a,int l,int r){
    if(r-l<=1) return;

    int mid=l+(r-l)/2;
    mergesort(a, l, mid);
    mergesort(a,mid+1,r);

    int tmp[n];
    int i=l,j=mid+1,k=l;
    for(;i<= mid&&j<=r;){
        if(a[i]>=a[j]){
            tmp[k]=a[i];
            i++;
        }else{
            tmp[k]=a[j];
            j++;
        }
        k++;
    }

    if(i<=mid){
        while(i<=mid){
            tmp[k]=a[i];
            k++;
            i++;
        }
    }else{
        while(j<=r){
            tmp[k] = a[j];
            k++;
            j++;
        }
    }

    k=l;
    while(k<=r){
        a[k] = tmp[k];
        k++;
    }
    return;
 }