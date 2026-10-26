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

typedef struct{
    char nombre[30];
    Idol miembros[4];
    int n;
    Idol *lider;
} Grupo;

void mostrar(const Idol *i){
    printf(" nombre: %s\n poplularidad: %d\n energia: %d\n energia maxima: %d\n fans: %d\n",
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
        printf ("nombre: %s\n nombre:%s\n", a->nombre, b->nombre);
        return 1;
    }
    }

void asignar_cancion(Idol *i, cancion*c){
    if (i==NULL){
        return;
    }
    i->cancion=c;
}

int popularidad_total(const Idol *i){
    if(i==NULL){
        return 0;
    }
    int total=i->popularidad;
    if(i->cancion!=NULL){
        total+=i->cancion->bonus;
    }
    return total;
}

int cambiar_lider(Grupo *g, Idol *nuevo){
    if(g==NULL || nuevo==NULL){
        return 0;
    }
    for(int i=0; i<g->n; i++){
        if(&g->miembros[i]==nuevo){
            g->lider=nuevo;
            return 1; 
        }
    }
    return 0;
}

void mostrar_grupo(const Grupo *g){
    if (g==NULL){
        return;
    }
    printf("nombre del grupo: %s\n", g->nombre);
    if (g->lider==NULL){
        printf("lider: NULL\n");
    }else
    printf("lider: %s\n", g->lider->nombre);
    for(const Idol *p=g->miembros; p<g->miembros+g->n; p++){
        mostrar(p);
    }
}

int contar_activos(const Grupo *g){
    if(g==NULL || g->n==0){
        return 0;
    }
    int activos=0;
    for(const Idol *p=g->miembros; p<g->miembros+g->n; p++){
        if(esta_activa(p)){
            activos++;
        }
    }
    return activos;
}

Idol *idol_mas_cansado(Grupo *g){
    if(g==NULL || g->n==0){
        return NULL;
    }
    Idol *mas_cansado= &g->miembros[0];
    for(Idol *p=g->miembros+1; p<g->miembros+g->n; p++){
        if(p->energia<mas_cansado->energia){
            mas_cansado=p;
        }

    }
    return mas_cansado;
}

void dar_concierto(Grupo *g){
    if(g==NULL){
        return;
    }
    for(Idol *p=g->miembros; p<g->miembros+g->n; p++){
        if(esta_activa(p)){
            p->fans+=popularidad_total(p)* 10;
            p->energia=limitar(p->energia-30,0,p->energia_max);
            if(p->cancion->vigencia>0){
                p->cancion->vigencia--;
                if(p->cancion->vigencia==0){
                    printf("La cancion %s ya no tiene vigenia\n", p->cancion->nombre);
            }
        }
    }
}
}
int main(){
    cancion discos[2]={
        {"HOME;RUN",10,3},{"HOT",5,6}
    };
    
    Grupo g ={"seventeen", {{"Mingyu",100,100,100,10000,NULL}, {"Jun",60,70,100,999,NULL}, {"The8",50,40,100,998,NULL}}, 3, NULL};
    printf("lider: %s\n",g.lider->nombre);
    cambiar_lider(&g, &g.miembros[0]);
    printf("lider: %s\n",g.lider->nombre);
    printf("fans: %d\n",g.lider->fans);
    mostrar_grupo(&g);
    printf("activos: %d\n", contar_activos(&g));
    Idol *mas_cansado=idol_mas_cansado(&g);
    if(mas_cansado!=NULL){
        descansar(mas_cansado);
    }
    printf("El idol mas cansado es: %s\n", mas_cansado->nombre);
    printf("Energia del mas cansado: %d\n", mas_cansado->energia);
    asignar_cancion(&g.miembros[0],&discos[0]);
    asignar_cancion(&g.miembros[1], &discos[0]);
    popularidad_total(&g.miembros[0]);
    
    printf("Empieza el concierto\n");
    dar_concierto(&g);
    printf("Energia total: %d\n", g.miembros[0].energia);    
    printf("Después del concierto\n");
    mostrar_grupo(&g);
    printf("fans: %d\n", g.miembros[0].fans);

    printf("Energia total: %d\n", g.miembros[0].energia);    printf("fans: %d\n", g.miembros[0].fans);


    colaboracion(&g.miembros[0], &g.miembros[0]);
    colaboracion(NULL, &g.miembros[1]);
    colaboracion(&g.miembros[0], &g.miembros[1]);
    mostrar(&g.miembros[0]);
    mostrar(&g.miembros[1]);

    Idol *turno=&g.miembros[0];
    Idol *otra=&g.miembros[1];
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

    

    Idol *p=&g.miembros[0];
    Idol *q=&g.miembros[1];
    colaboracion(&g.miembros[0], &g.miembros[0]);
    
    ensayar(&g.miembros[0]);
    /*ensayar(&g.miembros[0]);
    ensayar(&g.miembros[0]);
    ensayar(&g.miembros[0]);
    ensayar(&g.miembros[0]);
    ensayar(&g.miembros[0]);

    descansar(&g.miembros[0]);
    descansar(&g.miembros[0]);
    descansar(&g.miembros[0]);
    descansar(&g.miembros[0]);
    descansar(&g.miembros[0]);*/
    descansar(&g.miembros[0]);
    esta_activa(&g.miembros[0]);
    p-> energia=limitar(p->energia, 0, p->energia_max);
    printf("%d \n ", g.miembros[0].fans);
    printf("%d \n ", (*p).fans);
    printf("%d \n ", p->fans);
    printf("%p %p \n ",(void *)p, (void *)&g.miembros[0]);
    mostrar (&g.miembros[0]);
    printf(" esta activo: %d \n", esta_activa(&g.miembros[0]));
    printf(" popularidad total: %d \n", popularidad_total(&g.miembros[0]));
}

