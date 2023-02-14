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
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
}

int main()
{
    //generare dai 15 ai 30 segmenti con 4 coordinate per segmento(x1,y1  x2,y2)
    srand(time(NULL));
    int numero_atleti = rand()%8+2;
    cout << "Ci sono in totale: "<<numero_atleti<<" atleti"<<endl;
    int numero_linee=rand()%16+15;
    int numero_linee_tot = numero_atleti*numero_linee;
    int x1,y1,x2,y2;
    double km_tot=0;
  
    Segmento segmenti[numero_linee];
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
        
        cout <<endl<<"KM totali percorsi dal "<<a+1<<"° Atleta, sono: "<<km_tot<<endl;
        
        cout <<endl<<"KM totali percorsi dal "<<a+1<<"° Atleta, sono: "<<km_tot<<endl;
    }
    
    
    
    
    
    
    
    
    return 0;
}
