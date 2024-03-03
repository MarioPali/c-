#include "horse.hpp"
#include <vector>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

void draw_race(vector <horse> &horses,int *positions,int rounds)
{
    const int size=horses.size();
    for(int i=0;i<size;i++)
    {
        cout<<"|";
        for(int j=1;j<=rounds;j++)
        {
            if(positions[i]==j)
            {
                cout<<i+1;
            }
            else
            {
                cout<<".";
            }
        }
        cout<<"|"<<endl;
    }
}

void press_any_key()
{
    cout<<"Press Any Key....";
    getchar();
    cout<<endl<<endl;
} // i sinartisi gia na patame koumpi gia na proxoraei o guros

int main()
{
    mt19937 mt(steady_clock::now().time_since_epoch().count());
    auto random_value_genarator=uniform_int_distribution<int>(50,100);
    vector <horse> horses;
    string horse_names[10]{"Blitz","Bolt","Goliath","Hercules","Rogue","Danger","Raider","Storm","Nitro","Hulk"};
    auto random_name_chooser=uniform_int_distribution<int>(0,9); // emfanizei me tuxea sira ta proiparxonta onomata
    int h=4;
    int rounds=10;
    for(int i=1;i<=h;i++)
    {
        int j=random_name_chooser(mt);
        int startup_speed=random_value_genarator(mt);
        int power=random_value_genarator(mt);
        int stamina=random_value_genarator(mt);
        horses.push_back(horse(i,horse_names[j],startup_speed,power,stamina));
    }

    int *positions=new int[h];
    for(int i=0;i<h;i++)
    {
        positions[i]=1;
    }
    const int max_steps=rounds * 2;
    draw_race(horses,positions,rounds); press_any_key();
    bool can_be_moved;
    auto mf=uniform_real_distribution<double>(0.0,100.0);
    for(int i=0;i<max_steps;i++)
    {
        for(int j=0,t=horses.size();j<t;j++)
        {
            can_be_moved=horses[j].move_forward(positions[j],mf(mt));
            if(can_be_moved && positions[j]!=rounds)
            {
                positions[j]++;
            }
        }
        draw_race(horses,positions,rounds);
        press_any_key();
    }
    delete[] positions;
    return EXIT_SUCCESS;
}