#include <stdio.h>

typedef struct
{
    char nombre[30];
    int bonus;
    int vigencia;
}cancion;

typedef struct{
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;
    cancion *cancion;

}Idol;



void mostrar(const Idol *i){
    printf("nombre: %s \n, pop[ularidad: %d \n, energia: %d \n, energia maxima: %d \n, fans: %d \n",
    i->nombre, i->popularidad, i->energia, i->energia_max, i->fans);
}
int limitar(int valor, int minimo, int maximo){
    if(valor < minimo)return minimo;
    if(valor > maximo)return maximo;
    return valor;
    
}

void ensayar(Idol *i ){
    i->popularidad+=5;
    i->energia=limitar(i->energia-20,0, i->energia_max);
}
void descansar(Idol *i){
    i->energia=limitar(i->energia + 20, 0, i->energia_max);
}

int esta_activa(const Idol *i){
    return i->energia>0?1:0;

}
int colaboracion (Idol *a, Idol *b){
    if(a == NULL || b == NULL ||a == b){
         return 0;
    }
    else{
        a->popularidad+=10;
        b->popularidad+=10;
        a->energia=limitar(a->energia-15,0, a->energia_max);
        b->energia=limitar(b->energia-15,0, b->energia_max);
        printf ("nombre: %s\n, nombre:%s\n,", a->nombre, b->nombre);
        return 1;
    }
    }

void asignar_cancion(Idol *i, cancion*c){
    if (i==NULL){
        return;
    }
    i->cancion=c;
}

int main(){
    cancion discos[2]={
        {"hello",10,3},{"loser",5,6}
    };

    Idol uno ={"Mingyu",100,100,100,10000,NULL};
    Idol dos ={"Jun",60,70,100,999,NULL};

    asignar_cancion(&uno,&discos[0]);
    asignar_cancion(&dos, &discos[0]);

    colaboracion(&uno, &uno);
    colaboracion(NULL, &dos);
    colaboracion(&uno, &dos);
    mostrar(&uno);
    mostrar(&dos);

    Idol *turno=&uno;
    Idol *otra=&dos;
    Idol *temp=NULL;

while (esta_activa(turno)&& esta_activa(otra)){
    ensayar(turno);
    printf("turno %s %d\n",turno->nombre,turno->energia);

    temp=turno;
    turno=otra;
    otra=temp;
}
    if(esta_activa(turno)){
        printf("quedo con energia %s \n",turno->nombre );
    }else{
        printf("queda con energia %s \n", otra->nombre);
    }

    

    Idol *p=&uno;
    Idol *q=&dos;
    colaboracion(&uno, &uno);
    
    //ensayar(&uno);
    /*ensayar(&uno);
    ensayar(&uno);
    ensayar(&uno);
    ensayar(&uno);
    ensayar(&uno);

    descansar(&uno);
    descansar(&uno);
    descansar(&uno);
    descansar(&uno);
    descansar(&uno);*/
    //descansar(&uno);
    esta_activa(&uno);
    p-> energia=limitar(p->energia, 0, p->energia_max);
    printf("%d \n ", uno.fans);
    printf("%d \n ", (*p).fans);
    printf("%d \n ", p->fans);
    printf("%p %p \n ",(void *)p, (void *)&uno);
    mostrar (&uno);
    printf("esta activa: %d \n", esta_activa(&uno));
}

