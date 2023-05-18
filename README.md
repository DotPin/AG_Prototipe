# Prototipo inicial de Algoritmo Genético

***
## Objetivo:

- Mostrar el funcionamiento del algoritmo genético basado en un tipo de inteligencia artificial basada en la teoría básica biología.

## Funcionamiento:

- Desarrollo realizado en GNU Linux.

### Requisitos:

- Haber instalado 'build-esentials' como gestor de compilador para C++.
- Contar con herramienta terminal.
- Algún editor de texto para modificar instrucciones.

### Consideraciones:

- Al interior del archivo 'genetico.cpp', se encuentra:
	- En la línea 26 el parámetro de la probabilidad de mutación.
	- En la línea 27 el parámetro de la probabilidad de cruzamiento.

- Alternativo:
	- Línea 31 valor de precisión en la cantidad binaria para los cromosomas.
	- Delay para despliegue de datos línea 603-606.

### Compilación:

- Abrir terminal y teclear en el directorio donde se encuentre la carpeta  "module" y el archivo "genetico.cpp"
	- $g++ module/Aleatorio.cpp genetico.cpp -o archivo

- Al realizar el proceso de compilación satisfactoriamente, generará un archivo binario lenguaje máquina llamado "archivo", cual es un ejecutable.

- Para ejecutar, en terminal tipee:
	- $./archivo

- Solicitará la cantidad de indiviuos a usar y el grado de exigencia a minimizar con valor < 0.




