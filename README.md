# GestionaleSagra
"Gestionale Sagra" è un'applicazione desktop multifunzionale progettata per semplificare la gestione di sagre ed eventi simili. L'interfaccia unificata consente all'amministratore di gestire il catalogo dei prodotti, regolare le quantità, i prezzi, aggiungere nuovi prodotti, come bevande, piatti della cucina o grigliate, ogni tipo con parametri specifici che ne descrivono le caratteristiche particolari.
Inoltre, l'amministratore ha la possibilità di creare il menu selezionando i prodotti dal catalogo e gestire il personale assegnando ruoli "cameriere" o "distributore" agli utenti lavoratori; inoltre ha una panoramica sulle comande esistenti, con dettagli quali “cameriere”, “distributore”, prodotti inclusi e prezzi totali.
Per maggiore chiarezza: un distributore si occupa della preparazione dell’ordine, mentre un cameriere della consegna ai clienti.
Per i cassieri, l'applicazione offre un'interfaccia dedicata per creare comande, assegnare camerieri e distributori e aggiungere o rimuovere prodotti. Il cassiere può visualizzare l'ordine completo con i dettagli dei prodotti, le quantità e il prezzo totale.
Gli utenti con ruoli di cameriere o distributore hanno accesso a una lista delle comande assegnate, consentendo loro di visualizzare i dettagli dell'ordine per prepararlo efficacemente.
Questo progetto mira a  creare un applicazione che sia realmente utilizzabile e che semplifichi la gestione di queste manifestazioni. Inoltre i prodotti di diverse tipologie erano una buona occasione di sfruttare il polimorfismo.

## Funzionalità implementate
Le funzionalità implementative sono suddivise in due categorie: le prime sono funzionali, le seconde estetiche.
Le prime comprendono:
- Creazione, rimozione e modifica di tre diverse tipologie di prodotti presenti nel catalogo
- Impostazione del menu, aggiungendo e rimuovendo prodotti presenti nel catalogo tramite selezione
- Gestione del personale: creazione utenti, eliminazione e modifica del loro ruolo
- Creazione di una comanda, impostazione degli addetti in base al loro ruolo, aggiunta e rimozione di prodotti
- Conversione e salvataggio in formato json
Le funzionalità grafiche:
- Interfaccia di login che permette di accedere a tre interfacce differenti in base all’utente che effettua l’accesso
- L’interfaccia di Amministrazione permette di accedere alle impostazioni del menu, dei prodotti, del personale e permette di avere un overview sulle comande, sugli addetti assegnati e di visualizzare di quali prodotti è composto l’ordine di ciascuna comanda (la visualizzazione è possibile dopo aver selezionato la comanda)
- L’interfaccia di Cassa permette di creare una nuova comanda e di modificare l’ordine dell’ultima; inoltre permette la visualizzazione del prezzo di ogni prodotto e del totale
- nfine l’interfaccia di tipo utente permette ad ogni cameriere o distributore di visualizzare le proprie comande in corso, in tutte le loro caratteristiche

## Configurazione e istruzioni
Il progetto per poter funzionare necessita dell’istallazione di una libreria per la gestione del json. Questi sono i comandi per la macchina virtuale fornita.
```
sudo apt-get install libjsoncpp-dev
sudo ln -s /usr/include/jsoncpp/json/ /usr/include/json
```
Successivamente è necessario configurare i percorsi del file paths.json, che si trova nella directory `Gestionale_sagra`.
Per garantire il funzionamente è necessario inserire percorsi assoluti.
Effettuare l’operazione secondo il seguente esempio:
```
“prodotti”:”/pathTo/Gestionale_sagra/prodotti.json”
```
e così per gli altri file. Infine serve configurare il percorso del file paths.json all’interno del file `pathManager.cpp`.
`pathsJsonFileName = “/pathTo/Gestionale_sagra/paths.json”`.
Il progetto va compilato all’interno della directory `GestionaleSagra_qt` coi comandi `qmake` e `make`.
Per utilizzare il programma e vedere le 3 interfacce differenti si utilizzino le seguenti credenziali:
- username: admin password: **admin**
- username:cassiere password: **cassiere**
- username:Mario Rossi password: **mario123**
