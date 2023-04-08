# Présentation

Le General Problem Solver (GPS, 1959) de Newell et Simon, un des tous premiers programmes d'Intelligence Artificielle.

Le GPS est un programme de raisonnement automatique qui applique des règles logiques pour résoudre toutes sortes de problèmes.

Un problème est exprimé sous forme d'un **ensemble de faits initiaux** et d'un **ensemble de buts à atteindre**, ainsi qu'un **ensemble de règles à appliquer** pour, à partir des faits
initiaux, arriver aux buts

## Exemple 

Dans leur article de 1959, Newell et Simon utilisent l'exemple du fiston à emmener à l'école (fichier.txt) où :

la situation initiale est la suivante :

> son at home, have money, have phone book, car needs battery

Le but qu'on veut atteindre est :

> son at school

Pour résoudre le problème, on peut appliquer différentes règles comme celle ci :

```yml
action: drive son to school, #nom de la règle
preconds: son at home,car works, # ne peut s'appliquer que si le fils est à la maison et que lavoiture fonctionne
add: son at school, # Quand on applique cette règle, elle ajoute le fait son at school
delete: son at home, # et enlève le fait son at home
```

## Méthode de résolution 

**Le backtrack** (retour sur trace) consiste à pouvoir remettre en cause des choix fait lors des étapes antérieures de l'exécution d'un algorithme, pour explorer l'espace des solutions possibles.

C'est ce que nous faisons tous les jours lorsqu'on résout des problèmes, mais cela suppose de mémoriser les étapes de la résolution de problème, pour revenir à une étape antérieure.

### illustration 

on imagine qu'il s'agit de trouver son chemin vers un but quand, à chaque carrefour, il y a plusieurs chemins possibles. le principe est comme suit :

```
tantque (but non atteint ET but possible) faire
	si (il existe un chemin non exploré à partir du carrefour courant) alors
		avancer dans ce chemin jusqu'au carrefour suivant
	sinon
		si (on peut reculer au carrefour précédent) alors
			reculer au carrefour précédent
		sinon
			but impossible
		finsi
	finsi
fintantque
```

### Algorithme de backtrack pour le GPS

```
possible ← vrai; 
// indique s'il est encore possible de trouver un chemin jusqu'au but

IR ← 0; // indice à partir duquel on cherche une règle applicable

tantque (les buts ne sont pas atteints ET possible) faire

	si (il existe une règle R applicable d'index i>IR) alors
		appliquer R //ce qui conduit à un nouvel état E={faits, i}
		mémoriser E
		IR ← 0 // au cas où on était en mode backtrack, on réinitialise IR
		
	sinon
		si (il existe un état précédent) alors // on passe en mode backtrack
			IR ← j+1 // j est l'indice de règle de l'état courant E={...,j}
			revenir à l'état précédent // l'état courant est oublié
		sinon
			possible ← faux 
			// plus d'exploration possible dans l'espace de raisonnement
		finsi
		
	finsi
	
fintantque
```


## Trois fichiers de test :

Le dossier comprend trois problèmes fournis dans les fichiers textes :

- **monkeys.txt** : un singe est dans une pièce avec une balle dans la main, il a faim. Une banane est suspendue au milieu de la pièce, et il y a une chaise près de la porte.
- **school.txt** : on doit emmener un enfant à l'école, mais la batterie de la voiture est morte.
- **blocs.txt** : sur une table on a empilé 3 blocs, a sur b, b sur c et c sur la table. On veut qu'à la fin c soit sur b, b sur a et a sur la table.