/*
    C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder. 
    Dopo mezz'ora termina la registrazione.
    All'interno di un file sono elencati matricola, cognome e coordinate rilevate. 
    Realizzare un software in C++ che mi indichi il podio vincente, tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.
    
    (Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100)
*/

#include <iostream>
#include <ctime>
#include<cmath>

using namespace std;

struct Segmento {
    double x1, y1, x2, y2;
    double km;
};

double lunghezzaSegmento(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    
    //input numero atleti partecipanti
    srand(time(NULL));
    cout << "Quanti atleti ci sono in totale? "<<endl;
    int numero_atleti;
    cin>>numero_atleti;
    //generare dai 15 ai 30 segmenti con 4 coordinate per segmento(x1,y1  x2,y2)
    int numero_linee=rand()%16+15;
    int x1,y1,x2,y2;
    double km_tot=0;
   //creo vettore per la distanza e struct 
    Segmento segmenti[numero_linee];
    double distanza[numero_atleti];
    for(int a=0;a<numero_atleti;a++)
    {
        cout <<endl<<a+1<<"° Atleta"<<endl;
        km_tot=0;
        for (int i = 0; i < numero_linee; i++) 
        {
            segmenti[i].x1 = rand() % 100;
            segmenti[i].y1 = rand() % 100;
            segmenti[i].x2 = rand() % 100;
            segmenti[i].y2 = rand() % 100;
            segmenti[i].km = lunghezzaSegmento(segmenti[i].x1, segmenti[i].y1, segmenti[i].x2, segmenti[i].y2);
            km_tot = km_tot + segmenti[i].km;
            cout<<"Lunghezza totale "<<i+1<<"° linea "<< segmenti[i].km << endl;
        }
        cout <<endl<<"KM totali percorsi dal "<<a+1<<"° Atleta, sono: "<<km_tot<<endl;
        distanza[a]=km_tot;
    }
    
    //ordinamento del vettore
    for (int i = 0; i < numero_atleti-1; i++) {
        for (int j = 0; j < numero_atleti-i-1; j++) {
            if (distanza[j] > distanza[j+1]) 
            {
                int temp = distanza[j];
                distanza[j] = distanza[j+1];
                distanza[j+1] = temp;
            }
        }
    }
    
    for (int i = 0; i < numero_atleti; i++) 
    {
       cout<<distanza[i]<<" ";
    }
 
    
    return 0;
}
