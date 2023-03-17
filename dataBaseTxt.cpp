#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<direct.h>
#include<sys/stat.h>
#include <dirent.h>
#include <filesystem>

using namespace std;

struct node {
    string data ;
    struct node*next ;
};

class Vol
{
    public:
        int vol_c;
        string departure_city;
        string arrival_city;
        int Departure_date;
        int Arrival_date;

        Vol()
        {
            cout << " --> Vol number : ";
            cin >> this->vol_c;

            cout << " --> Departure date : ";
            cin >> this->Departure_date;

            cout << " --> Arrival date ";
            cin >> this->Arrival_date;

            cout << " --> Departure city : ";
            cin >> this->departure_city;

            cout << " --> Arrival city : ";
            cin >> this->arrival_city;
        }
};

void CreateFolder(){
    string path ;
    cout<< "-> Enter the path to create a new folder : ";
    cin>>path;
    string Folder_name ;
    cout<<"give a folder a name : ";
    cin>>Folder_name ;
    string Full_path = path + "\\" + Folder_name ;
    const char* c_full_path = Full_path.c_str();
    int result =  mkdir(c_full_path );   

    if( result == 0) cout<< "Folder Created sucessfely at => " << Full_path << endl;
    else cout<<"Failed to create a folder :/"<<endl ;
}

void DeleteVol(){

    string dirname;
    cout << "\n\n\n\n-> Enter the directory of the file : ";
    cin >> dirname;

    string fileTxt ;
    cout << "-> Enter the name of the file : ";
    cin >> fileTxt ;

    string path = dirname + "\\" + fileTxt + ".txt" ; 

    int vol_t;
    cout << " --> Vol number : ";
    cin >> vol_t;

    ifstream file_t(path) ;

    if (!file_t.is_open()) {
        cout << "Failed to open file " << path << endl;
        DeleteVol();
    }

    string textLine ;

    struct node*head = NULL ;
    struct node*ptr = NULL ;
    struct node*p = NULL ;

    // create a linked list 

    while( getline(file_t , textLine) ){

        ptr = new node;
        ptr->data = textLine ;
        ptr->next = NULL ;

        if( head == NULL ) head = ptr ;
        else {

            p = head ;

            while (  p->next != NULL)
            {
                p = p->next ;
            }
            p->next = ptr ;
        } 
    }

    p = head ;

    while ( p != NULL)
    {
        cout<<"--" << p->data << endl ;
        p = p->next ;
    }
    
    file_t.close();

    // delete a node

    struct node*prv = NULL ;
    struct node*current = head ;

    for (size_t index = 0 ; index < (vol_t*5) - 6  && current != NULL ; index++ )
    {
        prv = current ;
        current = current->next ;
    }

    for(size_t idx = 0 ; idx < 5 && current != NULL ; idx++){
        prv->next = current->next ;
        free(current); current = NULL; 
        current = prv->next ;
    }

    current = NULL;

    // rebuild the archive 

    ofstream MyFile(dirname+"\\"+"temp.txt");

    ptr = head ;

    printf("\n\n__________________________________\n\n");

    if (head == NULL) {
        cerr << "Error: Could not remove the vol\n\n" << endl;
        DeleteVol();
    }

    while ( head != NULL)
    {
        ptr = head ;
        MyFile<<head->data<<"\n";
        head = head->next ;
        free(ptr);
        ptr = NULL ;
    }

    MyFile.close();

    cout << "Note : the vold number " << vol_t << " has been deleted successfully ! \n\n\n";
} 

