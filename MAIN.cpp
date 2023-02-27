/*
    C'è un software che registra a distanza di un minuto le coordinate (GPS) di un Kayt-Snowborder. 
    Dopo mezz'ora termina la registrazione.
    All'interno di un file sono elencati matricola, cognome e coordinate rilevate. 
    Realizzare un software in C++ che mi indichi il podio vincente, tenendo conto che vince chi ha fatto effettivamente una distanza maggiore.
    
    (Le coordinate vanno generate tenendo conto di un piano cartesiano da 0,0 a 100,100)
*/

/*!
\file Gara_Kyte-snowborder.cpp
\brief Programma che simula una gara di Kayt-Snowbording calcolando i km percorsi da ogni atleta e salvando i risultati su file
\author [Alessandro Fiore]
\version 1.0
\date 24/02/2023
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

/*!
\brief Calcola la lunghezza di un segmento dati i suoi punti
\param[in] x1 Ascissa del primo punto
\param[in] y1 Ordinata del primo punto
\param[in] x2 Ascissa del secondo punto
\param[in] y2 Ordinata del secondo punto
\return Lunghezza del segmento 
*/

double lunghezzaSegmento(double x1, double y1, double x2, double y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

/*!
\fn carica_vet
\brief Apre il file in lettura, lo legge fino alla fine e inserisce all'interno di un vettore di struct tutto ciò che legge dal file
\param[in]  vet_at vettore della struct Atleti
 */
 
void carica_vet(Atleti vet_at[])
{
    ifstream fin("partecipanti.txt",ios::in);
    string appoggio;
    while(!fin.eof())
    {
        getline(fin,appoggio);
        for(int i=0; i<5; i++)
        {
            fin>>vet_at[i].cognome>>vet_at[i].matricola;
        }
   
    }
    fin.close();
}

/*!
\fn leggi_csv
\brief Richima la funzione di caricamento del vettore e stampa i partecipanti
\param[in]  vet_at vettore della struct Atleti
 */

void leggi_csv(Atleti vet_at[])
{
    carica_vet(vet_at);
    cout<<"Hai simulato una gara di Kayt-Snowbording dei seguenti atleti \n";
    for(int i=0; i<5; i++)
    {
        cout<<vet_at[i].cognome<<" "<<vet_at[i].matricola<<endl;
    }
}

/*!
\fn leggi_csv_aggiornato
\brief Apre il file "prova.txt" in lettura e lo legge fino alla fine
\param[in]  vet_at vettore della struct Atleti
 */


void leggi_csv_aggiornato(Atleti vet_at[])
{
    cout<<"\nRISULTATI FINALI GARA KAYT-SNOWBORDING "<<endl;
    ifstream fin("prova.txt",ios::in);
    string appoggio;
    while(!fin.eof())
    {
        getline(fin,appoggio);
        cout<<appoggio<<endl;
   
    }
    fin.close();
}
/*!
\fn esegui
\brief Apre il file "prova.txt" in scrittura e inserisce all'interno di esso i dati degli atleti, le coordinate e i km totali, inclusa la classifica finale
\param[in]  vet_at vettore della struct Atleti
 */

void esegui(Atleti vet_at[])
{
    leggi_csv(vet_at);
    fstream fout("prova.txt",ios::app);
    fout<<"RISULTATI FINALI GARA KAYT-SNOWBORDING"<<endl;
    
    srand(time(NULL));
    
    Atleti atleta;
    
    string matricola;
    
    double distanza[5];
    
    for(int a=0;a<5;a++)
    {
        int numero_linee=rand()%26+5;
        int x1,y1,x2,y2,z;
        double km_tot=0;
        Segmento segmenti[numero_linee];
        
        fout<<endl<<vet_at[a].cognome<<" "<<vet_at[a].matricola<<endl;
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
        }
        fout<<"KM totali:"<<atleta.km_tot<<endl<<endl;
        distanza[a]=atleta.km_tot;
    }
   
    for (int i = 0; i < 5-1; i++) {
        for (int j = 0; j < 5-i-1; j++) {
            if (distanza[j] > distanza[j+1]) 
            {
              
                int temp = distanza[j];
                distanza[j] = distanza[j+1];
                distanza[j+1] = temp;
            }
        }
    }
    
    fout<<"CLASSIFICA FINALE \n";
    
    int p=5;
    for (int i = 0; i < 5; i++) 
    {
       if(p==3 || p==2 || p==1)
       {
           fout<<p<<"° posto: "<<distanza[i]<<"\n";
       }
       atleta.km_tot = distanza[i];
       p--;
    }
    
    fout<<"Il vincitore ha percorso: "<<atleta.km_tot<<"km\n";
    
    fout.close();
 
}

/*!
\fn pulisci
 \brief Pulisce il file riportandolo allo stato iniziale
 */

void pulisci()
{
    ofstream file("prova.txt");
    if (file.is_open()) 
    {
        file.clear();
        file.close();
    }
    cout<<"File pulito \n ";
}

/*!
 \fn menu
 \brief Richiama i metodi del programma e offre 3 diverse scelte all'utente 
 */

void menu()
{
    int scelta;
    Atleti vet_at[5];
    do{
        cout<<"\n-----MENU-----\n";
        cout<<"1)Simula gara\n";
        cout<<"2)Leggi file\n";
        cout<<"3)Pulisci file\n";
        cout<<"4)Esci\n";
        cin>>scelta;

        switch(scelta)
        {
            case 1:
            esegui(vet_at);
            break;
            
            case 2:
            leggi_csv_aggiornato(vet_at);
            break;
            
            case 3: 
            pulisci();
            break;
            
        }
    }while(scelta!=4);
}

//! \fn main 
//! \brief metodo finale in cui viene richiamato solo il menu
int main()
{
    menu();
    
	return 0;
}
