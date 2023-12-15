# PRACTICA 5: SOLIDO RIGIDO

------------

## Teclas

`1-4` : Disparar diferentes partículas con velocidad y masa distintas

`5` : Crear sistema de partículas o solidos rigidos con un generador de FUENTE

`6` : Crear sistema de partículas o solidos rigidos con un generador de LLUVIA

`7` : Crear sistema de partículas o solidos rigidos con un generador de NIEVE

`8` : Crear sistema de partículas o solidos rigidos con un generador de NIEBLA

`Z` : Añade la fuerza de VIENTO  a todos los sistemas activos

`V` : Añade la fuerza de TORBELLINO a todos los sistemas activos

`X` : Añade la fuerza de EXPLOSION a todos los sistemas activos

`C` : Crea varios MUELLES de partículas en pantalla (borra todo lo demas)

`B` : Crea un SLINKY de partículas en pantalla (borra todo lo demas)

`N` : Crea una FLOTACION de agua y objeto cotidiano (borra todo lo demas)

`M` : Crea una FLOTACION de mercurio y un yunque (borra todo lo demas)

`P` : Aumenta la K de los MUELLES que existan

`O` : Disminuye la K de los MUELLES que existan

`R` : Cambia de modo entre generadores de particulas y solidos rigidos. Particulas

activas por defecto. Modifica el sistema creado por las teclas 5-8.

`Q` : crea un suelo como solido rigido estatico

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

**Anotaciones 1:** al añadir mas de una fuerza cuando hay varios sistemas en pantalla
a la vez puede que el rendimiento baje y bajen mucho los fotogramas por segundo.
Lo mismo ocurre al añadir demasiados sistemas simultáneamente.

**Anotaciones 2:** la pulsacion del teclado esta protegida por un tiempo 
predefinido de 1 segundo. Para cambiarlo, ir a `Data.h` y cambiar el valor 
de la variable `MAX_TIME_KEY`.
