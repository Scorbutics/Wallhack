Utilisation

2 fonctionnalités :
	- Ajout d'une option nommée "Opacity" au menu système de toutes les fenêtres permettant de régler la transparence de ces dernières

	-Par défaut, les fenêtres sur l'OS se lanceront désormais avec une opacité réglable allant de 0% (invisible) à 100% (aucune transparence) dans le premier onglet de l'interface graphique WallhackGUI

	- L'appuie sur "Windows + Alt" permet d'ignorer les évènements sur la fenêtre active au premier plan. L'utilisation du scroll de la souris permet de propager l'effet sur les fenêtres suivantes. Il est possible de modifier ce raccourci dans l'onglet "Wallhack shortcut" de l'application


(La gestion du touchpad n'est pas (encore ?) prise en compte)

_____________________________________

Notes techniques

OS 64 bits :
	Lancer Wallhack.exe dans le répertoire ./bin/x64Compatibility 

OS 32 bits :
	Seul Wallhack.x86.exe dans le répertoire ./bin peut être lancé


La version 64 bits utilise la communication inter-processus entre 3 processus simultanément : Un pour l'interface graphique, un pour la partie logique et un dernier pour le support des application lancées en WOW64 (support 32 bits sur une plateforme 64 bits). La fermeture de la fenêtre entraîne la fermeture des processus fils.

La version 32 bits utilise seulement le processus de l'interface graphique et celui logique.
