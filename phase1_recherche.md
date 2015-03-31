# Table des matières #

# Skyguide #
## Introduction ##

Nous sommes des étudiants de la HES-SO en Ingénierie. Dans le cadre du Projet P1, nous avons été mandaté à réaliser une application.

Celle-ci ayant pour objectif principal de recevoir des valeurs d'un pointeur d'étoiles via un cable RS232 et d'afficher les informations concernant l'étoile pointé dans l'interface.

L'appareil sera quant à lui réaliser pour un autre groupe.

# Qt #

## Introduction ##

Qt est un framework orienté objet et développé en C++. C’est une filiale de Nokia qui développe et améliore le framework. Qt est un projet open source, il est disponible avec différentes licences comme GNU GPL v3 et GNU LGPL 2.1. Autres caractéristiques importante de Qt, c’est qu’il est multiplateforme, il fonctionne aussi bien sous Windows, GNU/Linux que MacOS.
Le framework Qt est divisé en plusieurs modules, dont voici les principaux :
  * qtCore: fonctionnalités de base du framwork
  * qtGui: pour les composants graphiques
  * qtNetwork: pour la communication réseau
  * qtOpenGL: pour utiliser la bibliothèque OpenGL
  * qtSql: pour l’utilisation de base de données SQL
  * qtXml: pour manipuler des fichiers XML
  * qtDesigner: pour étendre les fonctionnalités de Qt Designer
  * qtAssitant: pour utiliser l’aide de Qt
  * qt3Support: pour assurer la compatibilité avec Qt

## Pourquoi avoir choisi le frameworkt Qt ##

Notre projet nous demande de réaliser une interface graphique, une communication avec une base de données, de trouver un moyen d’afficher des étoiles sur une image ou dans une fenêtre et de pouvoir communiquer avec le port série entre deux machine. Le framework Qt contient toutes ces fonctionnalités dont nous avons besoin. Cette une des raisons de notre choix, mais pas seulement:
  * C’est un framework open source
  * C’est un framework multiplateforme
  * Le module QtGui nous sera utile pour l’interface graphique
  * Le module QtSql nous sera utile pour la communication avec notre base de données
  * Qt propose une extension pour la communication RS232 : QExtSerialPort
  * Qt permet de créer des images ou de dessiner n’importe quelle forme sur des fenêtres (module de dessin)

## Exemple d’interface graphique avec Qt ##

### Fichier main.cpp ###

```
#include <QtGui/QApplication> // include pour Qt
#include "mainwindow.h" // include du fichier header de la fenêtre
int main(int argc, char *argv[]) // point d’entrée du programme
{
    QApplication app(argc, argv); // toutes application Qt commence par cette ligne
    MainWindow w; // création d’une fenêtre
    w.show(); // affichage de la fenêtre
    return app.exec(); // quitte le programme
}
```

### Fichier mainwindow.h ###

```
#ifndef MAINWINDOW_H // pour ne pas inclure plusieurs fois le fichier .h
#define MAINWINDOW_H
#include <QMainWindow>
namespace Ui {
    class MainWindow;
}
class MainWindow : public QMainWindow // déclaration de la classe
{
    Q_OBJECT // macro propre à Qt
public:
    explicit MainWindow(QWidget *parent = 0); // constructeur de l’objet
    ~MainWindow();// destructeur de l’objet
private:
    Ui::MainWindow *ui; // objet fenêtre

private slots:
    void pushButtonClicked(); // méthode appelé quand on clique sur le bouton
};
#endif // MAINWINDOW_H

```

### Fichier mainwindow.cpp ###

```
#include "mainwindow.h" // inclure le fichire de déclaration
#include "ui_mainwindow.h"
// définition de la classe qui érite de l’objet QMainWindow
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // connecte le bouton à l’événement clique à la méthode pushButtonClicked()
    connect(this->ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButtonClicked()));
}
MainWindow::~MainWindow() // détruit l’objet à la fin du programme
{
    delete ui;
}

void MainWindow::pushButtonClicked()
{
    // code éxécuté quand on clique sur le bouton
}
```

### Capture d'écran du résultat ###

Capture d’écran de l’application sous Ubuntu. Ce qui prouve bien que Qt fonctionne bien sous GNU/Linux.

