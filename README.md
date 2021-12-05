# **Jeu de la vie**
*v5.2.6*


Ce **[depot git](https://git.unistra.fr/bendriss/tech-dev-rendu-jeu-de-la-vie)** contient l'ensemble du code source du Jeu de la vie. 
Voici une liste des points abordés plus bas:

- Une listes des prérequis à installer
- Une brève introduction sur le jeu de la vie
- Générer l'executable
- Controles
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

##### Cairo
```
sudo apt-get install libcairo2-dev
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
Maintenant que vous savez comment le jeu fonctionne, il est temps **d'utiliser l'executable: **  
- Télécharger et extraire l'archive du depot git.
- Lancez un terminal et faites du **dossier que vous venez d'extraire votre repertoir courant**
- Compilez avec make, selon le mode souhaité, puis lancez l'executable. 

##### Mode TEXTE
```
make MODE=TEXTE
./bin/main ./grilles/grille[n].txt              // n est un chiffre entre 1 et 9
```
![](https://cdn.discordapp.com/attachments/662711929260736523/916330188525146152/MODETEXTE_make.mp4)
- Les cellules contenant un 'O' sont **vivantes**. 
- Les cellules vièrges sont **mortes**.
- Les cellules avec un X rouge sont **non viables.**

##### Mode GRAPHIQUE
```
make
./bin/main ./grilles/grille[n].txt              // n est un chiffre entre 1 et 9
```
![](https://cdn.discordapp.com/attachments/662711929260736523/916809756969168926/MODEGRAPH_make_online-video-cutter.com.mp4)
- Les cellules verte sont **vivantes**. 
- Les cellules vides **mortes**.
- Les cellules rouges sont **non viables.**

## Controles

Après avoir compilé et lancé l'executable, vous vous retrouvez face à votre grille. Un ensemble d'options vous sont offertes.  
Ces fonctionalitées sont disponibles en mode texte et en mode graphique:
- Evolution de la grille
- Activer/Désactiver le vieillissement
- Activer/Désactiver le voisinage cyclique
- Calculer l'oscillation d'une grille
- Charger une nouvelle grille

### Mode TEXTE

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

### Activer/désactiver le vieillissement des cellules
Vous avez la possibilité **d'afficher l'age des cellules présente dans votre grille**. Il vous suffit **d'appuyer sur la touche v puis entrée**:

![](https://cdn.discordapp.com/attachments/879749492868526150/903612816953589790/ezgif.com-gif-maker.gif)  
Les cellules **d'age 0 sont celles qui viennent de naitre**. Les cellules **d'age 1 sont celle qui on vecu une évoultion**, et ainsi de de suite..  
Lorsque le vieillissement est activé, une cellule **meurt si elle dépasse 8 évolutions (8 pas de temps après sa naissance)**.

### Activer/désactiver le voisinage cyclique

Vous avez la possiblilité **d'activer et de désactiver le voisinage cyclique** à tout instant, il vous suffit **d'appuyer sur la touche c puis entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902872988486094848/cyclique_or_no.gif)

### Test d'oscillation

Oscillation: periode qui sépare l'apparition entre 2 motifs identique. Le calcul prend en compte l'age des cellules, et le fait qu'un motif oscillant n'apparaisse pas imediatement. Si une grille est vide/stable, le test renvoie 1 par defaut. Si la colonie n'oscille pas et ne meurt jamais, le test renvoie -1. 
Pour lancer un test d'oscillation, appuyez sur la **touche c puis entrez**:

![](https://cdn.discordapp.com/attachments/662711929260736523/916358447266689095/ezgif.com-gif-maker.gif)

### Quitter le programme
Si vous souhaitez quitter le programme, il suffit **d'appuyer sur la touche q puis entrée**:

![](https://media.discordapp.net/attachments/879749492868526150/902863516929761290/quit.gif)


### Mode GRAPHIQUE

La plupart des fonctionalitées sont le memes que celles en mode textes, mais il y'a cependants des différences mineurs, ainsi que qlq fonctionalitées suplémentaires:

### Evolution de la grille

Un clique gauche remplace la touche entrée

### Charger une nouvelle grille

On appuye sur la touche n, puis on appuie sur le numéro de la grille que l'on veut charger sur le clavier (numéro situé au dessus du clavier). Les grilles disponibles restent les meme, grace au touche entre 1 et 9. Si après avoir appuyer sur la touche n on appuye sur une touche qui n'est pas un chiffre, rien ne ce passe et il faut appuyer sur n à nouveau pour choisir une grille

### Changer le mode du fond d'ecran

Appuyer sur la touche D pour faire une transition entre dark mode et light mode. Par defaut, le jeu est en dark mode. La fonctionalité n'a pas trop d'utile, mais sait on jamais si on a des hérétiques qui utilisent light mode 

### Afficher les controles

Appuyer sur la touche CRTL afin d'afficher des informations sur les controles et le code couleur

### Quitter le jeu

Un clique droit permet de quitter le jeu et fermet la fenetre


## Options disponible dans le makefile

- **Générer la doccumentation**
```
make doc
```
Une fois cela fait, **un dossier doc** sera créer, ouvrez le fichier **index.html** dans ce dossier pour avoir accès à la doccumentation

- **Créer une archive tar.gz**
```
make dist
```
L'archive contient les éléments suivants: **/src makefile Doxyfile /grilles README.md**

- **Supprimer les fichiers objets, la doc, l'archive et l'executable du répertoire courant**
```
make clean
```

## Notation des versions du jeu:

Le format sera **vx.y.z**

- **x sera le niveau du jeu**, c'est à dire 1, 2, 3, 4 ou 5  
- **y sera la version d'un certain niveau**, par exemple la version 2 du niveau 4 ce note: 4.2.z  
- **z permet de noter une version qui a légerement changer**, sans pour autant avoir un impact consequant sur le code. Par exemple, un petit changement a la version 2 du niveau 3 se note: 3.2.1 