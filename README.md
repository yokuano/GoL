# **Jeu de la vie**


Ce **[depot git](https://git.unistra.fr/bendriss/tech-dev-rendu-jeu-de-la-vie)** contient l'ensemble du code source du Jeu de la vie. Vous trouverez plus bas dans ce fichier des explcations sur les points suivants:

- Le fonctionement du jeu De La Vie
- Générer l'executable et l'utiliser
- Fonctionalitées disponibles dans le makefile
- Notation des versions

Prérequis
---------
Vous aurez besoin des paquets suivants pour utiliser l'executable, les commande pour les installer sur ubuntu vous sont fournis:
- GCC et make
~~~{.sh}
sudo apt install build-essential
~~~
- Doxygen
~~~{.sh}
sudo apt install doxygen
~~~



## Jeu de la Vie: quesquekoi??

Le jeu de la vie à été définie par le mathématicien anglais John Conway dans les années 70. C'est un automate céllulaire imaginé dans le but de résoudre un problème mis en évidence par John Von Neumann (c'est le "papa" de l'informatique moderne).
Le jeu est constitué d'une grille à 2 dimmensions, et chaque case correspond a une cellule. es cellules peuvent être dans deux états: vivante ou morte. Les cellules peuvent évoluer selon des règles d'évolution:

- Les voisines d'une cellule sont les 8 autres cellules qui l'entoure, comme illustré sur l'image du dessous. (A gauche, voisinage non cyclique et à droite, voisinage cyclique)

![](https://media.discordapp.net/attachments/879749492868526150/901791645899579402/unknown.png)
- Une cellule **morte** à un instant *t* devient **vivante** à l'instant *t+1* si et seulement si elle possède exactement **3 cellules voisines**
- Une cellule **vivante** à un instant *t* **reste en vie** à l'instant *t+1* si et seulement si elle possède **2 ou 3 cellules voisines**, sinon elle **meurt** de surpopulation (voisins>3) ou d'isolement (moins de 2 voisins)

Voici une ilustration de ces règles:

![](https://cdn.discordapp.com/attachments/879749492868526150/901789717203386398/unknown.png)

## Génerer l'executable et l'utiliser
Maintenant que vous savez comment le jeu fonctionne, il est temps d'utiliser l'executable:

- Télécharger l'archive du depot git et l'extraire
- Lancez un terminal et faites du dossier que vous venez d'extraire votre repertoir courant
- Lancer la compilation à l'aide de la commande **make**
- Maintenant, utilisez la commande suivante, en remplacant [n] par un nombre entre 1 et 7
~~~{.sh}
./main ./grilles/grille[n].txt
~~~

***[WIP]***





Explication de la notation des versions du jeu:

Le format sera vx.y.z

-x sera le niveau du jeu, c'est à dire 1, 2, 3, 4 ou 5
-y sera la version d'un certain niveau, par exemple la version 2 du niveau 4 ce note: 4.2.z
-z permet de noter une version qui a légerement changer, sans pour autant avoir un impact consequant sur le code. Par exemple, un petit changement a la version 2 du niveau 3 se note: 3.2.1

Explication arborésance des fichiers:

-Le Doxyfile se trouve dans le fichier "Doccumentation doxyfile"
-Pour ouvrir la doccumentation en html: ouvrir le fichier Doccumentation Doxygen/html/index.html
-Pour avoir le pdf, allez dans le dossier latex, puis faire la commande "make all". Le pdf sera ensuite généré
