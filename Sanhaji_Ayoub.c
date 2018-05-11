/**
 * @author Ayoub SANHAJI
 * @version 1.0
 */

#include<conio.h>
#include<stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include<math.h>

#define VIDE 0
#define Nbr 16

int laby[Nbr][Nbr];
int murs_vert[Nbr][Nbr];
int murs_horiz[Nbr][Nbr];
int stoped = 0;
int DERNIERE_VAL = 1;
int disponible = 0;
void retour_en_arr();
char chemin[99999];
int L, C,
    POS_ACT_VAL=0,
    POS_ACT_X=0,
    POS_ACT_Y=0;
char directions[4] = {'E','O','N','S'};
int directions_x[4] = { 0, 0, 1, -1};
int directions_y[4] = { 1, -1, 0, 0};

struct coords {
  int x;
  int y;
}coords;
struct coords case_trouvee;
struct coords PE;
struct coords PS;

int rdtsc()
{
    __asm__ __volatile__("rdtsc");
}

int random(const int MIN, const int MAX){
    int nombre = 0;
    srand(rdtsc());
    nombre = (rand() % (MAX + 1 - MIN)) + MIN;
    return nombre;
}

int dans_grille(int x, int y)
{
    return (x >= 0 && x < L && y >= 0 && y < C);
}

void laby_vierge(int l, int c){
    int x, y;
    for (x = 0; x < l; x++)
        for (y = 0; y < c; y++)
          laby[x][y] = VIDE;
    int xe = random(0,l-1);
    int ye = random(0,c-1);
    laby[xe][ye] = 1;
    POS_ACT_VAL = 1;
    POS_ACT_X = xe;
    POS_ACT_Y = ye;
}

void preparer_murs(int l, int c){
    int x, y;
    for (x = 0; x < l; x++){
        for (y = 0; y < c; y++){
            murs_vert[x][y] = 1;
            murs_horiz[x][y] = 1;
        }
    }
}

int direction_disponible (){
     int i=0,x, y;
     disponible = 0;
     while(i<9999){
         int ran = random(0,3);
         x = POS_ACT_X + directions_x[ran];
         y = POS_ACT_Y + directions_y[ran];
         disponible = 0;
         if( laby[x][y] == VIDE && dans_grille(x,y)){
             if(ran==0) murs_vert[x][y] = 0;
             if(ran==1) murs_vert[x][y+1] = 0;
             if(ran==2) murs_horiz[x][y] = 0;
             if(ran==3) murs_horiz[x+1][y] = 0;
             POS_ACT_X = x;
             POS_ACT_Y = y;
             disponible = 1;
             return disponible;
         }
         else{
             disponible = 0;
             }
         i++;
     }
     return disponible;
}

void remplire_laby(){
    int i,x, y,nbr_act = 0;
    stoped = 0;
    if(DERNIERE_VAL < C*L){
        if(direction_disponible() == 1){
            nbr_act = DERNIERE_VAL + 1;
            laby[POS_ACT_X][POS_ACT_Y] = nbr_act;
            DERNIERE_VAL = nbr_act;
            POS_ACT_VAL = DERNIERE_VAL;
            remplire_laby();
        }
        else{
             stoped = 1;
             retour_en_arr();
            }
                        }
}

void rech_par_val(int val){
     int i,j,x,y;
     for (i=0;i<L;i++)
     {
         for (j=0;j<C;j++)
         {
             if (laby[i][j]==val){
                   x = i;
                   y = j;
             }
         }
     }
     case_trouvee.x = x;
     case_trouvee.y = y;
}

void retour_en_arr(){
    int i ,x ,y, nbr_act;
    nbr_act = POS_ACT_VAL - 1;
    rech_par_val(nbr_act);
    POS_ACT_X = case_trouvee.x;
    POS_ACT_Y = case_trouvee.y;
    POS_ACT_VAL = nbr_act;
    remplire_laby();
}

void afficheSeparateur(int n,int y) {
  int i;
  for (i = 0; i < n; i++){
    if(murs_horiz[y][i]==1)
         printf("+---");
    else
         printf("+   ");
  }
  puts("+");
}

void afficheSeparateurHautBas(int n) {
  int i;
  for (i = 0; i < n; i++){
         printf("+---");
  }
  puts("+");
}

void afficheLabyVierge(int l, int c) {
    int x, y;

    for (x = 0; x < l; x++){
         afficheSeparateurHautBas(c);
         for (y = 0; y < c; y++){
               printf("|");
               printf("   ");
    }
    puts("|");
  }
  afficheSeparateurHautBas(c);
}

