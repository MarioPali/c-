#include "racing.hpp"
#define DNF 1000

mt19937 mt(chrono::steady_clock::now().time_since_epoch().count()); // global dld gia olo ton kwdika


void press_enter()
{
    cout<<"Press [Enter] to continue....";
    cin.get();
}


Racing::Racing(int number_of_horses,int number_of_rounds):n_horses(number_of_horses),rounds(number_of_rounds)
{
    if(n_horses>10)
    {
        cout<<"You need to insert less number of horses than 10!!!!!!"<<endl; // thetoume oria gia tous gurous kai ta aloga etsi wste na min kseperastoun ta oria pou einai 10 aloga kai 20 guroi toulaxiston
        exit(EXIT_FAILURE);
    }
    if(rounds>20)
    {
        cout<<"You need to insert less number of rounds than 20!!!!"<<endl;
        exit(EXIT_FAILURE);
    }
    auto random_value=uniform_int_distribution<int>(50,100);
    vector <string> names{"Blitz","Bolt","Goliath","Hercules","Rogue","Danger","Raider","Storm","Nitro","Hulk"};
    shuffle(names.begin(),names.end(),default_random_engine(chrono::steady_clock::now().time_since_epoch().count()));
    for(int i=0;i<this->n_horses;i++)
    {
        horse a_horse(i+1,names[i],random_value(mt),random_value(mt),random_value(mt));
        horses.push_back(a_horse);
        position.push_back(0); // me tin entoli .push_back() eisagw stoixeia ston pinaka
        standings.push_back(make_pair(a_horse,DNF));
        
    }


}

Racing::~Racing() {}
 
void Racing::race() //i sinartis auti proxoraei ta aloga ston epomeno guro i ta afinei stin idia thesi simfona me tin move_forward
{
    mt19937 gen(steady_clock::now().time_since_epoch().count());
    const int steps_will_be_made=this->rounds * 2;
    auto rand_real=uniform_real_distribution<double>(0,100);
    bool can_be_moved;
    this->drawing();
    press_enter();
    int rank=1; // o parakw kwdikas vazei se seira tis theseis twn alogwn analoga me tin seira pou termatisan.Episis an ena alogo den exei termatisi mesa sto orio twn girwn emfanizei to analogo minina DNF
    for(int i=0;i<steps_will_be_made;i++)
    {
        for(int j=0;j<this->horses.size();j++)
        {
            if(this->position[j]==this->rounds-1)
            {
                if(this->standings[j].second==DNF) 
                {
                    this->standings[j].second=rank;
                    rank++;
                }
                continue;
            }
            can_be_moved=this->horses[j].move_forward(this->position[j],rand_real(gen));
            if(can_be_moved)
            {
                this->position[j]++;
            }
        }
        this->drawing();//sxediasmos koursas meta apo kathe guro
        press_enter();
        
        
    }
}


void Racing::display_horses() // i sinartisi auti emfanizei ta aloga
        {
            for(int i=0;i<this->horses.size();i++)
            {
                this->horses[i].print();
            }
            cout<<endl;
        }

void Racing::drawing() // i sinartisi auti emfanizei ton agwna
{
    for(int i=0;i<this->horses.size();i++)
    {
        cout<<"|";
        for(int j=0;j<this->rounds;j++)
        {
            if(position[i]==j)
            {
                cout<<i;
            }
            else
                cout<<".";
        }
        cout<<"|"<<endl;
    }
}


void Racing::display_standings() // i sinartisi auti emfanizei ta apotelesmata tou agwna
{
    cout<<"------- RESULTS OF GAME --------"<<endl;
    auto i=0;
    sort(this->standings.begin(),this->standings.end(),[](pair<horse,int> &p1,pair <horse,int>&p2)
    {return p1.second<p2.second;});
    //taksinomisi twn thesews ton alogwn 
    for(int i=0;i<this->standings.size();i++)
    {
        cout<<this->standings[i].first.get_name()<<"->"<<(this->standings[i].second==DNF?"Did Not Finish The Race":to_string(this->standings[i].second))<<endl;
    } // to erwtimatiko litourgi san or etsi wste ama ena alogo den termatisi ton agona na emafanisi to parapanw minima kai tin thesi pou termatise dld to DNF
    cout<<endl;
} 