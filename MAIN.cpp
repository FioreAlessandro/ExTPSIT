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

\fn esegui
\brief Apre il file in scrittura e inserisce all'interno di esso i km e i vari dati degli atleti, inclusa la classifica finale
 */

void esegui()
{
    fstream fout("prova",ios::app);
    
    srand(time(NULL));
    
    Atleti atleta;
    
    string matricola;
    
    double distanza[atleta.numero_atleti];
    
    cout << "Quanti atleti ci sono in totale? "<<endl;
    cin>>atleta.numero_atleti;
    fout<<endl<<endl<<"Numero atleti: "<<atleta.numero_atleti<<endl<<endl;
   
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
        }
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
    
    fout<<"CLASSIFICA FINALE \n";
    
    int p=atleta.numero_atleti;
    for (int i = 0; i < atleta.numero_atleti; i++) 
    {
       fout<<p<<"° posto: "<<distanza[i]<<"\n";
       p--;
       atleta.km_tot = distanza[i];
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
    ofstream file("prova");
    if (file.is_open()) 
    {
        file.clear();
        file.close();
    }
    cout<<"File pulito \n ";
}

/*!
\fn leggi
 \brief Legge il file 
 */

void leggi()
{
     
    ifstream file("prova");
     
    string linea;
    if (file.is_open()) {
        while (getline(file, linea)) {
            cout << linea << endl;
        }
        file.close();
    } else {
        cout << "Impossibile aprire il file "<<endl;
    }
}

/*!
 \fn menu
 \brief Richiama i metodi del programma e offre 4 diverse scelte all'utente 
 */

void menu()
{
    int scelta;
    do{
        cout<<"\n-----MENU-----\n";
        cout<<"1)Inserisci dati atleti\n";
        cout<<"2)Leggi file\n";
        cout<<"3)Pulisci file\n";
        cout<<"4)Esci\n";
        cin>>scelta;

        switch(scelta)
        {
            case 1:
            esegui();
            break;
            
            case 2:
            leggi();
            break;
            
            case 3:
            pulisci();
            break;
            
            //default:
            //pulisci();
            
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

