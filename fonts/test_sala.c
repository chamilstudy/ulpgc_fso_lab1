// test_sala.c
// ===============
// Batería de pruebas de la biblioteca "sala.h/sala.c"
//

#include <assert.h>
#include <stdio.h>
#include "../headers/sala.h"

#define DebeSerCierto(x)	assert(x)
#define DebeSerFalso(x)		assert(!(x))

void INICIO_TEST (const char* titulo_test)
{
  printf("********** batería de pruebas para %s: ", titulo_test); 
 	// fflush fuerza que se imprima el mensaje anterior
	// sin necesidad de utilizar un salto de línea
	fflush(stdout);
}

void FIN_TEST (const char* titulo_test)
{
  printf ("********** hecho\n");
}


void test_ReservaBasica()
{
	int mi_asiento;
	#define CAPACIDAD_CUYAS 500
	#define ID_1 1500

	INICIO_TEST("Reserva básica");
	crea_sala(CAPACIDAD_CUYAS);
	DebeSerCierto(capacidad()==CAPACIDAD_CUYAS);
	DebeSerCierto((mi_asiento=reserva_asiento(ID_1))>=0);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	DebeSerCierto(estado_asiento(mi_asiento)>0);
	DebeSerCierto(libera_asiento(mi_asiento)==ID_1);
	DebeSerCierto((asientos_libres()+asientos_ocupados())==CAPACIDAD_CUYAS);
	elimina_sala();
	FIN_TEST("Reserva básiinfo");
}


/** ---------------------------------------------------------------------------
 *  -- TESTS ALUMNO
 *  ---------------------------------------------------------------------------
 */

void tests_manejo_salas() {
        INICIO_TEST("Manejo salas.");
        
	void sala_vacia() {
		DebeSerCierto(capacidad() == 0);
		DebeSerCierto(asientos_libres() == 0);
		DebeSerCierto(asientos_ocupados() == 0);
	}

	void sala_vacia_eliminada() {
		crea_sala(3);
		elimina_sala();
		DebeSerCierto(capacidad() == 0);
                DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 0);
	}

	void sala_llena() {
		crea_sala(3);
		DebeSerCierto(capacidad() == 3);
                DebeSerCierto(asientos_libres() == 3);
                DebeSerCierto(asientos_ocupados() == 0);
		elimina_sala();
	}

	void sala_asientos_negativos() {
		crea_sala(-3);
		DebeSerCierto(capacidad() == 0);
                DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 0);
		elimina_sala();
	}

	void elimina_sala() {
		elimina_sala();
		DebeSerCierto(capacidad() == 0);
                DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 0);
	}

	sala_vacia();
	sala_vacia_eliminada();
	sala_llena();
	sala_asientos_negativos();
	elimina_sala();
	
	FIN_TEST("Manejo salas.");
}

void tests_manejo_asientos() {
        INICIO_TEST("Manejo asientos.");

	void sala_vacia() {
		DebeSerCierto(reserva_asiento(1) == -1);
		DebeSerCierto(libera_asiento(1) == -1);
	}

	void sala_sin_asientos() {
		crea_sala(0);
		DebeSerCierto(reserva_asiento(1) == -1);
		DebeSerCierto(libera_asiento(1) == -1);
		elimina_sala();
	}

	void sala_con_asientos() {
		crea_sala(3);

		// Prueba primera posicion
		DebeSerCierto(reserva_asiento(1) == 0);
		DebeSerCierto(libera_asiento(0) == 1);

		// Prueba ultima posicion
		reserva_asiento(1);
		reserva_asiento(2);
		DebeSerCierto(reserva_asiento(3) == 2);
		DebeSerCierto(libera_asiento(2) == 3);

		// Prueba media posicion
		reserva_asiento(3);
		DebeSerCierto(libera_asiento(1) == 2);
		DebeSerCierto(reserva_asiento(2) == 1);

		elimina_sala();
	}

	void sala_asientos_negativos() {
		// Sala vacia
		DebeSerCierto(libera_asiento(-1) == -1);
		
		// Sala llena
		crea_sala(3);
		reserva_asiento(1);
		reserva_asiento(2);
		reserva_asiento(3);
		DebeSerCierto(libera_asiento(-1) == -1);
	}

	sala_vacia();
	sala_sin_asientos();
	sala_con_asientos();
	sala_asientos_negativos();
	
	FIN_TEST("Manejo asientos.");
}

void tests_info_sala() {
        INICIO_TEST("Info sala.");
        
	void sala_vacia() {
		DebeSerCierto(asientos_libres() == 0);
		DebeSerCierto(asientos_ocupados() == 0);
		DebeSerCierto(capacidad() == 0);
	}

	void sala_sin_asientos() {
		crea_sala(0);
		
		DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 0);
                DebeSerCierto(capacidad() == 0);
		
		elimina_sala();
	}
	
	void sala_con_1_asiento() {
		crea_sala(1);

		// Vacío
		DebeSerCierto(asientos_libres() == 1);
                DebeSerCierto(asientos_ocupados() == 0);
                DebeSerCierto(capacidad() == 1);
		
		// Lleno
		reserva_asiento(1);
		DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 1);
		
		elimina_sala();
	}

	void sala_con_varios_asientos() {
		crea_sala(3);

                //Vacío
                DebeSerCierto(asientos_libres() == 3);
                DebeSerCierto(asientos_ocupados() == 0);
                DebeSerCierto(capacidad() == 3);
		DebeSerCierto(estado_asiento(0) == -1);

                // Medio
		reserva_asiento(1);
                DebeSerCierto(asientos_libres() == 2);
                DebeSerCierto(asientos_ocupados() == 1);
		DebeSerCierto(estado_asiento(0) == 1);
		DebeSerCierto(estado_asiento(1) == -1);

		// Lleno
		reserva_asiento(2);
		reserva_asiento(3);
                DebeSerCierto(asientos_libres() == 0);
                DebeSerCierto(asientos_ocupados() == 3);
		DebeSerCierto(estado_asiento(1) == 2);
		DebeSerCierto(estado_asiento(2) == 3);

		// Elimina medio
		libera_asiento(2);
		DebeSerCierto(asientos_libres() == 1);
                DebeSerCierto(asientos_ocupados() == 2);
		DebeSerCierto(estado_asiento(2) == -1);

                elimina_sala();

		// Fuera de rango
		DebeSerCierto(estado_asiento(4) == -1);
		DebeSerCierto(estado_asiento(-1) == -1);

	}

	sala_vacia();
	sala_sin_asientos();
	sala_con_1_asiento();
	sala_con_varios_asientos();
	
	FIN_TEST("Info sala.");
}

void ejecuta_tests ()
{
	test_ReservaBasica();
	// Añadir nuevos tests
	tests_info_sala();
	tests_manejo_asientos();
}

int main()
{
	puts("Iniciando tests...");
	
	ejecuta_tests();
	
	puts("Batería de test completa.");
	
	return 0;
}
