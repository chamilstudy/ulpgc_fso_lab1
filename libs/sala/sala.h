/*!
 *  @author   Chamil José Cruz Razeq
 *  
 *  @version  0.0.0.0
 *  @date     09-03-23
 *
 *  @abstract Operative Systems Fundamentals Lab 1
*/

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
int existe_id(int id);

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
int reserva_asiento(int id);

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
int libera_asiento(int asiento);

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
int estado_asiento(int asiento);

/*!
 * @function   asientos_libres
 * @abstract   Checks the number of available chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_libres();

/*!
 * @function   asientos_ocupados
 * @abstract   Checks the number of booked chairs.
 *
 * @return     Number of available chairs.
*/
int asientos_ocupados();

/*!
 * @function   capacidad
 * @abstract   Checks the capacity of room.
 *
 * @return     Capacity of room.
*/
int capacidad();

/*!
 * @function   crea_sala
 * @abstract   Creates new room.
 * 
 * @param      capacidad       The capacity of the room.
*/
void crea_sala(int capacidad);

/*!
 * @function   elimina_sala
 * @abstract   Removes room.
*/
void elimina_sala();
