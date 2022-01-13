<h1 align="center"> MicroMouse-Evolutivo </h1>

![Badge License](https://img.shields.io/github/license/faffonso/MicroMouse-Evolutivo?color=g)
![Badge Stars](https://img.shields.io/github/stars/faffonso/MicroMouse-Evolutivo?color=g)
![Badge Last modified](https://img.shields.io/github/last-commit/faffonso/micromouse-evolutivo?style=flat)
![Badge contributors](https://img.shields.io/github/contributors/faffonso/micromouse-evolutivo?style=flat)

<h4 align="center"> 
    :construction:  Projeto em construção  :construction:
</h4>

## Descrição do Projeto

### Overview

Projeto final desenvolvido para disciplina de Sistemas Evolutivos e Aplicados à Robótica (SSC0713) oferecida pelo ICMC-USP. Todos os programas  e algoritmos desenvolvidos na disciplina e nesse projeto possuem apenas fins educacionais. O projeto é um compilado de algoritmos com o intuito de montar um algoritmo evolutivo para resolver o labirinto de competições MicroMouse, como no link: https://en.wikipedia.org/wiki/Micromouse. 

O projeto é divido em diversas pastas neste repositório, onde a pasta **src** fornece a maior parte dos algoritmos, tanto evolutivo quanto para análise de dados. Para sua utilização, há na pasta **header** dois arquvios .h importantes para o funcionamento da pasta src. Além disso, na pastas **obj** encontra-se alguns arquvivos de extensão .o relativos ao Cmake feito, e na pasta **public** imagens dos labirintos utilizados de inspiração, bem como sua implementação em um .txt. Por fim, a pasta **docs** guarda todas as informações necessárias para o funcionamento do site com a interface, a qual é auxiliada pela pasta **assets** com as extensões .svg. No mais, alguns arquvios de extensão .d estão na pasta principal do repositório e sao originário do Cmake.

### Funcionalidades e Resultados




### Parâmetros evolutivos

Os parametros utilizados para montar a parte evolutiva do código estão explicados durante sua implementação, porém cabe, nesse momento, uma breve descrição dos principais.

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

Afim de rodar o código principal evolutivo, pode-se utilizar o terminal integrado do VS code ou o terminal do sistema operacional na pasta do repositório a partir do comando:
~~~
make all && ./MicroMouse_evolutivo
~~~
 
> obs: para problemas em rodar o comando acima, revisar o arquivo "Makefile" e suas chamadas
 
Após o comando acima ser executado, pode-se avaliar as informações obtidas a partir do arquivo *"data_analysis.ipynb"* no path */src/data analysis/*. Recomenda-se, ou utilizar o vs code com a extensão "Jupyter", ou clicando com botão direito no arquivo e selecionando a opção "abrir com navegador". Em ambos os casos o comando de execução está no botão no canto superior da página com nome **Run all**. Vale lembrar que dependendo do número de dados o programa pode levar alguns instantes para ser executado.
 
Outra funcionalidade disponível, após o comando make é observar o labirinto por meio do **site**, para isso, a forma mais fácil é utilizar o arquivo *"index.html"* na pasta */docs/* e clicar no botão direito selecionando a opção "abrir com navegador". A Partir disso, basta utilizar os recursos disponíveis na interface e iniciar a animação.


## Licença

* MicroMouse_evolutivo é GNU General Public License v3.0.
    * O MicroMouse_evolutivo está em "Creative Commons licensed".

## Autores

- @faffonso
- @Felipe-Tommaselli
- @gianvstheworld
