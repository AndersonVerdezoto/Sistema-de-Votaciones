# 🗳️ Votaciones AEIS: Sistema de Voto Electrónico

Este repositorio contiene el desarrollado del proyecto práctico para la asignatura de **Programación I** de la carrera de Ingeniería en Ciencias de la Computación.

El sistema implementa una solución de voto electrónico persistente y robusta utilizando el lenguaje C, aplicando metodologías de programación estructurada y control de versiones con Git.

---

## 👥 Integrantes
* **Anderson Verdezoto**
* **Erick Cuji**
* **Jairo Enríquez**

**Docente:** Ing. Thomás Borja, MSc.  
**Institución:** Escuela Politécnica Nacional (EPN)

---

## 🛠️ Tecnologías y Requerimientos
* **Lenguaje:** C estándar
* **IDE Oficial:** Visual Studio Code
* **Control de Versiones:** Git & GitHub

---

## 🚀 Características y Módulos Implementados

De acuerdo con los objetivos del proyecto, la aplicación se divide en módulos independientes bien definidos

1. **Gestión de Datos y Persistencia:** Carga y guardado de votantes habilitados en el padrón electoral (`padron.txt`) y persistencia multiformato.
2. **Motor de Búsqueda:** Implementación de algoritmos de búsqueda para validar de manera inmediata si un ciudadano se encuentra habilitado en el padrón electoral.
3. **Ranking Electoral (Ordenamiento):** Clasificación del conteo de votos del más votado al menos votado utilizando algoritmos de ordenamiento eficientes para definir a los ganadores de la AEIS.
4. **Módulo de Reportes:** Generación automática de actas de escrutinio y reportes finales en disco.
5. **Auditoría con Recursividad:** Integración de lógica recursiva para funciones de auditoría y suma acumulada de actas electorales por jurisdicción.

---

## 📂 Estructura Modular del Código

El proyecto sigue una arquitectura limpia de desarrollo, separando la definición de contratos de funciones en archivos de cabecera (`.h`) y la implementación lógica en archivos fuente (`.c`):

* `main.c`: Punto de entrada principal y flujo del programa.
* `gestion.c` / `gestion.h`: Manejo de estructuras y administración dinámica.
* `busqueda.c` / `busqueda.h`: Algoritmo de búsqueda de votantes por cédula/ID.
* `ordenamiento.c` / `ordenamiento.h`: Algoritmo para jerarquizar los candidatos y resultados.
* `reportes.c` / `reportes.h`: Generación y exportación de actas y simulaciones persistentes.