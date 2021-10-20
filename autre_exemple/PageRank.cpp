//
//  main.cpp
//  matrix
//
//  Created by Amir on 10/02/2020.
//  Copyright © 2020 Amir. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sys/time.h>


using namespace std;

struct Node
{
    int dest;
    double pert;
    Node *next;
};

struct puit{
    int name;
    puit* next;
};
puit *puits = NULL;

double* create_random_vector();
double** create_matrix_pleine();
double* multiplication_matrix_pleine(double **matrix, double *vector);
Node** create_matrix_creuse();
double* multiplication_matrix_creuse(Node **nodes, double *vector);
void test_convergence_pleine(double *vector);
void test_convergence_creuse(double *vector);
double* random_surfer_multiplication(Node **nodes, double *vector);
void test_convergence_random_surfer( Node **nodes, double *vector);
double* extrapolation(double* Xk, double* Xk_2);
void test_convergence_creuse_extrapolation(Node **nodes, double *vector, int m);
ifstream inFile;

double Alpha = 0.85;
double unMoinsAlpha;
double unSurN;
double S;
int nbr_sommet = 0;

int main(int argc, const char * argv[]) {

    string file_name = "";
    cout << "File name : ";
    cin >> file_name;


    inFile.open("le chemin vers tonn fichier juste ici"+file_name);

    if (!inFile) {
       cout << "Unable to open file\n";
       exit(1);
    }

    int nbr_arc = 0;
    inFile >> nbr_sommet;

    inFile >> nbr_arc;

    //For random surfer
    unMoinsAlpha = 1 - Alpha;
    unSurN = (double)1 / nbr_sommet;
    S = unSurN * unMoinsAlpha ;


    //double *vector = create_random_vector(nbr_sommet);
/*
    double vector[nbr_sommet];

    for (int i = 0; i < nbr_sommet; i++) {
        vector[i] = 1/(double)nbr_sommet;
    }
*/
    double *vector = (double*) malloc (sizeof(double)*nbr_sommet);
    for (int i = 0; i < nbr_sommet; i++) {
        vector[i] = 1/(double)nbr_sommet;
    }

    Node **nodes = create_matrix_creuse();


    //test_convergence_pleine(nodes, vector);
    //test_convergence_creuse(nodes, vector);

    cout << "Teste sans extrapolation :\n";

    test_convergence_random_surfer(nodes, vector);

    cout << "-----------------------------------\n";

    cout << "Teste Avec extrapolation :\n";


    
    if(file_name == "in-2004v2.txt"){
        int i = 31;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }else if(file_name == "Stanford.txt"){
        int i = 32;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }else if(file_name == "wikipedia-20051105V2.txt"){
        int i = 18;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }else if(file_name == "wb-cs-stanford.txt"){
        int i = 24;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }else if(file_name == "Stanford_BerkeleyV2.txt"){
        int i = 32;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }else if(file_name == "wb-edu.txt"){
        int i=40;
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }
    /*for (int i=11; i < 100; i++) {
        cout << i << ":  ";
        test_convergence_creuse_extrapolation(nodes, vector, i);
    }*/

    inFile.close();

    return 0;
}

//**************************************************************************************************
//================================= creation vecteur aleatoire =====================================

double* create_random_vector(){

    double *vector = (double*) malloc (sizeof(double)*nbr_sommet);
    int modulo = 100;
    for (int i =0; i < nbr_sommet - 1; i++) {
      int r =  rand() % modulo;
      vector[i] = (double)r/100;
      modulo -= r;
    }
    vector[nbr_sommet-1] = (double)modulo/100;

    return vector;
}

//***************************************************************************************************
//================================== Matrice Pleine =================================================

double** create_matrix_pleine(){


    double **matrix;


    matrix = (double**) malloc (sizeof(double*)*nbr_sommet);
    for (int i =0; i < nbr_sommet; i++) {
        matrix[i] = (double*) malloc (sizeof(double)*nbr_sommet);
    }

    for (int i = 0; i < nbr_sommet; i++) {
        for (int j = 0; j < nbr_sommet; j++) {
            matrix[i][j]  = 0;
        }
    }

    inFile.clear();
    inFile.seekg (0, ios::beg);
    int tmp;
    inFile >>  tmp;
    inFile >>  tmp;


    int node1;
    int degree;
    int node2;
    double pert;
    while (inFile >> node1) {
       inFile >> degree;
       while(degree > 0){
           inFile >> pert;
           inFile >> node2;
           matrix[node1][node2] = pert;
           degree--;
       }
    }

    for (int i = 0; i < nbr_sommet; i++) {
       for (int j = 0; j < nbr_sommet; j++) {
           cout << matrix[i][j] << " ";
       }
       cout << "\n";
    }

    return matrix;

}

