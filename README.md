# Philosophers_42
Proyecto e introduccion a hilos

Roadmap para Philosophers
Antes de Programar
1. Entender el Problema

    Lee el enunciado completo del proyecto para comprender:

        Las reglas del problema (filósofos, tenedores, mesa).

        El objetivo (evitar interbloqueos y condiciones de carrera).

        Los requisitos técnicos específicos (normas de la escuela 42 como restricciones de memoria, etc.).

2. Estudiar Conceptos Necesarios

Dedica tiempo a estudiar estos temas clave:

    Hilos en C:

        Qué son y cómo funcionan (pthread_create, pthread_join).

        Cuándo usarlos.

    Mutexes y Locks:

        Qué es un mutex.

        Cómo usar pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, y pthread_mutex_destroy.

    Problemas Clásicos de Concurrencia:

        Comprender el problema de los "Filósofos Comensales".

        Conceptos de deadlock (bloqueo mutuo), starvation (inaniación), y race conditions.

    Timers en C:

        Uso de gettimeofday o clock_gettime para medir el tiempo.

3. Planificar la Estructura

    Diseña las estructuras de datos:

        Piensa en qué datos necesitará cada filósofo (id, tiempo de inicio, estado, etc.).

        Define estructuras para representar la mesa, los tenedores, y los filósofos.

    Define las relaciones:

        Por ejemplo, cada filósofo necesita dos mutexes (un tenedor izquierdo y derecho).

4. Organiza el Proyecto

    Divide el trabajo en módulos:

        Inicialización (configurar datos y crear hilos).

        Simulación (lógica de los filósofos comiendo, pensando, y esperando).

        Control de sincronización (gestión de mutexes y tiempos).

        Terminación (liberación de recursos y limpieza).

Primeros Pasos al Programar
1. Inicialización

    Objetivo: Configurar los filósofos, mutexes y crear los hilos.

    Crea una estructura básica:

        Define una estructura t_philosopher con los datos del filósofo.

        Define una estructura t_simulation para datos globales como mutexes y tiempos.

2. Hilos y Mutexes

    Implementa la creación de hilos para los filósofos:

    pthread_create(&thread, NULL, philosopher_routine, &philosopher);

    Asegúrate de que cada filósofo pueda acceder a los mutexes de los tenedores que necesita.

3. Simulación de Rutinas

    Implementa la lógica de cada filósofo:

        Pensar.

        Tomar los tenedores (bloquear mutexes).

        Comer.

        Soltar los tenedores (desbloquear mutexes).

        Dormir.

    Usa funciones para dividir estas acciones:

    void *philosopher_routine(void *arg);
    void take_forks(t_philosopher *philo);
    void eat(t_philosopher *philo);
    void put_down_forks(t_philosopher *philo);

4. Control de Tiempos

    Usa gettimeofday o una alternativa para medir los tiempos de comer y dormir.

5. Detección de Muertes

    Implementa un hilo separado o una rutina que monitoree si un filósofo murió porque no comió a tiempo.

6. Liberación de Recursos

    Limpia los mutexes y libera memoria dinámica antes de terminar el programa.

Pasos Finales

    Pruebas y Debugging

        Usa muchos casos de prueba:

            Diferentes números de filósofos.

            Tiempos muy cortos y largos.

        Revisa con herramientas como valgrind para evitar fugas de memoria.

    Optimización

        Revisa si tu solución es eficiente y cumple con las normas del proyecto.

        Evita soluciones que generen "busy waiting" (uso innecesario de CPU).

    Documentación

        Comenta claramente las partes importantes del código.

        Agrega un README con explicaciones y ejemplos de uso.
