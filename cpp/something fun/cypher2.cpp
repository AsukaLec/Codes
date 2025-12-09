#include <bits/stdc++.h>
using namespace std;
int main(){
    string a ="AJLPNYRJZJFLZYASGSKQGSMMEJKEJPFSVLPJLKKEJELNNSPZKYNNYGNSGASYZJGAKEYZYGASVWNJKSWSKECNLUJZKEJZEYCYZWSVOEKLGAHYKKJAZEJNYJZLKLGUESPPJLAFHSPZJLFSVGJRJPYTLOYGJALZMJJKJPZUESSGJPLUEYNATYOEKZLYNEJPKMSEVGAPJAKSGZGLTJEYZCLGYSNL";
    float n = a.length();
    float arr[26] = {0};
    for (int i =0;i<n;i++) arr[a[i]-65] +=1;
    for (int i =0;i<26;i++) cout<<fixed<<setprecision(2)<<arr[i]/n*100<<" ";
    cout<<endl;
    char a1 ='a';
    cout<<"   "<<a1;
    for (int i = 0; i< 25; i++){
        a1+=1;
        cout<<"    "<<a1;
    }

}
