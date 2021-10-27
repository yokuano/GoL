# **Jeu de la vie**
*v2.8.0*



Ce **[depot git](https://git.unistra.fr/bendriss/tech-dev-rendu-jeu-de-la-vie)** contient l'ensemble du code source du Jeu de la vie. Vous trouverez plus bas dans ce fichier des explcations sur les points suivants:

- Le fonctionement du Jeu de la vie
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

Si vous rencontrez un problème lors de l'instalation de ces packages, rendez vous sur **[ce lien](https://askubuntu.com/questions/378558/unable-to-locate-package-while-trying-to-install-packages-with-apt)**.



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
- Maintenant, utilisez la commande suivante, en remplacant [n] par un **nombre entre 1 et 8**

```
./main ./grilles/grille[n].txt
```
Voici une illustration sur un terminal:

![](https://media.discordapp.net/attachments/879749492868526150/902862396798939146/make_and_use_executable.gif)

Les cellules contenant un 'O' sont **les cellules vivantes**. Les cellules vièrges sont quant à elles **mortes**.\
A partir de la, un ensemble d'options vous sont offertes pour faire évoluer le jeu:

### Faire évoluer l'environement
Il est possible de **faire évoluer l'environement en appuyant sur la touche entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902862810504106024/evolution.gif)  
Le nombre d'évolution à augmenté de 1 à chaque fois que l'on appuie sur entrée, et notre environement a suivi les règles d'évolution énnoncé plus haut.

### Charger une nouvelle grille

Vous en avez marre de la grille actuellement sur votre terminal? Ca tombre bien, vous avez la possibilité de **charger une nouvelle grille, sans relancer l'exécutable**. Pour faire ca, **appuyez sur la touche n puis entrez**. Ensuite, entrez le **chemin vers la grille** que vous souhaitez charger:  
```
Entrez le chemain de la grille: ./grilles/grille[n].txt
```
![](https://media.discordapp.net/attachments/879749492868526150/902863472931516426/load_new_grille.gif)

### Activer/désactiver le villeilssement des cellules
Vous avez la possibilité **d'afficher l'age des cellules présente dans votre grille**. Il vous suffit **d'appuyer sur la touche v puis entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902872568921485322/old_or_not_old.gif)  
Les cellules **d'age 0 sont celles qui viennent de naitre**. Les cellules **d'age 1 sont celle qui on vecu une évoultion**, et ainsi de de suite..

### Activer/désactiver le voisinage cyclique

Vous avez la possiblilité **d'activer et de désactiver le voisinage cyclique** à tout instant, il vous suffit **d'appuyer sur la touche c puis entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902872988486094848/cyclique_or_no.gif)

### Quitter le programme
Si vous souhaitez quitter le programme, il suffit **d'appuyer sur la touche q puis entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902863516929761290/quit.gif)


## Options disponible dans le makefile

- **Générer la doccumentation**
```
make doc
```
Une fois cela fait, un dossier doc sera créer, ouvrez le fichier **index.html** pour avoir accès à la doccumentation

- **Créer une archive tar.gz**
```
make dist
```
L'archive contient les éléments suivants:** /src makefile Doxyfile /grilles README.md**

- **Supprimer les fichiers objets, la doc, l'archive et l'executable du répertoire courant**
```
make clean
```

## Notation des versions du jeu:

Le format sera **vx.y.z**

- **x sera le niveau du jeu**, c'est à dire 1, 2, 3, 4 ou 5  
- **y sera la version d'un certain niveau**, par exemple la version 2 du niveau 4 ce note: 4.2.z  
- **z permet de noter une version qui a légerement changer**, sans pour autant avoir un impact consequant sur le code. Par exemple, un petit changement a la version 2 du niveau 3 se note: 3.2.1  