double* multiplication_matrix_pleine(double **matrix, double *vector){

    double *result = (double*) malloc (sizeof(double)*nbr_sommet);
    double temp;
    for (int i = 0; i < nbr_sommet; i++) {
        temp = 0;
        for (int j = 0; j < nbr_sommet; j++) {
            temp += vector[j] * matrix[j][i];
        }
        result[i] = temp;
    }

    return result;
}

void test_convergence_pleine(double *vector){

    double **matrix = create_matrix_pleine();

    double *result1 = multiplication_matrix_pleine(matrix, vector);

    int count =0;

    timeval curTime;
    gettimeofday(&curTime, NULL);
    int m1 = curTime.tv_usec / 1000;

     while (1) {

        double *result2 = multiplication_matrix_pleine(matrix, result1);

        int i =0;
        double s = 0;
        for ( ; i < nbr_sommet; i++) {
            if (result1[i] > result2[i]) {
                s += (result1[i] - result2[i]);
            }
            else{
                s += (result2[i] - result1[i]);
            }
        }
        count++;
        if ( s < 0.000001 ) {
            cout << "elle converge";
            cout << " -> "<< count << "\n";
            break;
        }
        result1 = result2;
    }

    gettimeofday(&curTime, NULL);
    int m2 = curTime.tv_usec / 1000;

    cout << "it tooks "<<m2 - m1 << " ms\n";

}

//*****************************************************************************************************
//================================== Matrice Creuse ===================================================

Node** create_matrix_creuse(){

    Node **nodes = (struct Node**) malloc (sizeof(struct Node**)*nbr_sommet);
    int i =0;
    for (i = 0; i < nbr_sommet; i++) {
        nodes[i] = NULL;
    }

    inFile.clear();
    inFile.seekg (0, ios::beg);
    int tmp;
    inFile >>  tmp;
    inFile >>  tmp;

    int pred;
    int succ;
    int degree;
    Node *suiv;
    Node *node;

    puit *p;

    int o = 0;
    while (inFile >> pred) {
        o++;
        if (o%100000 == 0) {
            cout << o << "\n";
        }
        inFile >> degree;

        //instruction si le premier sommet est '1'
        pred--;

        if (degree == 0) {
            p = (puit*) malloc (sizeof(puit));
            p->name = pred;
            p->next = puits;
            puits = p;
        }

        while(degree > 0){
            node = (struct Node*)malloc(sizeof(struct Node));

            //premiere instruction si la pertinence est avant le sommet
            //inFile >> node->pert; inFile >> succ;
            inFile >> succ; inFile >> node->pert;

            node->dest = pred;
            node->next = NULL;

            //premiere instruction si le premier sommet est '0'
            //if (!nodes[succ]) nodes[succ] = node;
            if (!nodes[succ-1]){
               nodes[succ-1] = node;
             }
            else{
                //premiere instruction si le premier sommet est '0'
                //suiv = nodes[succ];
                suiv = nodes[succ-1];
                while ( suiv->next != NULL ) {
                    suiv = suiv->next;
                }
                suiv->next = node;
            }

           degree--;
        }
    }

    /*
    puit *a = puits;
    while (a) {
        cout << a->name << " ";
        a = a->next;
    }
    */
    /*
    for (int i = 0; i < nbr_sommet; i++) {
        Node *n = nodes[i];
        while (n != NULL) {
            cout << "| " << i+1 << " " << ((n->dest)+1) << " " << n->pert;
            n = n->next;
        }
        cout << "\n";
    }
    */
    return nodes;
}

double* multiplication_matrix_creuse(Node **nodes, double *vector){

    double *result = (double*) malloc (sizeof(double)*nbr_sommet);

    double temp;
    for (int i = 0; i < nbr_sommet; i++) {
        temp = 0;
        Node *node = nodes[i];
        while (node) {
            temp += node->pert*vector[node->dest];
            node = node->next;
        }
        result[i] = temp;
    }

    return result;

}

void test_convergence_creuse(double *vector){

    Node **nodes = create_matrix_creuse();

    double *result1 = multiplication_matrix_creuse(nodes, vector);

    int count =0;

    timeval curTime;
    gettimeofday(&curTime, NULL);
    int m1 = curTime.tv_usec / 1000;

     while (1) {

        double *result2 = multiplication_matrix_creuse(nodes, result1);

        int i =0;
        double s = 0;
        for ( ; i < nbr_sommet; i++) {
            if (result1[i] > result2[i]) {
                s += (result1[i] - result2[i]);
            }
            else{
                s += (result2[i] - result1[i]);
            }
        }

        count++;
        if ( s < 0.000001 ) {
            cout << "elle converge";
            cout << " -> "<< count << "\n";

            //for (int k =0; k < nbr_sommet; k++) cout << result2[k] << " ";

            break;
        }

        result1 = result2;
    }

    gettimeofday(&curTime, NULL);
    int m2 = curTime.tv_usec / 1000;

    cout << "it tooks "<<m2 - m1 << " ms\n";

}

