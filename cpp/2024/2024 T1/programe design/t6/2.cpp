#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<string>
using namespace std;
class Stock
{
private:
//
    string symbol;
    string name;
    double previousClosingPrice;
    double currentPrice;

    
//
public:
    Stock()    {}    
    
    void Input()
    {
        cout<<"请输入股票代码：";cin>>this->symbol;
        cout<<"请输入股票名称：";cin>>this->name;
        cout<<"请输入今日股票价格：";cin>>this->currentPrice;
        cout<<"请输入昨日股票价格：";cin>>this->previousClosingPrice;
    }
    void Output()const
    {
        cout<<setw(16)<<"股票代码："<<setw(6)<<this->symbol;
        cout<<setw(16)<<"股票名称："<<setw(6)<<this->name;
        cout<<setw(16)<<"今日股票价格："<<setw(6)<<this->currentPrice;
        cout<<setw(16)<<"昨日股票价格："<<setw(6)<<this->previousClosingPrice;
        cout<<setw(16)<<"股票涨幅："<<setw(6)<<fixed<<setprecision(2)<<this->getChangePercent()<<"%"<<endl;
    }
    double getChangePercent() const
    {        
        return 100*(this->currentPrice-this->previousClosingPrice)/this->previousClosingPrice;
    }
    Stock(const string &s , const string &n , double p , double c)
    {
        this->symbol=s;
        this->name=n;
        this->previousClosingPrice=p;
        this->currentPrice=c;
    }
    
};



class StockExchange
{
private:
    string boursename;
    Stock  *pstock;
    int stockmax;
    short stocknum;

public:
//
    StockExchange(short n=10,const string &na="上海证券交易所") : stockmax(n),boursename(&na){};
//  

    StockExchange(short n,const string na)
    {
        this->boursename=na;
        this->pstock = new Stock[this->stockmax];
        if (!pstock)
        {
            cout << "内存分配失败，程序终止！" << endl;
            exit(-1);
        }    
    }
   
    short addStock()
    {
        if(this->stocknum<this->stockmax)
        {
            this->pstock[this->stocknum++].Input();
            return this->stocknum;
        }
        cout<<"内存不够，无法添加股票!"<<endl;
        return -1;
    }
    
    
    short addStock(const Stock&st)
    {//
       this->symbol=;
        cout<<"请输入股票名称：";cin>>this->name;
        cout<<"请输入今日股票价格：";cin>>this->currentPrice;
        cout<<"请输入昨日股票价格：";cin>>this->previousClosingPrice;





     //
        cout<<"内存不够，无法添加股票!"<<endl;
        return -1;
    }
    
    short getNumOfStock() const 
         { return this->stocknum; }
    
    void Output()const
    {
        cout<<this->boursename<<"欢迎您！本所股票数量："<<this->stocknum<<"   分别为："<<endl;
        for(int i(0);i<this->stocknum;i++){
            cout<<"股票代码："<<this->pstock->symbol<<" 股票名称："<<this->pstock->name<<"今日股票价格： "<<this->pstock->currentPrice<<"昨日股票价格： "<<this->pstock->previousClosingPrice<<" 股票涨幅： "<<this->pstock->getChangePercent;
    //股票代码：600000 股票名称：浦发银行今日股票价格： 19.67昨日股票价格： 17.83 股票涨幅： 10.32%



    //
        }
            

    }
};


int main()
{
    StockExchange shbourse(10);
    shbourse.addStock(Stock("600000","浦发银行",17.83,19.67));
    for(int i(0);i<2;i++)        
        shbourse.addStock();
    shbourse.Output();
    
    StockExchange szbourse(5,"深圳证券交易所");
    szbourse.addStock();
    szbourse.addStock(Stock("000001","中国平安",15.83,14.67));
    szbourse.Output();
    system("pause");
    return 0;
}