void AddNewVol(){

    int yes_no = 0;

    cout<< " would you like to create a folder ( 1 for yes || 0 for no ) \ninput :  ";
    cin>>yes_no ;

    if( yes_no == 1){
        CreateFolder();
    }

    string dirname;
    cout << "\n\n\n\n-> Enter the directory of the file : ";
    cin >> dirname;

    string fileTxt ;
    cout << "-> Enter the name of the file : ";
    cin >> fileTxt ;

    dirname = dirname + "\\" + fileTxt + ".txt" ;

    cout<<"******** Create new Vol ********\n\n\n ";
    Vol vol_t ;

    if( vol_t.Departure_date > 12) vol_t.Departure_date = vol_t.Departure_date  - 12 ;
    if( vol_t.Arrival_date > 12) vol_t.Arrival_date = vol_t.Arrival_date - 12 ;

    fstream file_t; 
    file_t.open(dirname, ios::app); // append text

    if( file_t.is_open() )
    {
        file_t << "vol " << vol_t.vol_c << "\n";
        file_t <<"=========================" << "\n";
        file_t << vol_t.departure_city ;

        for (size_t i = 0; i < (12 - vol_t.departure_city.length() ); i++)
        {
            file_t << ".";
        }

        file_t << " = ";
        file_t << vol_t.Departure_date <<endl ;
        file_t << vol_t.arrival_city ;
        for (size_t i = 0; i < (12 - vol_t.arrival_city.length() ); i++)
        {
            file_t << ".";
        }
        file_t << " = ";
        file_t << vol_t.Arrival_date <<endl ;
        file_t <<"=========================" << "\n";

        file_t.close();

        cout<<"\n\n vol " << vol_t.vol_c << " has being succesfuly added at => " << dirname << endl ;
    }

    else cout<< "\n\n -> Failed to add new vol :/\n\n";
}

void ShowAll()
{
    string dirname;
    cout << "-> Enter the directory of the file : ";
    cin >> dirname;

    string fileTxt ;
    cout << "-> Enter the name of the file : ";
    cin >> fileTxt ;

    dirname = dirname + "\\" + fileTxt + ".txt" ;
    ifstream file_t(dirname);

    if(file_t.is_open() == false){
        cout<<"Error there is no such as this file , recheck the directory or the name of file :/"<<endl<<dirname<<endl<<endl;
        ShowAll();
    }

    printf("\n\n________________________________________________________________\n\n");

    string text;
    while (getline(file_t, text))
    {
        cout << text << endl;
    }

    file_t.close();
    printf("\n\n________________________________________________________________\n\n");
}

void SearchForVol()
{
    bool got_it = false;
    string dirname, text;
    cout << "-> Enter the directory of the file : ";
    cin >> dirname;

    string fileTxt ;
    cout << "-> Enter the name of the file : ";
    cin >> fileTxt ;

    dirname = dirname + "\\" + fileTxt + ".txt" ;

    int vol_t;
    cout << " --> Vol number : ";
    cin >> vol_t;
    int index = 1;
    ifstream file_t(dirname);
    printf("\n\n");

    for (size_t i = 0;  (getline(file_t , text)) && (i < (vol_t*5) && got_it != true ); i++)
    {
        if( i == ((vol_t*5) - 6)){
            for (int j = 0; (getline(file_t , text) && j < 5); j++)
            {
                cout<<text<<endl;
            }     
            got_it = true ;      
        }
    }

    if( got_it == false) cout <<"the vol is not exist in our database :/\n\n";
    printf("\n\n");
    file_t.close();
}

void ShowContent_OfFolder(){
    DIR *dir;
    struct dirent *ent;
    string path ; 
    cout << "\n\n-> Enter the directory of the file : ";
    cin >> path;

    const char * folderPath = path.c_str();
    cout << "\n\n The Files inside this folder :\n______________________________________\n\n";
    if ((dir = opendir(folderPath)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cout << ent->d_name << "\n";
        }
        closedir(dir);
    } else {
        cerr << "\n\nError: Failed to open directory" << endl;
    }

    printf("\n\n______________________________________\n\n");
}

void Menu(){

    int option ;

    do
    {
        cout << "\t\t\t*** Program's menu ***\n\n\n";
        cout << " \t 0) _ Exit the program \n\n\t 1) _ Add/Create new vol \n\n\t 2) _ Delete a Vol \n\n\t 3) _ Show the content of a file \n\n\t 4) _ Search for a vol \n\n\t 5) _ Show Content of a folder\n\n\n input : " ;
        cin>> option ;

        switch (option)
        {
        case 0:
            cout << "\n\nPROGRAM EXIT\n\n";
            exit(-0);
            break;
        case 1:
            AddNewVol();
            break;
        case 2:
            DeleteVol();
            break;
        case 3:
            ShowAll();
            break;
        case 4:
            SearchForVol();
            break;
        case 5:
            ShowContent_OfFolder();
            break;
        default:
            break;
        }
    } while ( option != 0);
}

int main()
{
    Menu();
    return 0;
}