![https://skyguide.googlecode.com/svn/wiki/img/cap.jpg](https://skyguide.googlecode.com/svn/wiki/img/cap.jpg)

# Sqlite #

## Introduction ##

SQlLite est une bibliothèque écrite en langage C, qui propose un moteur de base de données relationnelle accessible par le langage SQL. SQLite implémente la majorité des fonctionnalités du standard : SQL2.

SQLite est un projet open source, ce qui permet de l’utiliser aussi bien dans le développement de programme propriétaire que open source.

Une des particularités majeures de SQLite est que contrairement aux bases de donnée traditionnels (MySQL, PostgreSQL, SQLServer, Oracle), SQLite n’utilise pas le schéma habituel client-serveur. En effet, SQLite est directement intégré dans l’application sous forme d’un fichier contenant : table, index, données, types, etc …).

De nombreux logiciel grand public utilise SQLite, on peut citer par exemple : Firefox, Skype, produit d’Apple, d’Adobe ou de Google. Son utilisation est très appréciée aussi dans les systèmes embarqués de par sa légèreté (300 ko). Pour finir de nombreux, framework ou bibliothèque standard de différents langage implémente SQLite, on peut citer par exemple : PHP, Python, C#, Java ou Qt.

## Pourquoi avoir choisi SQLite ? ##

Pour notre projet nous avons besoin de stocker différentes informations sur des étoiles. Notre choix c’est porté sur SQLite pour différentes raisons :
  * C’est une technologie open source
  * C’est une base de donnée "attaché à l’application" et non client-serveur
  * C’est une base de données très simple à utiliser
  * On peut interroger SQLite avec le langage SQL
  * QLite est directement intégré dans le framework Qt

## Utilisation d’SQLite avec le framework Qt ##

