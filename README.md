# [IE-0117] Proyecto

<div align="center">
    <img src="images/C.png" width="200" height="200">
  <h3 align="center">Lenguaje de programación C</h3>
  <p align="center">
    Lenguaje creado por Dennis Ritchie.
  </p>
</div>

Autores:

|Carné|Nombre|
|---|---|
|B17326|Jun Hyun Yeom Song|
|C33566|Danny Gutiérrez Campos|
|C37259|Rodrigo Sánchez Araya|
|C31824|Sergio Castillo Víquez|

Bienvenidos al repositorio!

Aquí encontrarán el proyecto en C elaborado para el curso de Programación IE-0117, semestre I-2024.

## Instrucciones para el usuario

* Instale la librería raylib en su computadora siguiendo las instrucciones en:

~~~
https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
~~~

* Una vez instalado, para compilar el código ejecute el siguiente comando:

~~~
cc nombre_del_archivo.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
~~~

* Para verificar que ha instalado raylib correctamente, compile y ejecute el siguiente ejemplo:

~~~
https://github.com/raysan5/raylib/blob/master/examples/text/text_input_box.c
~~~

* Instale la libreria poppler en su computadora con base en el siguiente link, tome en cuenta solamente la parte que indica la instalción de Poppler (2.1.1 en caso de Linux) (2.2.1 en caso de Windows):

~~~
https://ucd-dnp.github.io/ConTexto/versiones/master/instalacion/instalacion_popple_teseract_linux.html
~~~

* Una vez instalado, para verificar su correcta descarga ejecute el siguiente comando:

~~~
dpkg -l | grep poppler-utils
~~~

* Si poppler-utils está instalado, deberías ver una línea similar a la siguiente en la salida:

~~~
ii  poppler-utils   0.86.1-0ubuntu1   amd64   PDF utilities (based on Poppler)
~~~


