<!DOCTYPE html>
<html lang="it">
    <head>
        <title>AreaUtente-GreenPark</title>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script type="text/javascript" src="prenotazione.js"></script>
		<link rel="stylesheet" type="text/css" href="navbar.css" />
		<link rel="stylesheet" type="text/css" href="areaUtente.css" />
		<link rel="stylesheet" type="text/css" href="index.css" />
        <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined">
        <link rel="stylesheet" type="text/css" href="index.css" />
    </head>
    <body>
    <section id="footer_buster">
        <?php 
			session_start();
			if(isset($_SESSION['username'])){
				$user = $_SESSION['username'];
			}else{
				$user ="";
			}

			if(isset($_SESSION['ruolo'])){
				$role = $_SESSION['ruolo'];
			}else{
				$role = "light";
			}
            ?>
    
            <header class="menubar">
                <div id="logo-container">
                    <img title="logo" class="logo" src="img/greenpark_logo.png" width="180">
                    <span onClick="showMenuBar()" id="hambuger" class="material-symbols-outlined">
                                menu
                    </span>
                </div>
                <nav>
                    <ul class="menu">
                        <li><a class="in_this_page" href="index.php">Home</a></li>
                        <li><a href="prenotazione.php">Prenotati</a></li>
                        <li><a href="chiSiamo.php">Chi siamo</a></li>
                    </ul>
                
                </nav>
                <?php 
    
                    $menu = '
                    <ul class="menu" id="right-menu">
                        <li>	
                            <a class="menu-item" href="areaUtente.php">
                                Ciao, '.$user.'
                            </a>
                        </li>
                        <li>
                            <a class="menu-item" href="logout.php">
                                Logout
                            </a>
                        </li>
                    </ul>
                    </div>
                    <div class="log-anchor" id="logout"><a href="logout.php"><button class="responsive-button">Logout</button></a></div>
                    ';
    
                    switch($role){
                        case "light":
                            echo '<div class="log-anchor"><a href="autenticazione.php"><button class="responsive-button">Login</button></a></div>';
                            break;
                        case "stdrd":
                            echo $menu;
                            break;
                        case "staff":
                            echo $menu;
                            break;
                    }
                ?>
                
            </header>
		
		<div id="main">
			<center>
                <?php

                    require 'db.php';
                    $query_utente = "SELECT * FROM Utente WHERE username=$1;";
                    $prep_utente = pg_prepare($connection, "dati_utente", $query_utente);
                    
                    $ret_utente = pg_execute($connection, "dati_utente", array($user));
                    if($ret_utente){
                        $dati_utente = pg_fetch_assoc($ret_utente);
                        $nome = $dati_utente['nome'];
                        $cognome = $dati_utente['cognome'];
                        $telefono = $dati_utente['telefono'];
                        $email = $dati_utente['email'];
                    }
                    $query_pren = 'select id_tavolo as "ID Tavolo", 
                        data as "Data",
                        orario as "Ora",
                        cognome_utente as "Cognome", 
                        telefono_utente as "Telefono", 
                        nome_utente as "Nome",
                        intolleranze as "Intolleranze",
                        posti as "Numero persone",
                        id_prenotazione as "ID Prenotazione"
                        from prenotazione
                        where telefono_utente=$1';

                    $prep = pg_prepare($connection,"prenotazioni_utente",$query_pren);
                    $ret = pg_execute($connection, "prenotazioni_utente",array($telefono));


                    if(isset($_GET['idbook'])){
                        $query_elimina_prenotazione = "Delete from Prenotazione where id_prenotazione=$1";
                        $prep_elimina_prenotazione = pg_prepare($connection, "delete_prenotazione", $query_elimina_prenotazione);
                        pg_execute($connection,"delete_prenotazione",array($_GET['idbook']));
                        header("Refresh:0; url=areaUtente.php");
                    }

                    echo '<h2 id="titleGenerale">Bentornato/a '.$user.'!</h2><br>';

                    
                    $counter = 0;
                    if(pg_num_rows($ret) == 0){
                        //visto che non c'è niente nel risultato della query, non posso neanche  ricevere il titolo delle colonne, quindi le scrivo a mano  
                        echo "Non hai prenotazioni!";
                    }
                    echo '<table class="tabellaTavoliUtente" border=1>';
                    while(($singola_prenotazione = pg_fetch_assoc($ret)) != false){    
                        echo "<tr>";
                        if ($counter == 0){
                            foreach($singola_prenotazione as $key => $value){
                                echo "<th>".$key."</th>";
                            }
                            echo "</tr>";
                        }
                        
                        foreach($singola_prenotazione as $key => $value){
                            if ($key == "ID Tavolo")$idtavolo = $value;
                            if ($key == "ID Prenotazione"){
                                $idprenotazione = $value;
                            }
                            if ($value == ""){
                                $value = "<em>N.D.</em>";
                            }
                            echo "<td>".$value."</td>";
                        }
                        echo '<td><center><a href="areaUtente.php?idbook='.$idprenotazione.'"><button id="elimina">Elimina</button></a></center></td>';
                        echo "</tr>";
                        $counter++;
                    }
                    echo "</table>";
                    
                ?>
            </center>
        </div>
    </body>
    </section>
	<footer>
        <div>Universit&agrave; degli studi di Salerno, DIEM A.A 21/22 </div>
        <div>Battipaglia Valerio, Caso Antonio, D'Angelo Antonio, Dell'Orto Giuseppe Maria</div>
    </footer>
</html>