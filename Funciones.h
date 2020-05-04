#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED


struct Pedidos
{
    int ID;
    char Nombre[50];
    float Costo_Preparacion;
    float Valor_Venta;
    int Tiempo_Preparacion;
    int IDRestaurante;
    int Comision;
    int IDCategoria;
    bool Estado;
};

const char *PATH_PEDIDOS = "Pedidos.dat";

/*Prototipos/Declaraciones*/

void Nuevo_Plato();

int Buscar_Pedidos(int);

bool CargarPlatos(Pedidos *);

void Menu_2(Pedidos);

bool guardar_pedidos(Pedidos);

void Modificar_Plato();

void Listar_Pedidos_x_ID();

Pedidos Leer_pedidos(int);

void listar_Pedidos(Pedidos);

bool Sobreescribir_pedidos(Pedidos, int);

void Platos_X_Restaurante();

int Cant_Platos();

void Listar_Todos();

void Dar_Baja();

/*Definiciones*/

void Dar_Baja()
{
    cls();
    int ID,pos;
    char a;
    Pedidos vec;
    cout<<"Ingrese ID a dar de baja: "<<endl;
    cin>>ID;
    pos=Buscar_Pedidos(ID);
    if(pos>=0)
    {
        cout<<""<<endl;
        vec=Leer_pedidos(pos);
        listar_Pedidos(vec);
        cout<<""<<endl<<endl;
        cout<<"Desea Eliminar plato Y/N?: ";
        cin.ignore();
        cin>>a;
        cout<<""<<endl;
        switch(a)
        {
        case 'Y':
        case 'y':
        {
            vec.Estado=false;
            if(Sobreescribir_pedidos(vec,pos))
            {
                cout<<""<<endl;
                cls();
                cout<<"Se elimino el plato correctamente"<<endl;
                getch();
                return;
            }
        }
        break;
        case 'N':
        case 'n':
        {
            cout<<"No se elimino el plato."<<endl;
            getch();
            return;
        }
        break;
        }

    }
    getch();


}

void Listar_Todos()
{
    int cant;
    cant=Cant_Platos();
    Pedidos *vec;
    vec=(Pedidos *) malloc(cant * sizeof(Pedidos));
    if(vec==NULL)
    {
        cout<<"No hay memoria suficiente";
        getch();
        return;
    }

    FILE *p;
    p=fopen(PATH_PEDIDOS,"rb");
    if(p==NULL)
    {
        cout<<"No se encuentra el Archivo";
        getch();
        free(vec);
        return;
    }

    fread(vec,sizeof(Pedidos),cant,p);
    fclose(p);
    cls();
    for(int x=0; x<cant; x++)
    {
        if(vec[x].Estado==true)
        {
            cout<<"ID: "<<vec[x].ID<<endl;
            cout<<"Nombre: "<<vec[x].Nombre<<endl;
            cout<<"Costo de Preparación: $"<<vec[x].Costo_Preparacion<<endl;
            cout<<"Valor de Venta: $"<<vec[x].Valor_Venta<<endl;
            cout<<"Tiempo de Preparación: "<<vec[x].Tiempo_Preparacion<<" min"<<endl;
            cout<<"ID de Restaurante: "<<vec[x].IDRestaurante<<endl;
            cout<<"Comisión: "<<vec[x].Comision<<"%"<<endl;
            cout<<"ID de Categoria: "<<vec[x].IDCategoria<<endl;
            cout<<""<<endl;
        }
    }
    getch();
    free(vec);
}

