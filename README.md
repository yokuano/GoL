# **Jeu de la vie**


Ce **[depot git](https://git.unistra.fr/bendriss/tech-dev-rendu-jeu-de-la-vie)** contient l'ensemble du code source du Jeu de la vie. Vous trouverez plus bas dans ce fichier des explcations sur les points suivants:

- Le fonctionement du jeu De La Vie
- Générer l'executable et l'utiliser
- Fonctionalitées disponibles dans le makefile
- Notation des versions

Prérequis
---------
Vous aurez besoin des paquets suivants pour utiliser l'executable, les commande pour les installer sur ubuntu vous sont fournis:
##### GCC et make
```
sudo apt install build-essential
```

##### Doxygen
```
sudo apt install doxygen
```



## Jeu de la Vie: quesquekoi??

Le jeu de la vie à été définie par le mathématicien anglais **John Conway** dans les années 70. C'est un **automate céllulaire** imaginé dans le but de résoudre un problème mis en évidence par John Von Neumann (c'est le "papa" de l'informatique moderne).  
Le jeu est constitué d'une grille à 2 dimmensions, et chaque case correspond a une cellule. Ces cellules peuvent être dans deux états: **vivante ou morte**.  
Les cellules peuvent **évoluer selon des règles d'évolution**:
- Les **voisines d'une cellule sont les 8 autres cellules qui l'entoure**, comme illustré sur l'image du dessous. (A gauche, voisinage non cyclique et à droite, voisinage cyclique)

![](https://media.discordapp.net/attachments/879749492868526150/901791645899579402/unknown.png)
- Une cellule **morte** à un instant *t* **devient vivante** à l'instant *t+1* si et seulement si elle possède exactement **3 cellules voisines**
- Une cellule **vivante** à un instant *t* **reste en vie** à l'instant *t+1* si et seulement si elle possède **2 ou 3 cellules voisines**, sinon elle **meurt** de surpopulation (voisins>3) ou d'isolement (moins de 2 voisins)

Voici une ilustration de ces règles:  
![](https://cdn.discordapp.com/attachments/879749492868526150/901789717203386398/unknown.png)

## Génerer l'executable et l'utiliser
Maintenant que vous savez comment le jeu fonctionne, il est temps **d'utiliser l'executable**:  
- Télécharger l'archive du depot git et l'extraire
- Lancez un terminal et faites du **dossier que vous venez d'extraire votre repertoir courant**
- Lancez la compilation à l'aide de la commande **make**
- Maintenant, utilisez la commande suivante, en remplacant [n] par un **nombre entre 1 et 7**

```
./main ./grilles/grille[n].txt
```
Le terminal ressemblera alors a ca:  
![](https://media.discordapp.net/attachments/879749492868526150/901802847807606895/unknown.png)

Les cellules contenant un 'O' sont **les cellules vivantes**. Les cellules vièrges sont quant à elles **mortes**.\
A partir de la, un ensemble d'options vous sont offertes pour faire évoluer le jeu:

### Faire évoluer l'environement
Il est possible de **faire évoluer l'environement en appuyant sur la touche entrée**, par exemple, si on appuye sur la touche entrée, on obtient ce resultat:

![](https://media.discordapp.net/attachments/879749492868526150/901803303355166730/unknown.png)  
Le nombre d'évolution à augmenté de 1, et notre environement a suivi les règles d'évolution énnoncé plus haut.

### Activer/désactiver le villeilssement des cellules
Vous avez la possibilité **d'afficher l'age des cellules présente dans votre grille**. Il vous suffit **d'appuyer sur la touche v** puis entrée:

![](https://media.discordapp.net/attachments/879749492868526150/901810177420976148/unknown.png)  
Les cellules **d'age 0 sont celles qui viennent de naitre**. Les cellules **d'age 1 sont celle qui on vecu une évoultion**, et ainsi de de suite..

### Charger une nouvelle grille

Vous en avez marre de la grille actuellement sur votre terminal? Ca tombre bien, vous avez la possibilité de **charger une nouvelle grille, sans relancer l'exécutable**. Pour faire ca, **appuyez sur la touche n** puis entrez. Votre terminal ressemblera à ca:  
![](https://media.discordapp.net/attachments/879749492868526150/901817907946856458/unknown.png)

Ensuite, entrez le **chemin vers la grille** que vous souhaitez charger:
```
Entrez le chemain de la grille: ./grilles/grille[n].txt
```
Appuyez sur entrée, et voila! Une grille toute neuve:  
![](https://media.discordapp.net/attachments/879749492868526150/901818848125284402/unknown.png)

### Activer/désactiver le voisinage cyclique

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
