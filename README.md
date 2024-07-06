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

### raylib

* Instale la librería raylib en su computadora siguiendo las instrucciones según su distro:

~~~
https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux
~~~

* Una vez instalado, para compilar un código que utilice esta librería, debe ejecutar el siguiente comando:

~~~
cc nombre_del_archivo.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
~~~

* Para verificar que ha instalado raylib correctamente, compile y ejecute el siguiente ejemplo:

~~~
https://github.com/raysan5/raylib/blob/master/examples/text/text_input_box.c
~~~

### poppler y glib

* Ejecute el siguiente comando en la terminal para instalar las librerías:

~~~
sudo apt-get install libglib2.0-dev libpoppler-glib-dev
~~~

* Ejecute el siguiente comando en la terminal para verificar su correcta instalación:

~~~
dpkg -l | grep libpoppler-glib-dev
dpkg -l | grep libglib2.0-dev
~~~

### Makefile

* Descargue el folder **Automatizacion**

* Ejecute en la terminal el comando *make*

* Ejecute el binario

* Siga las instrucciones de la interfaz gráfica