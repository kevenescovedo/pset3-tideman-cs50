
# PSET 3 Tideman
ocê já conhece as eleições pluralistas, que seguem um algoritmo muito simples para determinar o vencedor de uma eleição: cada eleitor ganha um voto e o candidato com mais votos vence.

Mas o voto de pluralidade tem algumas desvantagens. O que acontece, por exemplo, em uma eleição com três candidatos, e as cédulas abaixo são lançadas?

![Cédulas](https://assets.circle.so/1w2b0ikk0qx9t5q1fnp96roxvvdy)

Uma votação de pluralidade declararia aqui um empate entre Alice e Bob, uma vez que cada um tem dois votos. Mas esse é o resultado certo?

Existe outro tipo de sistema de votação conhecido como sistema de votação por escolha ranqueada. Em um sistema de escolha ranqueada, os eleitores podem votar em mais de um candidato. Em vez de apenas votar na primeira escolha, eles podem classificar os candidatos em ordem de preferência. As cédulas resultantes podem, portanto, ser semelhantes às apresentadas a seguir

![Cédulas Resultantes](https://assets.circle.so/2m24c946ngxm377tmkotrxbaludf)

Aqui, cada eleitor, além de especificar seu primeiro candidato preferencial, também indicou sua segunda e terceira opções. E agora, o que antes era uma eleição empatada, agora pode ter um vencedor. A corrida foi originalmente empatada entre Alice e Bob, então Charlie estava fora da corrida. Mas o eleitor que escolheu Charlie preferiu Alice a Bob, então Alice poderia ser declarada vencedora.

A votação por escolha ranqueada também pode resolver outra desvantagem potencial da votação por pluralidade. Dê uma olhada nas seguintes cédulas.

![Cédulas](https://assets.circle.so/zruuhvo0kvi4w3r7yq9y473dfkfn)

Quem deve ganhar esta eleição? Em uma votação de pluralidade em que cada eleitor escolhe apenas sua primeira preferência, Charlie vence a eleição com quatro votos, em comparação com apenas três para Bob e dois para Alice. (Observe que, se você estiver familiarizado com o sistema de runoff instantâneo,ou eleição em turnos, Charlie também vence nesse sistema). Alice, no entanto, pode razoavelmente argumentar que ela deveria ser a vencedora da eleição em vez de Charlie: afinal, dos nove eleitores, a maioria (cinco deles) preferia Alice a Charlie, então a maioria das pessoas ficaria mais feliz com Alice como o vencedor em vez de Charlie.

Alice é, nesta eleição, a chamada “vencedora Condorcet” da eleição: a pessoa que teria vencido qualquer confronto direto com outro candidato. Se a eleição tivesse sido apenas Alice e Bob, ou apenas Alice e Charlie, Alice teria vencido.

O método de votação Tideman (também conhecido como “pares ranqueados”) é um método de votação de escolha ranqueada que garante o vencedor da eleição de Condorcet, se houver.

De modo geral, o método Tideman funciona construindo um “gráfico” de candidatos, onde uma seta (isto é, aresta) do candidato A ao candidato B indica que o candidato A vence o candidato B em um confronto direto. O gráfico para a eleição acima, então, seria parecido com o abaixo.


![Cédulas](https://assets.circle.so/qbftlc1j9fohs7nl83mbj4df3qah)

A seta de Alice para Bob significa que mais eleitores preferem Alice a Bob (5 preferem Alice, 4 preferem Bob). Da mesma forma, as outras setas significam que mais eleitores preferem Alice a Charlie e mais eleitores preferem Charlie a Bob.

Olhando para este gráfico, o método Tideman diz que o vencedor da eleição deve ser a “fonte” do gráfico (ou seja, o candidato que não tem uma seta apontando para ele). Nesse caso, a fonte é Alice - Alice é a única que não tem uma seta apontando para ela, o que significa que ninguém é preferido frente a frente com a Alice. Alice é, portanto, declarada a vencedora da eleição.

É possível, entretanto, que quando as flechas forem puxadas, não haja um vencedor Condorcet. Considere as cédulas abaixo.

![Cédulas](https://assets.circle.so/8va20dto886f9nsa7zgg9l7dvzdq)

Entre Alice e Bob, Alice tem preferência sobre Bob por uma margem de 7-2. Entre Bob e Charlie, Bob é o preferido em relação a Charlie por uma margem de 5-4. Mas entre Charlie e Alice, Charlie é o preferido a Alice por uma margem de 6-3. Se desenharmos o gráfico, não haverá fonte! Temos um ciclo de candidatos, onde Alice vence Bob que vence Charlie que vence Alice (muito parecido com um jogo de pedra-papel-tesoura). Nesse caso, parece que não há como escolher um vencedor.

Para lidar com isso, o algoritmo Tideman deve ser cuidadoso para evitar a criação de ciclos no gráfico candidato. Como é feito isso? O algoritmo “bloqueia” as setas mais “fortes” primeiro, uma vez que essas são, sem dúvida, as mais significativas. Em particular, o algoritmo do Tideman especifica que as setas de cada “duelo” devem ser "travadas" no gráfico, uma de cada vez, com base na "força" da vitória (quanto mais pessoas preferirem um candidato ao adversário, mais forte será a vitória). Desde que a aresta possa ser travada no gráfico sem criar um ciclo, a aresta é adicionada; caso contrário ,é ignorada.

Como isso funcionaria no caso dos votos acima? Bem, a maior margem de vitória para um par é Alice derrotando Bob, já que 7 eleitores preferem Alice a Bob (nenhuma outra disputa direta tem um vencedor preferido por mais de 7 eleitores). Portanto, a seta Alice-Bob é travada no gráfico primeiro. A próxima maior margem de vitória é a vitória de Charlie por 6-3 sobre Alice, de modo que a flecha é a próxima.

A seguir vem a vitória de Bob por 5-4 sobre Charlie. Mas observe: se adicionássemos uma flecha de Bob a Charlie agora, criaríamos um ciclo! Uma vez que o gráfico não permite ciclos, devemos pular esta borda e não adicioná-la ao gráfico. Se houvesse mais setas a serem consideradas, olharíamos para as próximas, mas essa foi a última seta, então o gráfico está completo.

Este processo passo a passo é mostrado abaixo, com o gráfico final à direita.

![Cédulas](https://assets.circle.so/auljfwcaezpba4v05qm25jt1wai6)

Com base no gráfico resultante, Charlie é a fonte (não há nenhuma seta apontando para Charlie), então Charlie é declarado o vencedor desta eleição.

Colocado de forma mais formal, o método de votação do Tideman consiste em três partes:

**Contagem/Tally**: Uma vez que todos os eleitores indicaram todas as suas preferências, determine, para cada par de candidatos, quem é o candidato preferido e com que margem ele é preferido.

**Classificação/Ordenação/Sort** : Classifique os pares de candidatos em ordem decrescente de força de vitória, onde a força de vitória é definida pelo número de eleitores que preferem o candidato preferido.

**Decisão/Lock**: começando com o par mais forte, passe pelos pares de candidatos em ordem e “trave” cada par no gráfico candidato, contanto que travar nesse par não crie um ciclo no gráfico.

Assim que o gráfico estiver completo, a fonte do gráfico (aquela sem arestas apontando para ele) é a vencedora!


# EXEMPLO
```Run
./tideman Alice Bob Charlie
Número de eleitores: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie
```


