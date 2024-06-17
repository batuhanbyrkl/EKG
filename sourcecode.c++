#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class EKG{
    private:
        string filename;
        vector<double> z1,z2,z3,v1,v2,v3;
        vector<int> tepe;
        string tas="",brad="",normal="";
    
    public:
        EKG(string isim):filename(isim){};
        void print();
        void vericek();
        void ritimbul(vector<int>&);
        int tepebul(vector<double>&);
        string aralikbul(int );
        void veriyaz();
};


void EKG::vericek(){
    ifstream fptr(filename.c_str(),ios::in);
    double voltage,time;
    vector<vector<double>> vtime(3), vvoltage(3);
    if(!fptr){
        cout << "File could not be opened \n";
        return;
    }

    while(fptr >> time >> voltage){
        int index=static_cast<int>(time)/5;
        vtime[index].push_back(time);
        vvoltage[index].push_back(voltage);
    }
    fptr.close();
    z1=vtime[0],z2=vtime[1],z3=vtime[2];
    v1=vvoltage[0],v2=vvoltage[1],v3=vvoltage[2];
    for (size_t i = 0; i < 3; i++)
    {
        tepe.push_back(tepebul(vvoltage[i]));
    }
    ritimbul(tepe);
    
}

int EKG::tepebul(vector<double> &v){
    int temp=0;
    for (size_t i = 0; i < v.size()-1; i++)
    {
        if (v[i]<=0.1 && v[i+1]>=0.1) temp++;
        
    }
    return 12*(temp/2);
    
}

void EKG::ritimbul(vector<int>& v){
    int max=v[0],min=v[0],maxindex=0,minindex=0;
    for (size_t i = 1; i < v.size(); i++)
    {
        if (v[i]>=max)
        {
            max=v[i];
            maxindex=i;
        }
        if (v[i]<=min)
        {
            min=v[i];
            minindex=i;
        }
    }

    int mid=2*(maxindex+minindex)%3;
    normal=aralikbul(mid);
    tas=aralikbul(maxindex);
    brad=aralikbul(minindex);
    print();
    veriyaz();
    
}

string EKG::aralikbul(int x){
    if(x==0) return "0-5 sn aralik";
    else if(x==1) return "5-10 sn aralik";
    else if(x==2) return "10-15 sn aralik";
}

void EKG::print(){
    cout << "tasikardi: "<< tas << endl;
    cout << "normal: " << normal << endl;
    cout << "bradicardi: " << brad << endl;
}

void EKG::veriyaz(){
    ofstream sptr("kisiliksonuc.txt",ios::out);

    if (!sptr)
    {
        cout << "File not opened \n";
    }

    else{
        sptr << "Tasikardi: " << tas << endl;
        sptr << "Bradicardi: " << brad << endl;
        sptr << "Normal: " << normal << endl; 
    }
    
}


int main() {
    EKG kisi1 = EKG("datas.txt");
    kisi1.vericek();
    return 0 ;
}




