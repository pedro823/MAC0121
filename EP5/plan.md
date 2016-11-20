#Plano de ação: EP5
---


#####escanear todas as posições:
para cada posição, dar uma pontuação de 0 a +inf pra cada uma  
Jogar no local que tem a maior pontuação

__O Que vale como ponto:__
+ impedir uma sequência do inimigo
+ Fazer uma ponte[1]
+ Continuar uma escada[2]
+ Lema da intersecção[3]
+ subparte do lema: Impedir que o inimigo faça uma ponte
+ Completa uma sequencia ganhadora antes do inimigo completar a dele
+ bloqueia um caminho de um inimigo [definir melhor depois]
+ posição estratégica hardwired (14x14 -> (i,j : i + j = 14?)) pensar melhor nisso
+


---

#####Checar se ganhou:
rodar um Dijkstra? tentar chegar do 0,n até o 13,m ou
do n,0 até o m,13

#####Detectar caminhos possíveis
Rodar um backtracking ou algo pra ver se o inimigo tem um caminho possível para ganhar ou se eu tenho um caminho possível

#####Pie rule
Como perceber se é utilizável? contar os pontos de cada lugar antes de começar e ordenar por pontos, ver se a jogada foi nas top5 melhores e trocar caso?

#####Rodapé
[1] Ponte: um grupo de duas pedrinhas em que não há jeito de impedí-las de se conectar.  

      - - -  
     p - -  
    - - p  
[2] Escada: uma sequência de pedrinhas de jogadores diferentes que concorrem em duas linhas paralelas

        - - - -  
       - p b -  
      - p b -  
     - p b -  
[3] Lema da intersecção: quando o inimigo tem dois caminhos
para jogar tal que ele tenha uma vantagem/vitória garantida, deve-se jogar em um local que interfira nos dois caminhos.

        p - - -
       - p - -
      - b - -
     - b - -
Pretas à vencer horizontalmente. As pretas tem quatro subcaminhos de importância:

        p - - -     p - - -     p - - -     p - - -
       - p p p     - p p -     - p - -     - p - -
      - - - -     - - - p     - - p p     - - p -
     - - - -     - - - -     - - - -     - - - p
Em dois desses caminhos ótimos, a posição

       - - - -
      - - - -
     - - - x
    - - - -
aparece e deve ser jogada pelas brancas.


#Plano 2
---

Alpha-beta pruning com análise de tabuleiro completa

+ Um jogador tem uma sequência ganhadora?
+ 
