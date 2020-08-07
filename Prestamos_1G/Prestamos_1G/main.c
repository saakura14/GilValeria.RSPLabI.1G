#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "utn.h"
#include "Prestamo.h"
#include "Cliente.h"
#include "Informe.h"

#define QTY_CLIENTES 50
#define QTY_PRESTAMOS 50

int menu()
{
    int opcion;
    utn_getNumero(&opcion, "Ingrese la opcion a elegir:\n"
                  "1.  Alta de clientes\n"
                  "2.  Modificar datos de un cliente.\n"
                  "3.  Baja de cliente\n"
                  "4.  Alta de prestamo\n"
                  "5.  Saldar prestamo\n"
                  "6.  Reanudar prestamo\n"
                  "7.  Mostrar la lista de clientes\n"
                  "8.  Mostrar la lista de prestamos\n"
                  "9.  Informar clientes\n"
                  "10. Informar prestamos\n"
                  "11. Salir\n"
                  "Opcion: ",
                  "La opcion ingresada es incorrecta\n", 1, 11, 2);

    return opcion;
}

int main(void)
{
    Cliente arrayCliente[QTY_CLIENTES];
    Prestamo arrayPrestamo[QTY_PRESTAMOS];
    char respuesta = 's';
    int clientesCargados =0;
    int auxiliarIndice=0;
    int auxiliarIdCliente=0;
    int auxiliarIdPrestamo=0;
    int hayPrestamo = 0;
    int idClientes;
    int opcionPrestamo;
    int opcionClientes;
    int auxiliarImporte;
    int opcionPrestamos;
    int auxiliarCuotas;

    if(inicializarCliente(arrayCliente, QTY_CLIENTES)==0 && inicializarPrestamo(arrayPrestamo, QTY_PRESTAMOS)==0)
    {
        printf("El sistema esta listo para ingresar nuevos clientes y prestamos.\n");
    }

    do
    {

        switch(menu())
        {
        case 1:
            printf("\nALTA DE CLIENTE.\n");
            auxiliarIndice=buscarPrimerPosicionVacia(arrayCliente, QTY_CLIENTES);
            if(auxiliarIndice>=0)
            {
                if(altaDeCliente(arrayCliente, QTY_CLIENTES, auxiliarIndice, &idClientes) == 0)
                {
                    printf("\nCarga realizada con exito\n");
                    clientesCargados++;

                }
                else
                {
                    printf("\nNO HAY MAS LUGAR");
                }
            }
            break;
        case 2:
            printf("\nMODIFICAR CLIENTE: \n");
            if(clientesCargados<0)
            {
                imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
                if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID a modificar: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
                {
                    auxiliarIndice= buscarClientePorId(arrayCliente, QTY_CLIENTES, auxiliarIdCliente);
                    if(	auxiliarIndice >-1 &&
                            modificarCliente(arrayCliente, QTY_CLIENTES, auxiliarIndice) == 0)
                    {
                        printf("\nModificacion realizada con exito\n");
                    }
                }
            }
            else
            {
                printf("No hay clientes cargados\n");
            }
            break;
        case 3:
            printf("\nBAJA CLIENTE.\n");
            if(clientesCargados<0)
            {
                imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
                if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID a eliminar: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
                {
                    auxiliarIndice = buscarClientePorId(arrayCliente,QTY_CLIENTES,auxiliarIdCliente);
                    if(	auxiliarIndice >= 0)
                    {
                        darDeBajaCliente(arrayCliente, QTY_CLIENTES, auxiliarIndice);
                        darDeBajaPrestamoACliente(arrayPrestamo,QTY_PRESTAMOS,auxiliarIdCliente);
                        printf("\nBaja realizada con exito\n");
                        clientesCargados--;
                    }
                }
            }
            else
            {
                printf("No hay clientes cargados\n");
            }
            break;
        case 4:
            printf("\nALTA PRESTAMO:\n");
            auxiliarIndice=buscarPrimerPosicionVaciaPrestamo(arrayPrestamo, QTY_PRESTAMOS);
            if(auxiliarIndice>=0)
            {
                imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
                if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID del cliente al que le quiere asignar un prestamo: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
                {
                    altaDePrestamo(arrayPrestamo, QTY_PRESTAMOS,  auxiliarIndice, &auxiliarIdPrestamo, auxiliarIdCliente);
                    imprimirPrestamo(&arrayPrestamo[auxiliarIndice]);
                    hayPrestamo++;
                }
            }
            break;
        case 5:
            printf("\nSALDAR PRESTAMO\n");
            if(clientesCargados>0 && hayPrestamo>0){
            imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
            if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID del cliente al que quiere saldar un prestamo: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
            {
                imprimirArrayPrestamoFiltradoPorSaldado(arrayPrestamo, QTY_PRESTAMOS, 0,auxiliarIdCliente);
                if(utn_getNumero(&auxiliarIdPrestamo, "\nIndique el ID del prestamo al que quiere saldar: \n", "Error, reingrese el ID\n",0, QTY_PRESTAMOS, 0)==0)
                {

                    printf("\nSeguro que quiere saldarlo? s/n \n");
                    fflush(stdin);
                    scanf("%d", &opcionPrestamo);
                    if(opcionPrestamo=='s')
                    {
                        saldarPrestamo(arrayPrestamo, QTY_PRESTAMOS,auxiliarIndice);
                        printf("\nEl prestamo ha sido saldado\n");
                        hayPrestamo--;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            }else{
            printf("No hay prestamos o clientes cargados\n");
            }
            break;
        case 6:
            printf("\nREANUDAR PRESTAMO\n");
            imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
            if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID del cliente al que quiere reanudar un prestamo: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
            {
                imprimirArrayPrestamoFiltradoPorSaldado(arrayPrestamo, QTY_PRESTAMOS, 1,auxiliarIdCliente );
                if(utn_getNumero(&auxiliarIndice, "\nIndique el ID del prestamo que quiere reanudar: \n", "Error, reingrese el ID\n",0, QTY_PRESTAMOS, 0)==0)
                {
                    printf("\nconfirma reanudar? s/n \n");
                    fflush(stdin);
                    scanf("%d", &opcionPrestamo);
                    if(opcionPrestamo=='s')
                    {
                        reanudarPrestamo(arrayPrestamo, QTY_PRESTAMOS,auxiliarIndice );
                        printf("\nreanudado con exito\n");

                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        case 7:
            printf("\nCLIENTES CON PRESTAMOS ACTIVOS:\n");
            imprimirArrayClientes(arrayCliente, QTY_CLIENTES);
            if(utn_getNumero(&auxiliarIdCliente, "\nIndique el ID del cliente al que quiere mostra los prestamos activos: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
            {
                imprimirArrayPrestamoFiltradoPorSaldado(arrayPrestamo, QTY_PRESTAMOS, 0,auxiliarIdCliente);
            }
            break;
        case 8:
            printf("\nLISTA DE PRESTAMOS: \n");
            imprimirArrayPrestamo(arrayPrestamo,QTY_PRESTAMOS);
            if(utn_getNumero(&auxiliarIdPrestamo, "\nIndique el ID del prestamo para informar: \n", "Error, reingrese el ID\n",0, QTY_CLIENTES, 0)==0)
            {
                imprimirPrestamo(arrayPrestamo);
                auxiliarIdCliente=arrayPrestamo[auxiliarIdPrestamo-1].idCliente;
                printf("\nEl CUIL del cliente es: %s\n", arrayCliente[auxiliarIdCliente-1].cuil);
            }
            break;
        case 9:
            if(utn_getNumero(&opcionClientes, "\nIndique la opcion a elegir:\n"
                             "1 - Cliente con mas prestamos activos\n"
                             "2 - Cliente con mas prestamos saldados\n"
                             "3 - Cliente con mas prestamos\n", "Error, reingrese la opcion\n",1, 3, 0)==0)
            {
                switch(opcionClientes)
                {
                case 1:
                    mostrarClienteConMasPrestamosFiltradoPorSaldado(arrayCliente, QTY_CLIENTES, arrayPrestamo, QTY_PRESTAMOS, 0);
                    break;
                case 2:
                    mostrarClienteConMasPrestamosFiltradoPorSaldado(arrayCliente, QTY_CLIENTES, arrayPrestamo, QTY_PRESTAMOS, 1);
                    break;
                case 3:
                    mostrarClienteConMasPrestamos(arrayCliente, QTY_CLIENTES,arrayPrestamo, QTY_PRESTAMOS);
                }
            }
            break;
        case 10:
            if(utn_getNumero(&opcionPrestamos, "\nIndique la opcion a elegir:\n"
                             "1. \nCantidad de prestamos mayores a $1000\n"
                             "2. \nPrestamos de 12 cuotas saldados\n"
                             "3. \nPrestamos activos con 'n' cantidad de cuotas\n", "Error, reingrese la opcion\n",1, 3, 0)==0)
            {
                switch(opcionPrestamos)
                {

                case 1:
                    if(utn_getNumero(&auxiliarImporte, "\nINDIQUE IMPORTE PARA LISTAR PRESTAMOS MAYORES A $1000 :\n", "Error, reingrese el importe\n",1000, 100000, 1)==0)
                    {
                        mostrarCantidadPrestamosMayoresAImporteSeleccionado(arrayPrestamo, QTY_PRESTAMOS,auxiliarImporte );
                    }
                    break;
                case 2:
                    mostrarPrestamosDeDoceCuotasSaldados(arrayPrestamo, QTY_PRESTAMOS);
                    break;
                case 3:
                    if(utn_getNumero(&auxiliarCuotas, "\nIndique la cantidad de cuotas que desea ver :\n", "Error, reingrese la cantidad de cuotas\n",1, 48, 0)==0)

                    {
                        mostrarPrestamosActivosFiltradoPorCantDeCuotas(arrayPrestamo, QTY_PRESTAMOS, auxiliarCuotas);
                    }
                    break;
                }
            }
            break;
        case 11:
            printf("\nDESEA SALIR? s/n\n");
            fflush(stdin);
            scanf("%c", &respuesta);
            //tolower(respuesta);
            break;
        default:
            printf("Opcion incorrecta.\n");
            break;

        }
        system("pause");
        system("cls");

    }
    while(respuesta=='s');
    return 0;
}