void afficheLabyAvecNum(int l, int c) {
  int x, y;
    for (x = 0; x < l; x++){
        if(x==0) afficheSeparateurHautBas(c);
        else  afficheSeparateur(c,x);
        for (y = 0; y < c; y++){
           if(y==0)
               printf("|");
           else if(murs_vert[x][y]==1)
               printf("|");
           else
               printf(" ");
           printf("%3d", laby[x][y]);
        }
    puts("|");
  }
  afficheSeparateurHautBas(c);
}

void afficheLaby(int l, int c) {
        int x, y;
        int x1,y1,xf,yf;
        rech_par_val(1);
        PE.x = case_trouvee.x;
        PE.y = case_trouvee.y;
        rech_par_val(l*c);
        PS.x = case_trouvee.x;
        PS.y = case_trouvee.y;

    for (x = 0; x < l; x++){
        if(x==0) afficheSeparateurHautBas(c);
        else  afficheSeparateur(c,x);
        for (y = 0; y < c; y++){
           if(y==0)
               printf("|");
           else if(murs_vert[x][y]==1)
               printf("|");
           else
               printf(" ");
           if(x==PS.x && y==PS.y)
                        printf(" PS");
           else
               if(x==PE.x && y==PE.y)
                        printf(" PE");
           else
                printf("   ");
        }
    puts("|");
  }
  afficheSeparateurHautBas(c);
}

char* retournerChemin(int laby[Nbr][Nbr],struct coords pe,struct coords ps){
     int x=pe.x;
     int y=pe.y;
     int i, xi, yi;
     strcpy (chemin,"[ ");
     for(i=2; i <= L*C; i++){
        rech_par_val(i);
        xi = case_trouvee.x;
        yi = case_trouvee.y;
        int x_def = xi - x;
        int y_def = yi - y;
        if(x_def > 0 && y_def == 0) strcat(chemin,"S");
        else if(x_def < 0 && y_def == 0) strcat(chemin,"N");
        else if(x_def == 0 && y_def > 0) strcat(chemin,"E");
        else if(x_def == 0 && y_def < 0) strcat(chemin,"O");
        else strcat(chemin,"Retour");
        x = xi;
        y = yi;
        if(i != 1 && i<L*C) strcat(chemin,"; ");
     }
     strcat(chemin," ]");
     return chemin;
}

void menu()
{
     printf("\n*********************************************************************\n");
     printf("****           1:Labyrinthe Vierge                               ****\n");
     printf("****           2:L'affichage de Labyrinthe avec numeros          ****\n");
     printf("****           3:L'affichage de Labyrinthe sans numeros          ****\n");
     printf("****           4:L'affichage de Solution                         ****\n");
     printf("****           0:Pour termine                                    ****\n");
     printf("****           Donner votre choix :                              ****\n");
     printf("*********************************************************************\n\n");
}

main(){
       int choix;
       do{
           printf("Taper le nombre des lignes [ <16 ] : ");
       scanf("%d",&L);
       printf("Taper le nombre des colonnes [ <16 ] : ");
       scanf("%d",&C);
       }while((L<1)||(L>16)||(C<1)||(C>16));
       laby_vierge(L,C);
       preparer_murs(L,C);
       do{
            menu();
                scanf("%d",&choix);
                switch(choix)
                {
                    case 1 :  printf("Voila le Labyrinthe vierge : \n");
                              afficheLabyVierge(L, C);
                              break;
                    case 2 :  printf("Voila le Labyrinthe avec numeros : \n");
                              remplire_laby();
                              afficheLabyAvecNum(L,C);
                              break;
                    case 3 :  printf("Voila le Labyrinthe sans numeros : \n");
                              remplire_laby();
                              afficheLaby(L,C);
                              break;
                    case 4 :  printf("Voila la solution de Labyrinthe :\n");
                              remplire_laby();
                              afficheLaby(L,C);
                              printf("\nLes coordonnees des PE et PS sont : \n");
                              printf("\nPoint d\'entree: PE(%d,%d)",PE.x,PE.y);
                              printf("\nPoint de sortie: PS(%d,%d)\n",PS.x,PS.y);
                              printf("\nLes instructions a suivre Du Point D'entree vers le point de sortie : \n %s\n",retournerChemin(laby,PE,PS));
                              break;
                    case 0 :  break;
                    default : printf("Erreur de choix\n");
                }
    }while(choix);
       getch();
}
