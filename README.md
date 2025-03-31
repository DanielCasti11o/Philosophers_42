# Philosophers_42
📌 Roadmap para Philosophers
1️⃣ Estudiar Threads en C (✓)

    ✅ Crear y manejar pthread_create y pthread_join.

    ✅ Implementar una función que se ejecute en varios hilos.

2️⃣ Mutex y Exclusión Mutua (✓)

    ✅ Aprender pthread_mutex_t, pthread_mutex_lock, pthread_mutex_unlock.

    ✅ Usar un mutex para sincronizar la impresión en la terminal.

3️⃣ Comprender el Problema de los Filósofos (🔜)

    🟡 Entender la mecánica:

        Filósofos (threads) comparten tenedores (recursos compartidos).

        No pueden comer sin 2 tenedores.

        Tienen que alternar entre pensar, comer y dormir.

    🟡 Leer el enunciado detalladamente:

        ¿Qué pasa si un filósofo no puede comer?

        ¿Cómo se maneja la simulación?

        ¿Cuándo termina el programa?

4️⃣ Implementar la Estructura de Datos

    🟡 Definir una estructura t_philo que represente a cada filósofo.

    🟡 Crear una estructura t_table para los recursos compartidos (tenedores y mutexes).

5️⃣ Programar la Lógica de los Filósofos

    🟡 Implementar el ciclo de vida: piensan → toman tenedores → comen → sueltan tenedores → duermen.

    🟡 Usar pthread_mutex_t para controlar los tenedores.

6️⃣ Manejar Casos Especiales

    🟡 Evitar deadlocks y race conditions.

    🟡 Implementar un mecanismo para detectar si un filósofo muere de hambre.

7️⃣ Optimización y Tests

    🟡 Revisar si el código funciona bien con 1, 2, 3... filósofos.

    🟡 Optimizar la sincronización para mejorar el rendimiento.
