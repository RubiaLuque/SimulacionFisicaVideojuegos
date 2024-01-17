# PROYECTO FINAL

------------

## Teclas

`1-3` : Selección de dificultad

`6` : Disparo de una BOLA DE FUEGO

`7` : Disparo de un LÁSER

`8` : Disparo de una BALA 

`9` : Disparo de una FLECHA

--------------------


## Arquitectura

La clase `SceneManager` se encarga de gestionar la creacion, destruccion y 
actualizacion de sistemas. 

Luego, dos clases de sistemas disponibles: sistema de particulas y de solidos 
rigidos. El funcionamiento es casi el mismo.

Se crea un nuevo sistema por cada generador que se quiera crear y las fuerzas
afectan a todos los sistemas presentes y cuyos elementos se encuentren dentro
del radio de efecto.

 ### Generadores:
Existen 2 generadores principales (Uniforme y Gaussiano) que 
heredan de una clase abstracta. Estos que, a su vez son abstractos, tienen dos 
hijos cada uno que se encargan de diferenciar la creacion de particulas o 
solidos rigidos.

### Fuerzas: 
Todas son templates y, por tanto, su definicion se encuentra enteramente
en el archivo de cabecera de cada una. De esta manera, funcionan para 
particulas y solidos rigidos. La clase `ForceRegistry` se encarga de almacenar
las particulas o solidos rigidos con la fuerza que les afecta.

### Clase Particle: 
Tiene toda la funcionalidad basica de las particulas. 

### Clase SolidRigid: 
Idem a la clase particle, pero para la funcionalidad de los
solidos rigidos.

Definicion de un nuevo namespace en `Data.h` que contiene todas las variables 
globales y estaticas del proyecto.

----------------------

**Anotaciones:** la pulsacion del teclado esta protegida por un tiempo 
predefinido de 1 segundo. Para cambiarlo, ir a `Data.h` y cambiar el valor 
de la variable `MAX_TIME_KEY`.