//****************************************************************************************************
//================================== Surfeur Aleatoire ===============================================

double* random_surfer_multiplication(Node **nodes, double *vector){

    double *result = (double*) malloc (sizeof(double)*nbr_sommet);

    double M = 0; //les arcs d'un puit à tous les sommets
    puit *a = puits;
    while (a) {
       M += unSurN * vector[a->name];
       a = a->next;
    }

    for (int i = 0; i < nbr_sommet; i++) {
        result[i] = 0;
        Node *node = nodes[i];
        while (node) {
            result[i] += node->pert*vector[node->dest];
            node = node->next;
        }
        result[i] = ((( result[i] + M ) * Alpha ) + S );
    }

    return result;

}


void test_convergence_random_surfer(  Node **nodes, double *vector ){

    timeval curTime;
    gettimeofday(&curTime, NULL);
    int m1 = curTime.tv_usec / 1000;


    gettimeofday(&curTime, NULL);
    int m2 = curTime.tv_usec / 1000;
    cout << "it tooks "<<m2 - m1 << " ms to create matrix / " << " s\n";


    double *result1 = random_surfer_multiplication(nodes, vector);

    int count =0;

    gettimeofday(&curTime, NULL);
    m1 = curTime.tv_usec / 1000;

     while (1) {

        double *result2 = random_surfer_multiplication(nodes, result1);

        int i = 0;
        double s = 0;
        for ( ; i < nbr_sommet; i++) {
            if (result1[i] > result2[i]) {
                s += (result1[i] - result2[i]);
            }
            else{
                s += (result2[i] - result1[i]);
            }
        }
        count++;
         cout << "difference 2 " << s * 1000000 <<"\n";
        if ( s < 0.000001 ) {
            cout << "elle converge";
            cout << " -> "<< count << "\n";

            //for (int k =0; k < nbr_sommet; k++) cout << result2[k] << " ";

            break;
        }
        result1 = result2;
    }

    gettimeofday(&curTime, NULL);
    m2 = curTime.tv_usec / 1000;
    cout << "it tooks "<<m2 - m1 << " ms to converge /   s\n";

}

//****************************************************************************************************
//================================== Extrapolation ===================================================

double* extrapolation_amine(double* Xk, double* Xk_1) {

    double *result = (double*) malloc (sizeof(double)*nbr_sommet);

    for (int i=0; i < nbr_sommet; i++) {
        result[i] = ( Xk[i] - ( Alpha * Xk_1[i] ) ) / (1 - Alpha) ;
    }

    return result;
}

double alpha2 = Alpha * Alpha;

double* extrapolation(double* Xk, double* Xk_2) {

    double *result = (double*) malloc (sizeof(double)*nbr_sommet);

    for (int i=0; i < nbr_sommet; i++) {
        result[i] = ( Xk[i] - ( alpha2 * Xk_2[i] ) ) / (1 - alpha2) ;
    }

    return result;
}

void test_convergence_creuse_extrapolation(Node **nodes, double *vector, int m){

    //le vecteur k-1
    double *K_Moins_1 = vector;

    //le vecteur k-2
    double *K_Moins_2 = vector;

    //le vecteur k
    double *K;

    int count = 0;
    int limite = 100;

    timeval curTime;
    gettimeofday(&curTime, NULL);
    int m1 = curTime.tv_usec / 1000;

    while (1) {

        K = random_surfer_multiplication(nodes, K_Moins_1);

        double s = 0;
        for (int i = 0; i < nbr_sommet; i++) {
           if (K[i] > K_Moins_1[i]) s += (K[i] - K_Moins_1[i]);
           else s += (K_Moins_1[i] - K[i]);
        }
        cout << "difference " << s*1000000 <<"\n";
        if ( s < 0.000001 ) {
           cout << "* elle converge";
           cout << " -> "<< count << "\n";

           //for (int k =0; k < nbr_sommet; k++) cout << result2[k] << " ";

           break;
        }
        if (count == limite){ cout << "count = "<< limite << " And it doesn't converge ! \n";break;}


        // il y a plusieurs méthodes pour faire appel a extrapolation
        // 1) count == m
        // 2) count != 0 && count%m == 0
        // 3) count > m && ( (count-m)%3 == 0 ) ; -- selon le prof

        if (count == m ) {  K = extrapolation_amine(K, K_Moins_1); }


        K_Moins_2 = K_Moins_1;
        K_Moins_1 = K;

        count++;

    }
    if(count < limite){
        gettimeofday(&curTime, NULL);
        int m2 = curTime.tv_usec / 1000;
        cout << "\tit tooks "<<m2 - m1 << " ms to converge / " << " s\n";
    }

}
/*
 wb-cs-stanford.txt
 Stanford.txt
 Stanford_BerkeleyV2.txt
 in-2004v2.txt
 wikipedia-20051105V2.txt
 wb-edu.txt
 */
