#include<iostream>
//#include <vector>
using namespace std;

int n;
int partition(int *a,int l,int r);
void quicksort(int *a,int l,int r);

int main(){
    cin >> n;
    int arr[n];

    //vector<int>arr;
    //int num;
    //n=0;
    /**while(cin.peek()!='\n'){
        cin >> num;
        arr.push_back(num);
        n++;
    }**/
    for(int i =0;i<n;i++) cin >> arr[i];

    quicksort(arr,0,n-1);

    for(int i=n-1;i>=0;i--) cout << arr[i] <<" ";
    cout << endl;
    return 0;
}

void quicksort(int *a,int l,int r){
    if(l>=r) return;
    int q = partition(a, l, r);
    quicksort(a, l, q-1);
    quicksort(a, q+1, r);

}

int partition(int *a,int l,int r){
    int x=a[r];
    int i=l-1;
    for(int j=l;j<=r-1;j++){
        if(a[j]<=x) {
            i++;
            if(j!=i){
                int tmp = a[i];
                a[i] = a[j];
                a[j] = tmp;
            }
        }

    }
    i++;
    int tmp = a[i];
    a[i] = a[r];
    a[r] = tmp;
    return i;
}