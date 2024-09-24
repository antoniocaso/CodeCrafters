# APS Project Work - WP4

Il software presente in questo archivio consente di simulare il progetto presentato nel project work.
Per avviare il software, bisogna:

-   avviare il server dell'autorità sanitaria eseguendo `cd medical_authority && python3 main.py`
-   scaricare dall'autorità sanitaria l'archivio contenente il Green Pass 2.0 (`user_id` disponibili 000000, 000001, 000002)
-   avviare il server di gioco eseguendo `cd server && python3 main.py`
-   se la porta di default risulta essere occupata è possibile specificare la porta come argomento da linea di comando, es. `-p 12346`
-   copiare la cartella `client` tante volte quanti sono i giocatori che si vogliono simulare
-   per poter simulare una mano è necessario che ci siano almeno due giocatori nella stessa lobby e una lobby può avere al massimo 5 giocatori
-   copiare nella cartella `data` della directory dei client l'estrazione del contenuto dell'archivio Green Pass
-   avviare il client eseguendo `cd [client_dir] && python3 main.py`
