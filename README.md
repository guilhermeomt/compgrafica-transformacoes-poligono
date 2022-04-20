# Transformações de Polígono

Este código-fonte implementa transformações de polígonos utilizando C++ e OpenGL. As transformações disponíveis são:
- Translação
- Rotação
- Escala
- Cisalhamento
- Reflexão

Ao executar o programa, o usuário clicar no eixo cartesiano para formar os vértices do polígono. Ao clicar novamente na opção de Polígono, o polígono será fechado. Em seguida, basta selecionar uma das transformações disponíveis e clicar em um dos vértices do polígono para aplicar a transformação.

Para compilar o código-fonte, execute o comando na pasta raiz do projeto:
```
g++ -o transformacoes src/main.cpp src/window.cpp src/matrix.cpp src/transformation.cpp -lglut -lGL -lGLU
```

Então execute o programa:
```
./transformacoes
```

Também pode ser utilizado o CMAKE para compilar o código-fonte:
```
cmake build
cd build
./compgrafica
```
