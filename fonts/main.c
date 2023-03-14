/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  0.0.0.0
 *  @date     09-03-23
 *
 *  @abstract Operative Systems Fundamentals Lab 1
*/

#include <stdio.h>
#include "../headers/sala.h"

/*!
 * @function   pick
 * @abstract   Asks user to pick a value in an interval.
 * @discussion This function allows the user to input a value between the
 *             minimum and maximum values given. If the value inputted is out
 *             of this interval, returns -1.
 *                
 *
 * @param      min     The minimum value of the interval.
 * @param      max     The maximum value of the interval.
 *
 * @return     A integer value inputted by the user or -1.
*/
int pick(int min, int max) {
        /*! @var      selection      Selected option by user.*/
	int selection = -1;
	
        scanf("%d", &selection);
	
	// Checks if selection is between max and min
	if ((selection > max) && (selection < min)) {
		selection = -1;
	}

	return selection;
}

/*!  
 * @function   print_option
 * @abstract   Prints indexes and description of each option.
 *  
 * @result     A menu printed on CLI.
*/
void print_options() {
    printf("    [OPCIONES] Opciones disponibles:\n"
           "    * 0 : Crear Sala.\n"
           "    * 1 : Eliminar Sala.\n"
           "    * 2 : Reservar Asiento.\n"
           "    * 3 : Liberar Asiento.\n"
           "    * 4 : Revisar Asiento.\n"
           "    * 5 : Ver información general de Sala.\n"
           "    * 6 : Ver opciones.\n"
           "    * Cualquier otro valor: Salir.\n");
}

/*!
 * @function   print_asientos
 * @abstract   Prints a table with all the chairs and clients id.
 *
 * @result     A table printed on CLI.
*/
void print_asientos() {
  //  prints the header of the table
  printf("    [DEBUG MODE]\tTabla de datos:\n"
         "    * -------------------\n"
         "    * | Asie |    ID    |\n"
         "    * -------------------\n");
  
  for(int i = 0; i < capacidad(); i++) {
    int id = estado_asiento(i);
   
    //  checks if chair has client assigned
    if (id != -1) {
      //  prints each row of the table
      printf("    * | %4d | %8d |\n"
             "    * -------------------\n", i, id);
    } 
  }
}

