#include <iostream>
using namespace std;
#include <clocale>
#include "rlutil.h"
using namespace rlutil;
#include "Funciones.h"


int main()
{
    setlocale(LC_ALL, "spanish");
    setColor(WHITENESS);
    setBackgroundColor(BLACK);
    int opc;
    while(true)
    {
        cls();
        cout<<"|----------------------------|"<<endl;
        cout<<"|       MENÚ PRINCIPAL       |"<<endl;
        cout<<"|----------------------------|"<<endl;
        cout<<"| 1) PLATOS                  |"<<endl;
        cout<<"| 2) CLIENTES                |"<<endl;
        cout<<"| 3) PEDIDOS                 |"<<endl;
        cout<<"| 4) REPORTES                |"<<endl;
        cout<<"| 5) CONFIGURAIÓN            |"<<endl;
        cout<<"|----------------------------|"<<endl;
        cout<<"| 0) SALIR DEL PROGRAMA      |"<<endl;
        cout<<"|----------------------------|"<<endl<<endl;
        cout<<"Ingrese una Opción: ";
        cin>>opc;
        switch(opc)
        {
        case 1:
        {
            Menu_2();
        } break;
        case 2:
        {

        } break;
        case 3:
        {

        } break;
        case 4:
        {

        } break;
        case 5:
        {

        } break;
        case 0:
        {
            return false;
        }
        break;
        default:
        {
            cout<<"Opción Incorrecta"<<endl;
            getch();
        }
        break;
        }
    }
    return 0;
}
