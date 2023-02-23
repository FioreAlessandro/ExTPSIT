/*
    C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder. 
    Dopo mezz'ora termina la registrazione.
    All'interno di un file sono elencati matricola, cognome e coordinate rilevate. 
    Realizzare un software in C++ che mi indichi il podio vincente, tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.
    
    (Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100)
*/

/**

@file main.cpp
@brief Simula una gara di atletica leggera calcolando i km percorsi da ogni atleta e salvando i risultati su file
@author [Alessandro Fiore]

*/

#include <iostream>
#include <ctime>
#include<cmath>
#include <fstream>

using namespace std;

/**

@struct Segmento
@brief Definisce una struttura Segmento contenente le coordinate di due punti e la loro lunghezza in km
*/

struct Segmento {
    double x1, y1, x2, y2;
    double km;
};

/**

@struct Atleti
@brief Definisce una struttura Atleti contenente il numero degli atleti, la loro matricola, il cognome e i km percorsi
*/

struct Atleti {
    int numero_atleti;
    string matricola;
    string cognome;
    int km_tot;
};

/**

@brief Calcola la lunghezza di un segmento dati i suoi punti
@param x1 Ascissa del primo punto
@param y1 Ordinata del primo punto
@param x2 Ascissa del secondo punto
@param y2 Ordinata del secondo punto
@return Lunghezza del segmento in km
*/

double lunghezzaSegmento(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main()
{
    fstream fout("prova",ios::app);
    
    srand(time(NULL));
    cout << "Quanti atleti ci sono in totale? "<<endl;
    Atleti atleta;
    cin>>atleta.numero_atleti;
    fout<<endl<<endl<<"Numero atleti: "<<atleta.numero_atleti<<endl<<endl;
    
    string matricola;
    double distanza[atleta.numero_atleti];
    for(int a=0;a<atleta.numero_atleti;a++)
    {
        int numero_linee=rand()%26+5;
        int x1,y1,x2,y2,z;
        double km_tot=0;
   
        Segmento segmenti[numero_linee];
        
        for(int aa=0;aa<5;aa++)
        {
            int num = rand() % 26; 
            char carattere = 'a' + num;
            matricola+=carattere;
        }
        
        atleta.matricola = matricola;
        matricola = " ";
        fout<<"Matricola: "<<atleta.matricola<<endl;
        cout <<endl<<a+1<<"° Atleta"<<endl;
        cout <<"Inserisci cognome atleta: ";
        cin>>atleta.cognome;
        fout<<"Cognome: "<<atleta.cognome<<endl;
        fout<<"Coordinate rilevate in 30 minuti di gara\n";
        atleta.km_tot=0;
        for (int i = 0; i < numero_linee; i++) 
        {
            segmenti[i].x1 = rand() % 100;
            segmenti[i].y1 = rand() % 100;
            segmenti[i].x2 = rand() % 100;
            segmenti[i].y2 = rand() % 100;
            fout<<segmenti[i].x1<<" "<<segmenti[i].y1<<" "<<segmenti[i].x2<<" "<<segmenti[i].y2<<"\n";
            segmenti[i].km = lunghezzaSegmento(segmenti[i].x1, segmenti[i].y1, segmenti[i].x2, segmenti[i].y2);
            atleta.km_tot = atleta.km_tot + segmenti[i].km;
            cout<<"Lunghezza totale "<<i+1<<"° linea "<< segmenti[i].km << endl;
        }
        cout <<endl<<"KM totali percorsi dal "<<a+1<<"° Atleta ("<<atleta.cognome<<"), sono: "<<atleta.km_tot<<endl;
        fout<<"KM totali:"<<atleta.km_tot<<endl<<endl;
        distanza[a]=atleta.km_tot;
    }
   
   
   
    for (int i = 0; i < atleta.numero_atleti-1; i++) {
        for (int j = 0; j < atleta.numero_atleti-i-1; j++) {
            if (distanza[j] > distanza[j+1]) 
            {
                int temp = distanza[j];
                distanza[j] = distanza[j+1];
                distanza[j+1] = temp;
            }
        }
    }
    
    cout <<endl<<"I km percorsi in ordine crescente dagli altleti sono: "<<endl;
    fout<<"CLASSIFICA FINALE \n";
    int p=atleta.numero_atleti;
    for (int i = 0; i < atleta.numero_atleti; i++) 
    {
       cout<<distanza[i]<<" ";
       fout<<p<<"° posto: "<<distanza[i]<<"\n";
       p--;
       atleta.km_tot = distanza[i];
    }
    
    fout<<"Il vincitore ha percorso: "<<atleta.km_tot<<"km\n";
    
    fout.close();
 
    
    return 0;
}
