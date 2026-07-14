# 🗳️ Votaciones AEIS: Sistema de Voto Electrónico (Parte 2)

Este repositorio contiene la segunda etapa del proyecto práctico desarrollado para la asignatura de **Programación I (ICCD144)** de la carrera de Ingeniería de Software / Ciencia de Datos / Computación. 

El sistema implementa una solución de voto electrónico persistente y robusta utilizando el lenguaje C, aplicando metodologías de programación estructurada y control de versiones con Git.

---

## 👥 Integrantes
* **Anderson Verdezoto**
* *[Inserta aquí los nombres de tus compañeros de grupo]*

**Docente:** Ing. Thomás Borja, MSc.  
**Institución:** Escuela Politécnica Nacional (EPN)

---

## 🛠️ Tecnologías y Requerimientos
* **Lenguaje:** C estándar
* **IDE Oficial:** Visual Studio Code[cite: 1]
* **Control de Versiones:** Git & GitHub[cite: 1]

---

## 🚀 Características y Módulos Implementados

De acuerdo con los objetivos del proyecto, la aplicación se divide en módulos independientes bien definidos[cite: 1]:

1. **Gestión de Datos y Persistencia:** Carga y guardado de votantes habilitados en el padrón electoral (`padron.txt`) y persistencia multiformato[cite: 1].
2. **Motor de Búsqueda:** Implementación de algoritmos de búsqueda para validar de manera inmediata si un ciudadano se encuentra habilitado en el padrón electoral[cite: 1].
3. **Ranking Electoral (Ordenamiento):** Clasificación del conteo de votos del más votado al menos votado utilizando algoritmos de ordenamiento eficientes para definir a los ganadores de la AEIS[cite: 1].
4. **Módulo de Reportes:** Generación automática de actas de escrutinio y reportes finales en disco[cite: 1].
5. **Auditoría con Recursividad:** Integración de lógica recursiva para funciones de auditoría y suma acumulada de actas electorales por jurisdicción[cite: 1].

---

## 📂 Estructura Modular del Código

El proyecto sigue una arquitectura limpia de desarrollo, separando la definición de contratos de funciones en archivos de cabecera (`.h`) y la implementación lógica en archivos fuente (`.c`)[cite: 1]:

* `main.c`: Punto de entrada principal y flujo del programa.
* `gestion.c` / `gestion.h`: Manejo de estructuras y administración dinámica.
* `busqueda.c` / `busqueda.h`: Algoritmo de búsqueda de votantes por cédula/ID[cite: 1].
* `ordenamiento.c` / `ordenamiento.h`: Algoritmo para jerarquizar los candidatos y resultados[cite: 1].
* `reportes.c` / `reportes.h`: Generación y exportación de actas y simulaciones persistentes[cite: 1].