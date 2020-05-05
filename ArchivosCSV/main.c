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

#define TAMLINEA 100
#define TAMELEMENTO 50

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
    posicionActual = ftell(archivo);// no es necesaario guardar la pocision actual. ftell siempre devuelve long
    
    
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

void guardarVarios(FILE* archivo,int n, int dato){
    int i;
   
    
    for(i=0;i<n;i++){
      printf("Ingrese un numero entero: \n");
      scanf("%d;", &dato); 
     fprintf(archivo, "%i;", dato);
    }
    fprintf(archivo, "\n");
    
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


void eliminaLinea(FILE* archivo, int numLinea){
    FILE* archivo2;
    
    int contador = 0;
    char linea[TAMLINEA];
    
      while(fgets(linea, TAMLINEA, archivo) != NULL){
       
        if(numLinea == contador){
            int dato1=NULL;
            int dato2=NULL;
            int dato3=NULL;
           fprintf(archivo, "%i;%i;%i\n", dato1, dato2, dato3);
        }
    }
    
    
}


void imprimeLinea(FILE* archivo, int numLinea){
   
    int contador = 0;
    char linea[TAMLINEA];
    
    fseek(archivo, 0, SEEK_SET);
      while(fgets(linea, TAMLINEA, archivo) != NULL){
          contador++;
        if(numLinea == contador){
            
            imprimirElementos(linea);
        }
    }
    
    
}


void imprimeLinea2(FILE* archivo, int numLinea){
    int i=0;
    char linea[TAMLINEA];
    fseek(archivo, 0, SEEK_SET);
    for(i=0;i<numLinea;i++){
       fgets(linea,TAMLINEA, archivo);

    }
        imprimirElementos(linea);
   
}

/*
 * 
 */
int main(int argc, char** argv) {
    char nombreArchivo[50];
    char nuevoNombre[50];
    FILE* archivo;
    int opcion = 1;
    int dato1;
    int dato2;
    int dato3;
    int n;
    
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
        printf("7. Cambiar nombre del archivo\n");
        printf("8. Agregar varios elementos\n");
        printf("0. Salir\n\n");
        printf("Ingrese la opcion: ");
        scanf("%d", &opcion);
        
        switch(opcion){
            case 1:     //tamanno
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    printf("El tamanno del archivo es %ld", tamannoArchivo(archivo));
                    cerrarArchivo(archivo);
                }
                break;
                   system("pause");
                   system("cls");
            case 2:     //cantidad lineas
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    printf("El archivo contiene %d lineas", contarLineas(archivo));
                    cerrarArchivo(archivo);
                }
                break;
                   system("pause");
                   system("cls");
            case 3:     //imprimir todos los elementos
                archivo = abrirArchivo(nombreArchivo, "r");
                if (archivo != NULL) {
                    imprimirArchivo(archivo);
                    cerrarArchivo(archivo);
                }
                break;
                   system("pause");
                   system("cls");
            case 4:     //agregar elementos
                printf("Ingrese tres numeros enteros separados por espacios: \n");
                scanf("%d %d %d", &dato1, &dato2, &dato3);
                archivo = abrirArchivo(nombreArchivo, "a");
                if(archivo != NULL){
                    guardarElementos(archivo, dato1, dato2, dato3);
                    cerrarArchivo(archivo);
                }
                break;
                   system("pause");
                   system("cls");
            case 5:     //mostrar linea
                printf("Ingrese el numero de linea: ");
                scanf("%d", &dato1);
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    if(dato1 > 0 && dato1 <= contarLineas(archivo)){
                        imprimeLinea(archivo,dato1);
                    }
                    else{printf("La linea no existe\n");}
                }
                break;
                   system("pause");
                   system("cls");
            case 6:     //eliminar linea
                printf("Ingrese el numero de linea que desee eliminar: ");
                scanf("%d", &dato1);
                archivo = abrirArchivo(nombreArchivo, "r");
                if(archivo != NULL){
                    if(dato1 > 0 && dato1 <= contarLineas(archivo)){
                        eliminaLinea(archivo,dato1);
                    }
                    else{printf("La linea no existe\n");}
                }
                break;
                   system("pause");
                   system("cls");
            
            
            case 7:     //eliminar linea
                printf("Ingrese el nuevo nombre: ");
                scanf("%s", nuevoNombre);
                
                archivo = abrirArchivo(nombreArchivo, "r");
                
              
                
                
                cerrarArchivo(nuevoNombre);
                break;
                   system("pause");
                   system("cls");
            
            
            case 8:
                
       archivo = abrirArchivo(nombreArchivo, "a");
       
                if(archivo != NULL){
                    
               printf("Digite el numero de elementos que desea guardar\n");
               scanf("%d", &n);
                
                    guardarVarios(archivo,n,dato1);
                    cerrarArchivo(archivo);
                }
                
               
                break;
                system("pause");
                system("cls");
            
            default:
                if(opcion != 0){
                    printf("Opcion no reconocida");
                }
        }
        
        //printf("\nPresione una tecla para continuar\n");
        getchar();
        system("pause");
        system("cls");
    }
    
    return (EXIT_SUCCESS);
}

