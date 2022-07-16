## Introduccion
Proyecto final de Algooritmo y estructuras de datos. El objetivo es dada una matriz de '1','0'y'x', donde los '1' representan nodos por donde 
tiene que pasar un Drone, los '0' accesibles y 'x' obstaculos, se deben encontrar TODOS los caminos Hamiltonianos posibles utilizando algoritmos de busqueda en amplitud y profundidad, luego de encontrar los caminos se debe seleccionar el mas corto y devolverlo por consola.

### Caracteristicas
- Algoritmos de busqueda en amplitud y en profundidad
- IF / FOR  
- colas y pilas
- direccionamiento de memoria
- grafos

Para ejecutar correctamente asegurate de configurar bien la siguiente linea 
```
string fileName = "D:\\YOUR_PATH\\test\\txtMap.txt";.
```
#### Analizando la consola...
![imagen 1](/droneFlight/assets/imagen1.png)

- El programa separa los nodos en un nueva matriz, imagen 1.
![Imagen 2](/droneFlight/assets/imagen3.png)

- Cada nodo lo define como un vertice, imagen 2
![Imagen 3](/droneFlight/assets/imagen2.png)

- Ademas procesa separa los obstaculos en una nueva matriz, imagen 2. 
![Imagen 4](/droneFlight/assets/imagen4.png)

- Analiza los posibles caminos que no sean interferidos por ningun obstaculo.
- Luego, nos muestra por consola el camino hamiltoniano mas corto.

