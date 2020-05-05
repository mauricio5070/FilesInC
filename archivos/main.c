/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Capacitacion
 *
 * Created on 30 de enero de 2018, 08:13 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {
    
    FILE* archivo;
    char string [250];
    // fopen=> file open
    //            nombre /    modo
    archivo = fopen("prueba.txt","a");   //r: read; w:write-> solo al incio; a: append-> al final;
    fputs("Esto es un archivo de prueba...\n",archivo);
    fclose(archivo);
    archivo= fopen("prueba.txt", "r");
    fgets(string,250,archivo);
    printf("%s",string);
    fclose(archivo);

    return (EXIT_SUCCESS);
}