int Cant_Platos()
{
    int bytes,cp;
    FILE *p;
    p = fopen(PATH_PEDIDOS, "rb");
    if (p == NULL)
    {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    bytes = ftell(p);
    cp = bytes / sizeof(Pedidos);
    fclose(p);
    return cp;
}

void Platos_X_Restaurante()
{
    cls();
    int ID,cant;
    cout<<"ingrese ID del Restaurante: ";
    cin>>ID;
    cant=Cant_Platos();
    if(cant==0)
    {
        cout<<"No se encuentran cargados Platos";
        getch();
        return;
    }
    Pedidos *vec;
    vec=(Pedidos *) malloc(cant * sizeof(Pedidos));
    if(vec==NULL)
    {
        cout<<"No hay memoria suficiente";
        getch();
        return;
    }

    FILE *p;
    p=fopen(PATH_PEDIDOS,"rb");
    if(p==NULL)
    {
        cout<<"No se encuentra el Archivo";
        getch();
        free(vec);
        return;
    }

    fread(vec,sizeof(Pedidos),cant,p);
    fclose(p);

    cls();
    for(int x=0; x<cant; x++)
    {
        if(vec[x].IDRestaurante==ID && vec[x].Estado==true)
        {
            cout<<"ID: "<<vec[x].ID<<endl;
            cout<<"Nombre: "<<vec[x].Nombre<<endl;
            cout<<"Costo de Preparación: $"<<vec[x].Costo_Preparacion<<endl;
            cout<<"Valor de Venta: $"<<vec[x].Valor_Venta<<endl;
            cout<<"Tiempo de Preparación: "<<vec[x].Tiempo_Preparacion<<" min"<<endl;
            cout<<"ID de Restaurante: "<<vec[x].IDRestaurante<<endl;
            cout<<"Comisión: "<<vec[x].Comision<<"%"<<endl;
            cout<<"ID de Categoria: "<<vec[x].IDCategoria<<endl;
            cout<<""<<endl;
        }
    }
    getch();

    free(vec);
}

bool Sobreescribir_pedidos(Pedidos vec, int pos)
{
    FILE *p;
    p=fopen(PATH_PEDIDOS,"rb+");
    if(p==NULL)
        return false;

    fseek(p,pos*sizeof (Pedidos),SEEK_SET);
    bool a=fwrite(&vec,sizeof(Pedidos),1,p);
    fclose(p);
    return a;
}

void listar_Pedidos(Pedidos vec)
{
    if(vec.Estado==true)
    {
        cout<<"ID: "<<vec.ID<<endl;
        cout<<"Nombre: "<<vec.Nombre<<endl;
        cout<<"Costo de Preparación: $"<<vec.Costo_Preparacion<<endl;
        cout<<"Valor de Venta: $"<<vec.Valor_Venta<<endl;
        cout<<"Tiempo de Preparación: "<<vec.Tiempo_Preparacion<<" min"<<endl;
        cout<<"ID de Restaurante: "<<vec.IDRestaurante<<endl;
        cout<<"Comisión: "<<vec.Comision<<"%"<<endl;
        cout<<"ID de Categoria: "<<vec.IDCategoria<<endl;
    }
}

Pedidos Leer_pedidos(int pos)
{
    Pedidos vec;
    FILE *p;
    p=fopen(PATH_PEDIDOS,"rb");
    if(p==NULL)
    {
        vec.ID=-1;
        return vec;
    }
    fseek( p, pos * sizeof(Pedidos),SEEK_SET);
    fread(&vec,sizeof (Pedidos),1,p);
    fclose(p);
    return vec;

}

void Listar_Pedidos_x_ID()
{
    cls();
    int id, pos;
    cout<<"Ingrese ID: ";
    cin>>id;

    pos=Buscar_Pedidos(id);
    if(pos>=0)
    {
        Pedidos vec=Leer_pedidos(pos);
        listar_Pedidos(vec);
        getch();
    }
    else
    {
        cout<<"No existe el ID ingresado";
        getch();
    }
}

void Modificar_Plato()
{
    cls();
    Pedidos vec;
    int ID,pos;
    cout<<"Ingrese id del plato a modificar: "<<endl;
    cin>>ID;
    pos=Buscar_Pedidos(ID);
    if(pos>=0)
    {
        vec=Leer_pedidos(pos);
        cout<<""<<endl;
        listar_Pedidos(vec);
        cout<<""<<endl;
        cout<<"Ingrese Valor de Venta: $";
        cin>>vec.Valor_Venta;
        cout<<"Ingrese tiempo de preparación: ";
        cin>>vec.Tiempo_Preparacion;
        if(Sobreescribir_pedidos(vec,pos))
        {
            cls();
            cout<<"Se modifico correctamente el plato";
            getch();
        }
        else
        {
            cls();
            cout<<"No se pudo modificar el plato";
            getch();
        }
    }
    else
    {
        cls();
        cout<<"El ID no se encuentra";
        getch();
    }

}

void Nuevo_Plato()
{
    Pedidos vec;
    if(CargarPlatos(&vec))
    {
        if(guardar_pedidos(vec))
        {
            cout<<"Se guardo correctamente el Plato"<<endl;
            getch();
        }
        else
        {
            cout<<"No se pudo guardar el plato correctamente"<<endl;
            getch();
        }
    }
    else
    {
        cout<<"No se pudo guardar el Plato"<<endl;
        getch();
    }
}

bool guardar_pedidos(Pedidos reg)
{
    bool escribio;
    FILE *p;
    p = fopen(PATH_PEDIDOS, "ab");
    if (p == NULL)
        return false;

    escribio = fwrite(&reg, sizeof(Pedidos), 1, p);
    fclose(p);
    return escribio;
}

int Buscar_Pedidos(int id)
{
    Pedidos v;
    int i=0;
    FILE *p;
    p=fopen(PATH_PEDIDOS,"rb");
    if(p == NULL)
        return -2;

    while(fread(&v,sizeof(Pedidos),1,p))
    {
        if(id==v.ID)
        {
            fclose(p);
            if(v.Estado==true)
            {
                return i;
            }
        }
        i++;
    }
    fclose(p);
    return -1;
}

bool CargarPlatos(Pedidos *vec)
{
    cls();
    int ID,pos;
    cout<<"Ingrese ID: ";
    cin>>ID;
    if(ID<=0)
        return false;
    pos=Buscar_Pedidos(ID);
    if(pos>=0)
    {
        cout<<"El ID ya se encuentra cargado"<<endl;
        getch();
        return false;
    }
    vec->ID=ID;
    cout<<"Ingrese Nombre: ";
    cin.ignore();
    cin.getline(vec->Nombre,50);
    if(strlen(vec->Nombre)<=0)
        return false;
    cout<<"Ingrese Costo de Preparación: $";
    cin>>vec->Costo_Preparacion;
    if(vec->Costo_Preparacion<0)
        return false;
    cout<<"Ingrese Valor de Venta: $";
    cin>>vec->Valor_Venta;
    if(vec->Valor_Venta<0 || vec->Valor_Venta<vec->Costo_Preparacion)
        return false;
    cout<<"ingrese Tiempo de Preparación: ";
    cin>>vec->Tiempo_Preparacion;
    if(vec->Tiempo_Preparacion<0)
        return false;
    cout<<"Ingrese ID del Restaurante: ";
    cin>>vec->IDRestaurante;
    if(vec->IDRestaurante<0)
        return false;
    cout<<"Ingrese Comisión del Restaurante: ";
    cin>>vec->Comision;
    if(vec->Comision<0 || vec->Comision>100)
        return false;
    cout<<"Ingrese ID de Categoria: ";
    cin>>vec->IDCategoria;
    if(vec->IDCategoria<0)
        return false;
    vec->Estado=true;
    return true;

}

void Menu_2()
{
    int opcion;
    bool salir=true;
    while(salir)
    {
        cls();
        cout<<"|-----------------------------|"<<endl;
        cout<<"|         MENÚ PLATOS         |"<<endl;
        cout<<"|-----------------------------|"<<endl;
        cout<<"| 1) NUEVO PLATO              |"<<endl;
        cout<<"| 2) MODIFICAR PLATO          |"<<endl;
        cout<<"| 3) LISTAR PLATO POR ID      |"<<endl;
        cout<<"| 4) PLATOS POR RESTAURANTE   |"<<endl;
        cout<<"| 5) LISTAR TODOS LOS PLATOS  |"<<endl;
        cout<<"| 6) ELIMINAR PLATO           |"<<endl;
        cout<<"|-----------------------------|"<<endl;
        cout<<"| 0) VOLVER AL MENÚ PRINCIPAL |"<<endl;
        cout<<"|-----------------------------|"<<endl<<endl;
        cout<<"Opción: "<<endl;
        cin>>opcion;
        switch(opcion)
        {
        case 1:
        {
            Nuevo_Plato();
        }
        break;
        case 2:
        {
            Modificar_Plato();
        }
        break;
        case 3:
        {
            Listar_Pedidos_x_ID();
        }
        break;
        case 4:
        {
            Platos_X_Restaurante();
        }
        break;
        case 5:
        {
            Listar_Todos();
        }
        break;
        case 6:
        {
            Dar_Baja();
        }
        break;
        case 0:
        {
            salir=false;
        }
        break;
        default:
        {
            cout<<"Opción incorrecta"<<endl;
            getch();
        }
        break;
        }

    }
}

#endif // FUNCIONES_H_INCLUDED
