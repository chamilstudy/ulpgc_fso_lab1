/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  0.0.0.0
 *  @date     09-03-23
 *
 *  @abstract Operative Systems Fundamentals Lab 1
*/

#include <stdlib.h>

struct {
	int* asientos;
	int n_asientos, o_asientos;
} sala;

/*!
 * @function   existe_id
 * @abstract   Checks if client ID exists.
 * @discussion Checks if client ID exists and returns 1, if not returns 0.
 *                
 *
 * @param      id       Client ID to check.     
 *
 * @return     Returns 0 if not found and 1 if found..
*/
int existe_id(int id) {
	int existe = 0;

	if (id >= 0) {
		for (int i = 0; i < sala.n_asientos; i++) {
			if (*(sala.asientos + i) == id) {
				existe = 1;
			}
		}
	}

	return existe; 
}

/*!
 * @function   reserva_asiento
 * @abstract   Books a chair for given client ID.
 * @discussion Books a chair for given client ID, if successful returns the
               first available chair found, if not returns -1.
 *                
 *
 * @param      id       Client ID.
 *
 * @return     Chair assigned or -1 if not successful.
*/
int reserva_asiento(int id) {
	int asiento = -1;
      
        // checks if id is greater than 0 and if room is not empty
	if ((!existe_id(id)) && (sala.o_asientos < sala.n_asientos) && (id >= 0)) {
		for (int i = 0; i < sala.n_asientos; i++) {
			if((*(sala.asientos + i) == -1)) {
				*(sala.asientos + i) = id;
				asiento = i;
				sala.o_asientos++;
				break;
			}
		}	
	}

	return asiento;
}

/*!
 * @function   libera_asiento
 * @abstract   Frees given chair.    
 * @discussion Frees given chair, if successful returns the ID of the client that
               had booked the chair, if not returns -1.
 *                
 *
 * @param      id       Client ID.
 *
 * @return     ID of client or -1 if not successful.
*/
int libera_asiento(int asiento) {
	int id = -1;
        
        // checks if chair is in the interval [chair, capacity] and if the room
        // is not empty
	if ((asiento >= 0) && (asiento < sala.n_asientos) && (*(sala.asientos + asiento) != -1)) {
		id = *(sala.asientos + asiento);
		*(sala.asientos + asiento) = -1;
		sala.o_asientos--;
	}

	return id;
}

/*!
 * @function   estado_asiento
 * @abstract   Checks if the chair is booked and by whom.
 * @discussion Checks if the chair is booked and returns ID of client or -1 if
               unsuccessful or available.
 *                
 *
 * @param      asiento   Chair to check.
 *
 * @return     ID of client or -1 if available or unsuccessful.
*/
int estado_asiento(int asiento) {
	int id = -1;
      
        // checks if asiento is in the interval [chair, capacity]
	if ((asiento < sala.n_asientos) && (asiento >= 0)) {
		id = *(sala.asientos + asiento);
	}

	return id;
}

/*!
 * @function   asientos_libres
 * @abstract   Checks the number of available chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_libres() {
	return sala.n_asientos - sala.o_asientos;
}

/*!
 * @function   asientos_ocupados
 * @abstract   Checks the number of booked chairs.
 *
 * @return     Number of booked chairs.
*/
int asientos_ocupados() {
	return sala.o_asientos;
}

/*!
 * @function   capacidad
 * @abstract   Checks the capacity of room.
 *
 * @return     Capacity of room.
*/
int capacidad() {
	return sala.n_asientos;
}

/*!
 * @function   crea_sala
 * @abstract   Creates new room.
 * 
 * @param      capacidad       The capacity of the room.
*/
void crea_sala(int capacidad) {
        // checks if capacidad is positive. if not sets to 0
	if (capacidad < 0) capacidad = 0;
	
	sala.asientos = calloc(capacidad, sizeof(int));

	sala.n_asientos = capacidad;
	sala.o_asientos = capacidad;
        
        // sets each chair to default value (-1)
	for (int i = 0; i < capacidad; i++) {
		libera_asiento(i);
	}
}

/*!
 * @function   elimina_sala
 * @abstract   Removes room.
*/
void elimina_sala() {
	free(sala.asientos);
	sala.asientos = NULL;
	sala.n_asientos = 0;
	sala.o_asientos = 0;
}
