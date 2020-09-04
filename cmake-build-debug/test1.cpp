#include<iostream>
#include<string>
#include<unistd.h>
int a[100000005];
int main(){
    for(int i=0;i<100000000;i++){
        a[i]=i;
        a[i+1]=a[i]+1;
        short ;
    }
    std::cout<<a[5000]<<"\n";
    std::cout<<"Hello world"<<"\n";
    return 0;
}
