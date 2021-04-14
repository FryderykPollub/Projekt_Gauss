#include<iostream>
#include<math.h>
#include<fstream>

using namespace std;
bool czyDane; //zmienna logiczna sprawdzaj¹ca czy wczytano dane z pliku
int rozmiarTab; //zmienna ca³kowita przechowuj¹ca rozmiar wczytanej tablicy

void bezWyboru(int opcja, double **tab, int r) //funkcja do podpunktu 2
{
    double **tablica;
    double pom;

    if(opcja==1){
        tablica=new double*[r];
        for(int i=0; i<r; i++){
            tablica[i]= new double[r+1];
        }
        for(int i=0; i<r; i++){
            tablica[i]=new double[r+1];
            for(int j=0; j<=r; j++){
                tablica[i][j]=tab[i][j];
            }
        }
    }
    else{
        cout<<"Wprowadz ilosc wierszy: ";
        cin>>r;
        cout<<"Wprowadz wspolczynniki: ";
        tablica=new double*[r];
        for(int i=0; i<r; i++){
            tablica[i]=new double[r+1];
            for(int j=0; j<=r; j++){
                cin>>tablica[i][j];
            }
            cout<<endl;
        }
    }

    for(int i=0; i<r-1; i++){
        if(fabs(tablica[i][i])>1e-7){
            for(int j=i+1; j<r; j++){
                pom=tablica[j][i]/tablica[i][i];
                for(int k=0; k<=r; k++){
                    tablica[j][k]-=pom*tablica[i][k];
                }
            }
        }
    }

    double tabwynik[r];
    for(int i=r-1; i>=0; i--){
        double x=tablica[i][r];
        if(fabs(tablica[i][i])>1e-7){
            for(int j=r-1; j>i; j--){
                x=x-(tablica[i][j]*tabwynik[j]);
            }
            tabwynik[i]=x/tablica[i][i];
        }
    }

    cout<<"\t\tWYNIK"<<endl;
    for(int i=0; i<r; i++){
            cout<<"x"<<i+1<<"= "<<tabwynik[i]<<endl;
        }

    delete []tablica;
}

double **wczytZpliku() //funkcja wczytująca dane z pliku
{
    double** A;
    double* b;
    unsigned matrix_size;
    ifstream source_file("dane.csv");
    if (!source_file.is_open())
    {
        cout <<"Nie da sie otworzyc pliku"<<endl;
        czyDane=false;
    }

    else{
    czyDane=true;

    source_file >> matrix_size;

    A = new double*[matrix_size];
    A[0] = new double[matrix_size*(matrix_size+1)];
    for(unsigned i = 1; i< matrix_size; i++)
        A[i] = A[i-1] + matrix_size;

    b = new double[matrix_size];

    char semicolumn;
    for (unsigned i = 0; i < matrix_size+1; i++)
        source_file >> semicolumn;

    for (unsigned i = 0; i < matrix_size; i++)
    {
        for (unsigned j = 0; j < matrix_size; j++)
        {
            source_file >> A[i][j];
            source_file >> semicolumn;
        }
        source_file >> semicolumn;
        source_file >> b[i];
    }
    source_file.close();

    //modyfikacja względem zaproponowanego kodu, aby całość była w jednej tablicy
    for(int i=0;i<matrix_size;i++){
            A[i][matrix_size]=b[i];
    }

    for(int i=0;i<matrix_size;i++){
        for(int j=0;j<matrix_size+1;j++){
            cout<<A[i][j]<<" ";
        }
        cout<<endl;
    }

    rozmiarTab=matrix_size;
    return A;
    }
}

int main()
{
    double **W;
    int wybor;
    int opcja;
    do{
    cout<<"\t\tMENU"<<endl;
    cout<<"1: Wczytanie danych z pliku"<<endl;
    cout<<"2: Metoda eliminacji Gaussa bez wyboru elementow"<<endl;
    cout<<"3: Wyjscie z programu"<<endl<<endl;
    cout<<"Wpisz swoj wybor: ";
    cin>>wybor;

    switch(wybor){
    case 1:
        cout<<"Wczytuje z pliku..."<<endl;
        W=wczytZpliku();
        if(czyDane==true) cout<<"Wczytano"<<endl;
        break;

    case 2:
        cout<<endl<<"\t\tMETODA ELIMINACJI BEZ WYBORU ELEMENTOW"<<endl;
        if(czyDane==true){
            cout<<"1: Uzyj danych wczytanych z pliku"<<endl;
            cout<<"2: Wpisz wlasne dane"<<endl;
            cin>>opcja;
            if(opcja==1) bezWyboru(1,W,rozmiarTab);
            else if(opcja==2) bezWyboru(2,W,rozmiarTab);
            else cout<<"Zly wybor"<<endl;
            break;
        }

        else{
            cout<<"Nie wczytano danych wiec nalezy wpisac je wlasnorecznie"<<endl;
            bezWyboru(2,W,rozmiarTab);
            break;
        }

    case 3:
        cout<<"Program zostal zakmniety"<<endl;
    }
    }while(wybor!=3);
}
