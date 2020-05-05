/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Ari Mora
 *
 * Created on 1 de febrero de 2018, 06:49 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMLINEA    100
#define TAMELEMENTO 50
#define TAMARCHIVO    50000

// abre un archivo
FILE* abrirArchivo(char* nombre, char* modo){
    FILE* archivo;
    
    archivo = fopen(nombre, modo);
    if(archivo == NULL){
        printf("Error al abrir el archivo\n");
    }
    
    return archivo;
}

// cierra un archivo
void cerrarArchivo(FILE* archivo){
    if (fclose(archivo) != 0){
        printf("Error al cerrar el archivo\n");
    }
}

// retorna el tamanno del archivos en bytes
long tamannoArchivo(FILE* archivo){
    long resultado = 0;
    long posicionActual;
    
    // guardo la posicion actual del cursor
    posicionActual = ftell(archivo);
    
    // movemos el cursor al inicio del archivo
    fseek(archivo, 0, SEEK_SET);
    // movemos el cursor al final del archivo
    fseek(archivo, 0, SEEK_END);
    // guardamos la posicion del cursor
    resultado = ftell(archivo);
    
    return resultado;
}

void guardarElementos(FILE* archivo, int dato1, int dato2, int dato3){
    fprintf(archivo, "%i;%i;%i\n", dato1, dato2, dato3);
}

void imprimirElementos(char* linea){
    char* elemento;
    elemento = strtok(linea, ";");

    while( elemento != NULL ){
        printf("%s ", elemento);

        elemento = strtok(NULL, ";");
    }

    printf("\n");
}

void imprimirArchivo(FILE* archivo){
    int contador = 1;
    char linea[TAMLINEA];
    
    while(fgets(linea, TAMLINEA, archivo) != NULL){
        printf("Linea %d: ", contador);
        imprimirElementos(linea);
        contador++;
    }
}

int contarLineas(FILE* archivo){
    int contador = 0;
    char linea[TAMLINEA];
    
    while(fgets(linea, TAMLINEA, archivo) != NULL){
        contador++;
    }
    
    return contador;
}

void imprimirLinea(FILE* archivo, int numLinea){
    int contador = 1;
    char linea[TAMLINEA];
    
    fseek(archivo, 0, SEEK_SET);
    
    while(fgets(linea, TAMLINEA, archivo) != NULL){
        if (contador == numLinea){
            imprimirElementos(linea);
        }
        contador++;
    }
}

void imprimirLinea2(FILE* archivo, int numLinea){
    int contador = 0;
    char linea[TAMLINEA];
    
    fseek(archivo, 0, SEEK_SET);
    
    for (contador = 0; contador < numLinea; contador++) {
        fgets(linea, TAMLINEA, archivo);
    }
    imprimirElementos(linea);
}

void eliminarLinea(FILE* archivo, int numLinea){
    int contador = 1;
    char linea[TAMLINEA];
    
    fseek(archivo, 0, SEEK_SET);
    
    while(fgets(linea, TAMLINEA, archivo) != NULL){
        if (contador != numLinea){
            imprimirElementos(linea);
        }
        contador++;
    }
}

void eliminarLineaArchivo(char* nombreArchivo, int numLinea){
    int contador = 1;
    char linea[TAMLINEA];
    char contenidos[TAMARCHIVO] = "";
    FILE* archivo;
    
    archivo = abrirArchivo(nombreArchivo, "r");
    fseek(archivo, 0, SEEK_SET);
    while(fgets(linea, TAMLINEA, archivo) != NULL){
        if (contador != numLinea){
            strcat(contenidos, linea);
        }
        contador++;
    }
    cerrarArchivo(archivo);
    
    archivo = abrirArchivo(nombreArchivo, "w");
    fputs(contenidos, archivo);
    cerrarArchivo(archivo);
}

/*
 * 
 */
int main(int argc, char** argv) {
    char nombreArchivo[50];
    FILE* archivo;
    int opcion = 1;
    int dato1;
    int dato2;
    int dato3;
    
    printf("Ingrese el nombre del archivo: ");
    scanf("%s", nombreArchivo);
    
    while(opcion != 0){
        printf("Editor CSV\n");
        printf("1. Ver el tamanno del archivo\n");
        printf("2. Ver el total de lineas\n");
        printf("3. Imprimir los contenidos del archivo\n");
        printf("4. Agregar elementos al archivo\n");
        printf("5. Imprimir contenidos de una linea\n");
        printf("6. Eliminar contenidos de una linea\n");
        printf("0. Salir\n\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion){
            case 1:     //tamanno
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    printf("El tamanno del archivo es %ld bytes", tamannoArchivo(archivo));
                    cerrarArchivo(archivo);
                }
                break;
            case 2:     //cantidad lineas
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    printf("El archivo contiene %d lineas", contarLineas(archivo));
                    cerrarArchivo(archivo);
                }
                break;
            case 3:     //imprimir todos los elementos
                archivo = abrirArchivo(nombreArchivo, "r");
                if (archivo != NULL) {
                    imprimirArchivo(archivo);
                    cerrarArchivo(archivo);
                }
                break;
            case 4:     //agregar elementos
                printf("Ingrese tres numeros enteros separados por espacios: \n");
                scanf("%d %d %d", &dato1, &dato2, &dato3);
                archivo = abrirArchivo(nombreArchivo, "a");
                if(archivo != NULL){
                    guardarElementos(archivo, dato1, dato2, dato3);
                    cerrarArchivo(archivo);
                }
                break;
            case 5:     //mostrar linea
                printf("Ingrese el numero de linea: ");
                scanf("%d", &dato1);
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    if(dato1 > 0 && dato1 <= contarLineas(archivo)){
                        imprimirLinea(archivo, dato1);
                        cerrarArchivo(archivo);
                    }
                }
                break;
            case 6:     //eliminar linea
                printf("Ingrese el numero de linea: ");
                scanf("%d", &dato1);
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    if(dato1 > 0 && dato1 <= contarLineas(archivo)){
                        cerrarArchivo(archivo);
                        eliminarLineaArchivo(nombreArchivo, dato1);
                    }
                }
                break;
            default:
                if(opcion != 0){
                    printf("Opcion no reconocida");
                }
        }
        
        printf("\nPresione una tecla para continuar\n");
        getchar();
        //system("cls");
    }
    
    return (EXIT_SUCCESS);
}