### Prérequis ###

  * Le framework Qt (téléchargeable ici : http://www.sqlite.org/download.html)
  * sqlite3.exe (téléchargeable ici : http://qt.nokia.com/downloads)

### Création de la base de données ###
Pour cela il faut utiliser le petit utilitaire sqlite3.exe dans une invite de commande. Il permet de créer la base de données et d’y insérer des requêtes SQL.

### Exemple d’utilisation de sqlite3.exe ###

![https://skyguide.googlecode.com/svn/wiki/img/sql.png](https://skyguide.googlecode.com/svn/wiki/img/sql.png)

Fichiers clients.bd créé:

![https://skyguide.googlecode.com/svn/wiki/img/outpud_sql.png](https://skyguide.googlecode.com/svn/wiki/img/outpud_sql.png)

## Exemple de code avec le framework Qt ##
```

QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); // on choisit SQLite

db.setDatabaseName("test.db"); // le nom de la base de donnée
if (!db.open()) // ouverture de la base de donnée
{
  // erreur de connection
}
QSqlQuery query; // créer une requête
if (query.exec("INSERT INTO clients(prenom_client, nom_client) VALUES(Matthieu, Rossier)"))
{
  // requête SQL bien exécuté
}
else
{
  // erreur dans la requête SQL
}
db.close();
```

# Calculs astronométriques #

## Introduction ##

Pour calculer la position des étoiles, nous avons écrit un programme en C++ pour convertir les valeurs reçues en valeurs utilisables pour déterminer les positions des étoiles.

Comme le groupe IIE n’a pas encore commencé le travail sur le hardware,  nous ne sommes pas en position pour savoir quelles valeurs ils nous enverront. Nous avons donc essayé de deviner, de manière réaliste, quelles unités nous recevront.  Nous avons donc estimé que du GPS nous recevront la latitude et la longitude, et du pointeur, la déclinaison et l’ascension droite. A partir de ceux-ci nous sommes capables de calculer la hauteur et l’azimut, desquelles nous pouvons identifier une étoile. L’heure n’est pas difficile à trouver.

## Expliquons rapidement ce que représentent ces différentes coordonnées ##

Les **latitudes** et les **longitudes** sont un système de coordonnées qui permettent de marquer un point sur la terre.

La **longitude** est un angle calculé horizontalement depuis le centre de la terre, séparant la planète en quartiers, le point d’origine de son calcul est à Greenwich.

La **latitude** est un angle calculé verticalement depuis le centre de la terre, divisant la planète en « tranches ».  Son origine est l’équateur.

L’angle horaire est la différence entre le temps sidéral et son ascension droite. Le temps sidéral est calculé selon le point vernal moyen. Plus explicitement, un jour sidéral sur terre dure 4 minutes de moins qu’un jour comme nous les connaissons, soit  0,9972696 jour solaire.

![https://skyguide.googlecode.com/svn/wiki/img/calcul.png](https://skyguide.googlecode.com/svn/wiki/img/calcul.png)


L’ascension droite et la déclinaison sont comparable à la latitude et la longitude, mais pour la sphère céleste et en utilisant comme point d’origine le point vernal. Ces valeurs nous sont données par le pointeur.

![https://skyguide.googlecode.com/svn/wiki/img/calcul2.png](https://skyguide.googlecode.com/svn/wiki/img/calcul2.png)

Encore une fois, **l’azimut** et la **hauteur** sont des angles calculés depuis le centre d’une sphère. Il est calculé dans le sens des aiguilles d’une montre et depuis le sud géographique, cela présente l’avantage d’avoir l’angle horaire et l’azimut nuls lors du passage de l’astre au méridien.

![https://skyguide.googlecode.com/svn/wiki/img/calcul3.png](https://skyguide.googlecode.com/svn/wiki/img/calcul3.png)

## Calcul de l'azimut et de la hauteur ##

On commence par calculer l’heure sidérale à partir de l’heure, la date et de l’ascension droite.

La hauteur peut être trouvée grâce à la déclinaison, la latitude et l’angle horaire. Les calculs sont effectués en radians.

![https://skyguide.googlecode.com/svn/wiki/img/calcul4.png](https://skyguide.googlecode.com/svn/wiki/img/calcul4.png)


# Versionning #

## Introduction ##

Dans le cadre du Projet P1, nous avons dû choisir une forge ainsi qu’un outil de subversion. Nous avons effectué plusieurs recherches mais notre intention s’est tout particulièrement orientée vers Google Code et TortoiseSVN.

## Google Code ##

Google Code est une application web fourni par google permettant l’hébergement de projet. C’est-à-dire qu’ils offrent l’opportunité à tout chef de projet de publier l’avancement de son projet ainsi que ces codes sources. C’est également dans ce site que sont publiés la majeure partie des API de Google comme Google Maps ou encore Google Earth.

![https://skyguide.googlecode.com/svn/wiki/img/version.png](https://skyguide.googlecode.com/svn/wiki/img/version.png)

### Avantages ###

Les avantages constatés lors de la préparation sont les suivants :
  * Google Code étant une application Web de Versionning offrant la possibilité aux utilisateurs, l’emploi d’un outil de Subversion tels que TortoiseSVN pour la publication des fichiers sources.
  * Les backups sont gérés par le site, c’est-à-dire qu’à chaque nouveau chargement d’un fichier, les versions ultérieures sont gardées dans l’espace de travail.
  * Il y a également la possibilité de créer un wiki pour publier de la documentation concernant le projet ainsi que son développement.
  * Un suivi des modifications est directement affiché sur l’accueil de l’espace de travail, car à chaque téléchargement de fichiers, une description des modifications est demandée à l’utilisateur.

### Les inconvénients ###

Après quelques mois de recherches, aucun inconvénient n’a été constaté mis à part l’obligation d’avoir un compte Gmail pour accéder et modérer l’espace de travail.

## Conclusion ##

Après diverses recherches sur les différents outils disponibles, nous avons retenu Google Code car il nous offrait une grande panoplie d’outils pour la gestion de notre projet et que beaucoup de développeurs utilisait également cette forge sur le web.

![https://skyguide.googlecode.com/svn/wiki/img/version2.png](https://skyguide.googlecode.com/svn/wiki/img/version2.png)

# TortoiseSVN #

TortoiseSVN est un des logiciels client de SVN les plus populaires1.
C'est un logiciel libre distribué selon les termes de la licence GNU GPL.
En s'intégrant dans l'explorateur de Windows, il offre aux utilisateurs de Windows une interface graphique permettant de réaliser la plupart des tâches qu'offre SVN en ligne de commande.

## Les fonctionnalités de TortoiseSVN ##

Voici une courte liste des fonctionnalités  qui propose le client Subversion TortoiseSVN :
  * Intégration dans le shell
  * Recouvrement d'icônes
  * Interface Utilisateur
  * Accès facile aux commandes de Subversion
  * Répertoires versionnés
  * Livraisons atomiques
  * Metadonnées versionnées
  * Gestion cohérente des données
  * Embranchements et étiquetages efficaces

## Recouvrement d'icônes ##

Une des fonctionnalités les plus visibles de TortoiseSVN sont les recouvrements d'icônes qui apparaissent sur les fichiers de votre copie de travail. Celles-ci vous montrent en un clin d'œil quels fichiers ont été modifiés.
Figure 1.0 L'Explorateur montrant le recouvrement d'icônes
TortoiseSVN ajoute une icône de recouvrement à chaque icône de fichier chevauchant l'icône de fichier original. Selon le statut Subversion du fichier, l'icône de recouvrement est différente. Voici quelques exemples :
  * ![https://skyguide.googlecode.com/svn/wiki/img/i.png](https://skyguide.googlecode.com/svn/wiki/img/i.png) : Cela signifie que le statut Subversion est normal.
  * ![https://skyguide.googlecode.com/svn/wiki/img/i2.png](https://skyguide.googlecode.com/svn/wiki/img/i2.png) : Dès que vous commencez à éditer un fichier, le statut change en modifié et l'icône de recouvrement devient alors un point d'exclamation rouge.
  * ![https://skyguide.googlecode.com/svn/wiki/img/i3.png](https://skyguide.googlecode.com/svn/wiki/img/i3.png) : Si un conflit se produit lors d'une mise à jour alors l'icône de recouvrement devient un point d'exclamation jaune.
  * ![https://skyguide.googlecode.com/svn/wiki/img/i4.png](https://skyguide.googlecode.com/svn/wiki/img/i4.png) : Si vous avez verrouillé un fichier et que le statut de Subversion est normal, cette icône de recouvrement vous rappelle que vous devriez relâcher le verrou si vous ne l'utilisez pas pour permettre aux autres utilisateurs de livrer leurs changements.
Et bien d’autres icônes encore comme c’est mentionnée la dessus.


# Communication par RS232 #

## Problématique ##

Les différents systèmes d’exploitation implémentent la plupart des accès aux interfaces RS232. La communication par RS232 à besoins de beaucoup paramètres différents (start/stopbit, baudrate, flowcontrol, etc.), tous ses paramètres doivent configurer manuellement.

## Solution ##

Marco Aeberli a déjà travaillé avec RS232 en combinaison avec Qt. Il apporte la component QSerialDevice, qui est développé avec Qt et sous une licence open source. La component possède une interface en style de Qt, avec signal et slots. QSerialDevice est disponible pour les système exploitation suivre: Win 2K/XP/Vista/7, GNU/Linux distributions, MacOSX .
La première partie de QSerialDevice est utile pour énumèrer tous les Serial Interface qui sont disponible sur l’ordinateur. L’énumération des interfaces sous MacOSx n’est pas encore implémentée. La deuxième partie contient l’interface pour accéder et configurer un port série. Cette partie fonctionne sur toutes les plateformes.
Site d’internet: http://qt-apps.org/content/show.php?content=112039
6.3	Exemple d’utilisation
Pour comprendre comment la communication fonctionne entre deux terminaux par RS232, nous avons développé un petit logiciel pour communiquer entre deux ordinateurs. Pour connecter les deux ordinateurs nous avons utilisé une file null-modem (les deux ordinateurs étaient des maître).

![https://skyguide.googlecode.com/svn/wiki/img/rs2322.png](https://skyguide.googlecode.com/svn/wiki/img/rs2322.png)

### Screenshot ###

![https://skyguide.googlecode.com/svn/wiki/img/rs232.jpg](https://skyguide.googlecode.com/svn/wiki/img/rs232.jpg)

### Code ###
```
//open a connection to the serialport (CONTAINS PSEUDO CODE)
this->serialPort->setDeviceName(SERIALPORT_CONFIGURATION);

if(this->serialPort->open(QIODevice::ReadWrite))
{
	this->serialPort->setBaudRate([BAUDRATE_CONFIGURATION]);
	this->serialPort->setParity([PARITIY_CONFIGURATION]);
	this->serialPort->setDataBits(DATABITS_CONFIGURATION);
	this->serialPort->setFlowControl(FLOWCONTROL_CONFIGURATION);
}

//send an bytearray over the serialport (CONTAINS PSEUDO CODE)
this->serialPort->write(BYTEARRAY2SEND);

//receive a bytearray (CONTAINS PSEUDO CODE)

//connect signal on a slot
connect(this->serialPort, SIGNAL(readyRead()),
		this, SLOT(readIncommingData()));


void readIncommingData()
{
	QByteArray ba = this->serialPort->readAll();
	qDebug(QString::fromUtf8(ba.data()));
}
```