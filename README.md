# Prototipo inicial de Algoritmo Genético

Algoritmo que dio inicio (2019) al proyecto de título para optar a la Ingeniería Civil en Informática, prototipo inicial que permitió optar al grado de ingeniero, logrando el proyecto deseado una vez terminado (2022), para iniciar la investigación.

Se deja a dispocisión la versión de prototipo para mejoras que puedan ser sustantivas.

***
## Objetivo:

- Mostrar el funcionamiento del algoritmo genético basado en un tipo de inteligencia artificial con orientación en la teoría básica biológica de la evolución.
- Algoritmo Genético base desarrollado bajo el principio de la siguiente literatura:
	- https://www.researchgate.net/file.PostFileLoader.html?id=5703bd8e4048546d0943c349&assetKey=AS%3A347504454455296%401459862926298

## Funcionamiento:

- Desarrollo realizado en GNU Linux.
- Cuenta con desarrollo propio de un proceso aleatorio determinista por máquina.
- Cuenta con 3 distintos procesos de mutación.
- Proceso de codificación cromosómica es binaria.


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

### Compilación y ejecución:

- Abrir terminal y teclear en el directorio donde se encuentre la carpeta  "module" y el archivo "genetico.cpp"
	- $g++ module/Aleatorio.cpp genetico.cpp -o archivo

- Al realizar el proceso de compilación satisfactoriamente, generará un archivo binario lenguaje máquina llamado "archivo", cual es un ejecutable.

- Para ejecutar, en terminal tipee:
	- $./archivo

- Solicitará la cantidad de indiviuos a usar y el grado de exigencia a minimizar con valor < 0.




