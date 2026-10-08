#include <stdio.h>
typedef struct{
    char nombre[30];
    int popularidad;
    int energia;
    int energia_max;
    int fans;

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

int main(){
    Idol uno ={"Mingyu",100,100,100,10000};

    Idol *p=&uno;
    
    ensayar(&uno);
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
    descansar(&uno);
    esta_activa(&uno);
    p-> energia=limitar(p->energia, 0, p->energia_max);
    printf("%d \n ", uno.fans);
    printf("%d \n ", (*p).fans);
    printf("%d \n ", p->fans);
    printf("%p %p \n ",(void *)p, (void *)&uno);
    mostrar (&uno);
    printf("esta activa: %d \n", esta_activa(&uno));
}