/*!
 * @function   user_interface
 * @abstract   Allows interactions and provides visual interface for room
 *             management.
 * @discussion This function provides a visual interface and allows the
 *             user to interact with the program using CLI.
 *                
 *
 * @param      mode     Enables/Disables printing debug information.
 *
 * @result     Visual interface and interaction
*/
void user_interface(int mode) {
  /*!
   *  @var      selection     Selected option by user.
   *  @var      agree         Inputted agreement/disagreement by user.
  */
  int selection = 0;
  char agree = '\0';
  
  int asiento, id, n_asientos;
  asiento = id = n_asientos = -1;  
  
  print_options();
  
  //  loops over options selected by user
  while((selection >= 0) && (selection <= 6)) {
    
    //  asks user to type option desired
    printf("[!] Elija una opción (Introduzca 6 para ver opciones): ");
    selection = pick(0, 6);
    
    //  switch over desired option
    switch(selection) {
      //  adds room
      case 0:
        //  checks if there is already a room and asks if wants to overwrite it
        if (capacidad() != 0) {
          printf("[!] [CREA SALA]\t\tYa existe una sala. ¿Quieres borrar la anterior? [s/n]: ");
          scanf("%s", &agree);
          
          //  check if user agreed
          if (agree != 's') {
            printf("    [CREA SALA]\t\tCreación de sala cancelada.\n");
            break;
          }
        }
        
        //  loops until capacity above 0 is inputted
	printf("[!] [CREA SALA]\t\tIndique capacidad de la sala: ");
	while (n_asientos < 1) {
	  scanf("%d", &n_asientos);
	  
	  if (n_asientos < 1) {
	    printf("[!] [CREA SALA]\t\tIndique capacidad mayor que 0: ");
	  }
	}
	
	//  creates room
	printf("    [CREA SALA]\t\tCreando sala de capacidad %d.\n", n_asientos);
	crea_sala(n_asientos);
      	break;
      
      //  removes room
      case 1:
        //  checks if there is a room
        if (capacidad() == 0) {
          printf("    [ELIMINA SALA]\tNo existen salas.\n");
          break;
        }
        
        //  asks user for agreement to remove room
        printf("    [ELIMINA SALA]\t¿Estás seguro de que deseas eliminar la sala? [s/n]: ");
        scanf("%s", &agree);
        
        //  checks if user agreed
        if (agree != 's') {
          printf("    [ELIMINA SALA]\tEliminación de sala cancelada.\n");
          break;
        }
        
        //  removes room
	printf("    [ELIMINA SALA]\tEliminando sala.\n");
	elimina_sala();
	break;
	
      //  book chair and sets client id
      case 2:
        //  checks if there is a room and chairs available
        if (capacidad() == 0) {
	  printf("    [RESERVA ASIENTO]\tNo existen salas.\n");
	  break;
	} else if (asientos_libres() < 1) {
	  printf("    [RESERVA ASIENTO]\tNo hay asientos disponibles.\n");
	  break;
	}
	
	//  asks for client id
	printf("[!] [RESERVA ASIENTO]\tIndique identificación personal: ");
	
	// loops until id is positive
	while (id < 0) {
		scanf("%d", &id);
		if (id < 0) {
			printf("[!] [RERSERVA ASIENTO]\tIndique ID mayor que 0: ");
		}
	}

	//  checks if client already booked a chair
	if (existe_id(id)) {
	  printf("    [RESERVA ASIENTO]\tEl cliente ya tiene una reserva.\n");
	  break;
	}
	
	asiento = reserva_asiento(id);
	
	//  checks for any error
	if (asiento == -1) {
	  printf("    [RESERVA ASIENTO]\tError inesperado, no se pudo realizar reserva.\n");
	  break;
	}
	
	//  prints chair number and client id
	printf("    [RESERVA ASIENTO]\tReservando asiento %d asignado a cliente %d.\n",
	       asiento, id);
	break;
      
      //  frees given chair
      case 3:
        //  checks if there is a room and chairs booked
        if (capacidad() == 0) {
	  printf("    [LIBERA ASIENTO]\tNo existen salas.\n");
	  break;
	} else if (asientos_libres() == capacidad()) {
	  printf("    [LIBERA ASIENTO]\tNo hay asientos ocupados.\n");
	  break;
	}
      
        //  loops until existing chair is inputted
	printf("[!] [LIBERA ASIENTO]\tIndique asiento a liberar: ");
	while ((asiento < 0) || (asiento > (capacidad() - 1))) {
	  scanf("%d", &asiento);
	  if ((asiento < 0) || (asiento > (capacidad() - 1))) {
	    printf("[!] [LIBERA ASIENTO]\tIndique asiento dentro de los limites 0 y %d: ",
	           capacidad() - 1);
	  }
	}
	id = libera_asiento(asiento);
	
	//  checks if chair is booked or if there is any other error
        if (id == -1) {
	  printf("    [LIBERA ASIENTO]\tError inesperado, no se pudo liberar asiento.\n");
	  break;
	}
	
	//  prints chair number, client id and frees the chair
	printf("    [LIBERA ASIENTO]\tLiberando asiento %d asignado a cliente %d.\n",
	       asiento, id);
	break;
      
      //  checks given chair state
      case 4:
        
        //  checks if there is a room and chairs booked
        if (capacidad() == 0) {
          printf("    [REVISA ASIENTO]\tNo existen salas.\n");
          break;
        } else if (asientos_libres() == capacidad()) {
          printf("    [REVISA ASIENTO]\tNo hay asientos ocupados.\n");
          break;
        }
        
        //  asks for chair to show
	printf("[!] [REVISA ASIENTO]\tIndique asiento a revisar: ");
	//  loops until existing chair is inputted
	while ((asiento < 0) || (asiento > capacidad() - 1)) {
	  scanf("%d", &asiento);
	  if ((asiento < 0) || (asiento > capacidad() - 1)) {
	    printf("[!] [REVISA ASIENTO]\tIndique asiento dentro de los limites 0 y %d: ",
	           capacidad() - 1);
	  }
	}
	id = estado_asiento(asiento);
	
	//  checks if chair is booked or if there is any other error
	if (id == -1) {
	  printf("    [REVISA ASIENTO]\tError inesperado, no se pudo revisar asiento.\n");
	  break;
	}
	
	//  prints chair number and client id
	printf("    [REVISA ASIENTO]\tEl asiento %d tiene asignado el cliente %d.\n",
	       asiento, id);
	break;
      
      //  shows general information about the room (capacity, available chairs, booked chairs)
      case 5:
        if (capacidad() == 0) {
          printf("    [VER SALA]\t\tNo existen salas.\n");
          break;
        }
        
	printf("    [VER SALA]\t\tLa sala tiene capacidad %d asientos, con %d libres y %d ocupados.\n",
	       capacidad(), asientos_libres(), asientos_ocupados());
	break;
      
      // shows options
      case 6:
        print_options();
        break;
    }
    
    //  if mode is enabled shows table (DEBUG)
    if (mode && (selection != 6) && (selection != -1)) {
      print_asientos();
    }
    
    //  resets variables
    asiento = id = n_asientos = -1;
    agree = '\0';
  }
  
  //  frees memory and ends execution
  printf("[!] Terminando ejecución.\n");
  elimina_sala();
}

/*!
 * @function   main
 * @abstract   Asks user for Debug/User mode and executes method.
*/
int main() {
  printf("[!] Indique si desea acceder en modo usuario 0 o modo debug 1: ");
  user_interface(pick(0,1));

  return 0;
}
