# MicroMouse-Evolutivo

## Descrição do Projeto

<p align="center">
<img src="http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge"/>
</p>

![Badge License](https://img.shields.io/github/license/faffonso/MicroMouse-Evolutivo?style=plastic)


### Overview

Projeto final desenvolvido para disciplina de Sistemas Evolutivos e Aplicados à Robótica (SSC0713) oferecida pelo ICMC-USP. Todos os programas  e algoritmos desenvolvidos na disciplina e nesse projeto possuem apenas fins educacionais. O projeto é um compilado de algoritmos com o intuito de montar um algoritmo evolutivo para resolver o labirinto de competições MicroMouse, como no link: https://en.wikipedia.org/wiki/Micromouse. 

### Objetivos 

### Resultados

### Parâmetros evolutivos

* Os parametros utilizados para montar a parte evolutiva do código estão explicados durante sua implementação, porém cabe, nesse momento, uma breve descrição dos principais.

## How to run

### Pré requisitos

* **Sistema operacional:** Neste projeto foi utilizado o sistema operacional Linux pela distribuição Ubuntu 20.04 LTS, porém o código é otimizado para outros sistemas convencionais como Windows e MACos.

* **IDE:** O IDE utilizado foi o VScode (Visual Studio Code), o qual pode ser baixado pelo link: https://code.visualstudio.com/download.

* **Extensões**: No VS code serão necessárias as extensões: "C/C++", "C/C++ Extension Pack", "Cmake Tools", "Code Runner", "Jupyter" e "Python".

* **Compilador e Interpretador**: No trabalho utilizou o compilador nativo do Ubuntu 20.04, porém para usuários de Windows, o GCC MinGW-64 é recomendado. Ele pode ser instalado a partir de: https://www.mingw-w64.org/. Para o interpretador em python recomenda-se o Python 3.9.10 64-bit, disponível em: https://www.python.org/.

* **Bibliotecas**: Para os arquivos em python, é necessário instalar as dependencias por meio dos comandos no terminal:

~~~
pip install pandas
~~~
~~~
pip install matplotlib
~~~
~~~
pip install numpy
~~~
~~~
pip install random
~~~
### Execução

* Afim de rodar o código, pode-se utilizar o terminal integrado do VS code ou o terminal do sistema operacional na pasta do repositório a partir do comando:
~~~
make all && ./MicroMouse_evolutivo 
~~~

## Autores

- @faffonso
- @Felipe-Tommaselli
- @gianvstheworld