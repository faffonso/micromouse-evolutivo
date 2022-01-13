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

![Exemplo de labirinto](https://user-images.githubusercontent.com/62042164/149367647-4ba8d008-2783-48e0-8a80-9676d314e005.png)

### Funcionamento e Resultados

### Organização

* **assets:** arquivos adicionais
* **docs:** códigos da interface
* **header:** header da parte evolutiva
* **obj:** objs do CMake
* **public:** Imagens e arquvios do labirinto MicroMouse
* **src:** Arquivos source da parte evolutiva
    * **data_analysis:** Jupyter com a análise dos dados
    * arquivos evolutivos e logs
* arquivos gerados pelo Cmake 

### Funcionamento

O funcionamento do código com suas especificidades e demonstrações está explicado no vídeo de apresentação da disciplina:
https://drive.google.com/file/d/1ACR8glyEmO4OqcV5zKy9schgDcGg-833/view

### Parâmetros evolutivos

Os parametros utilizados para montar a parte evolutiva do código estão explicados durante sua implementação, porém cabe, nesse momento, uma breve descrição dos principais.

* **TAMPOP:** Número de indivíduos da população
* **MAX_INFO_LEN:** Número de genes disponíveis para resolver o labirinto (tamanho máximo de informações por cromossomo)
* **GEN_MAX:** Máximo de gerações a serem rodadas
* **MUX_TAX:** Taxa de mutação (quanto de mutabilidade é aplicado no CROSSOVER)

> obs: o N (tamanho do labirinto) é fixo e estipulado pelo Micromouse


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

* **Evolutivo:** Afim de rodar o código principal evolutivo, pode-se utilizar o terminal integrado do VS code ou o terminal do sistema operacional na pasta do repositório a partir do comando:
~~~
make all && ./MicroMouse_evolutivo
~~~
 
> obs: para problemas em rodar o comando acima, revisar o arquivo "Makefile" e suas chamadas
 
* **Análise:** Após o comando acima ser executado, pode-se avaliar as informações obtidas a partir do arquivo *"data_analysis.ipynb"* no path */src/data analysis/*. Recomenda-se, ou utilizar o vs code com a extensão "Jupyter", ou clicando com botão direito no arquivo e selecionando a opção "abrir com navegador". Em ambos os casos o comando de execução está no botão no canto superior da página com nome **Run all**.
 
* **Interface:** Outra funcionalidade disponível, após o comando make é observar o labirinto por meio da **interface do site**, para isso, basta acessar https://faffonso.github.io/micromouse-evolutivo/, selecionar o Database querido e rodar a animação.


## Licença

* MicroMouse_evolutivo é GNU General Public License v3.0.
    * O MicroMouse_evolutivo está em "Creative Commons licensed".

## Autores

- @faffonso
- @Felipe-Tommaselli
- @gianvstheworld
