<?php
    
     
    $countSteps = 0;
    $query_pren = 'select id_tavolo as "ID Tavolo", 
    data as "Data",
    orario as "Ora",
    cognome_utente as "Cognome", 
    telefono_utente as "Telefono", 
    nome_utente as "Nome",
    intolleranze as "Intolleranze",
    posti as "Numero persone",
    id_prenotazione as "ID Prenotazione"
    from prenotazione;';

    $ret = pg_query($connection,$query_pren);
    
    if(isset($_POST['idtavolo']) && isset($_POST['data']) && isset($_POST['ora'])){
        
        $query_inserimento_prenotazione = "INSERT INTO prenotazione(id_tavolo,data, orario, cognome_utente, telefono_utente, nome_utente, intolleranze, posti) values($1,$2,$3,$4,$5,$6,$7,$8)";
        $prep = pg_prepare($connection, "inserimento_prenotazione", $query_inserimento_prenotazione);

        if(!empty($_POST['cognome']))
            $cognome = $_POST['cognome'];
        else
            $cognome = "";
        
        if(!empty($_POST['telefono']))
            $telefono = $_POST['telefono'];
        else
            $telefono = "";
        
        if(!empty($_POST['nome']))
            $nome = $_POST['nome'];
        else
            $nome = "";

        if(!empty($_POST['intolleranze']))
            $intolleranze = $_POST['intolleranze'];
        else
            $intolleranze = "";

        if(!empty($_POST['numeropersone']))
            $posti = $_POST['numeropersone'];
        else
            $posti = 0;

        $query_check_presenza = "select * from utente where telefono='".$_POST['telefono']."'";
        $ret_del = pg_query($connection,$query_check_presenza);
        
        //se non c'è l'utente lo inserisco nel database
        if(!pg_fetch_assoc($ret_del)){                   
            $ruolo = "light";
            $query_inserimento_utente = "INSERT INTO utente(cognome, telefono, ruolo) values($1,$2,$3)";
            $prep_utente = pg_prepare($connection, "inserimento_utente", $query_inserimento_utente); 
                
            
            //invio l'utente al DB
            $params_utente = array($_POST['cognome'], $_POST['telefono'], $ruolo);
            $result_utente = pg_execute($connection,"inserimento_utente", $params_utente);
            
            if($result_utente==false){ echo "Registrazione non eseguita!";}
        }
        

        $params = array($_POST['idtavolo'], $_POST['data'], $_POST['ora'], $cognome, $telefono, $nome, $intolleranze, $posti);
        $result = pg_execute($connection,"inserimento_prenotazione", $params);

        if($result==false){ echo "Prenotazione non eseguita!";}
        else { 
            echo "Prenotazione Inserita!"; 
            header("Refresh:0; url=prenotazione.php ");
        }
    }

    echo '<center><h2 id="titleGenerale">Bentornato SuperUser!</h2></center><br>';

    echo '<table class="tabellaTavoliStaff" border=1>';
    
    if(isset($_GET['idbook'])){
        $query_elimina_prenotazione = "Delete from Prenotazione where id_prenotazione=$1";
        $prep_elimina_prenotazione = pg_prepare($connection, "delete_prenotazione", $query_elimina_prenotazione);
        pg_execute($connection,"delete_prenotazione",array($_GET['idbook']));
        header("Refresh:0; url=prenotazione.php");
    }

    $counter = 0;
    if(pg_num_rows($ret) == 0){
        //visto che non c'è niente nel risultato della query, non posso neanche  ricevere il titolo delle colonne, quindi le scrivo a mano  
        echo "<tr><th>ID Tavolo</th>";
        echo "<th>Data</th>";
        echo "<th>Ora</th>";
        echo "<th>Cognome</th>";
        echo "<th>Telefono</th>";
        echo "<th>Nome</th>";
        echo "<th>Intolleranze</th>";
        echo "<th>Numero persone</th>";
        echo "<th>ID Prenotazione</th></tr>";

        $query_tavolo = "select id_tavolo from Tavolo";
        $ret_tav = pg_query($connection,$query_tavolo);
        echo "<tr>";
        echo '<form id="formTabellaTavoliStaff" method="post" action="prenotazione.php">';  
            echo '<td><select id = "idtavolo" name ="idtavolo">';
            while(($result_tav = pg_fetch_assoc($ret_tav)) != false){
                $restv = $result_tav['id_tavolo'];
                echo '<option value="'.$restv.'">'.$restv.'</option>';
            }
            echo '</select></td>';
            echo '<td><input type ="date" id="data" name ="data" value="'.date("Y-m-d").'" required> </input></td>';
            echo '<td><select id = "ora" name ="ora">';
            for ($i=19; $i<25; $i++){
                echo ' <option value="'.$i.':00">'.$i.':00</option> ';
            }
            echo '</select></td>';
            echo '<td><input type ="text" id="cognome" name ="cognome" > </input></td>';
            echo '<td><input type ="numeric" id="telefono" name ="telefono" required > </input></td>';
            echo '<td><input type ="text" id="nome" name ="nome" > </input></td>';
            echo '<td><input type ="text" id="intolleranze" name ="intolleranze" > </input></td>';
            echo '<td><input type ="numeric" id="numeropersone" name ="numeropersone" > </input></td>';
            echo '<td></td>';
            echo '<td><center><input type="button" onclick="checkFormTabellaTavoliStaff()" >Invia</button></center></td>';
             /*Questo qua è il primo "caso" di form, esce quando NON ci sono righe*/ 
        echo "</form>";
        echo "</tr>";
    }

    while(($singola_prenotazione = pg_fetch_assoc($ret)) != false){    
        echo "<tr>";
        if ($counter == 0){
            foreach($singola_prenotazione as $key => $value){
                echo "<th>".$key."</th>";
            }
            echo "</tr>";
            $query_tavolo = "select id_tavolo from Tavolo";
            $ret_tav = pg_query($connection,$query_tavolo);
            echo "<tr>";
            echo '<form id="formTabellaTavoliStaff" method="post" action="prenotazione.php">';  
                echo '<td><select id = "idtavolo" name ="idtavolo">';
                while(($result_tav = pg_fetch_assoc($ret_tav)) != false){
                    $restv = $result_tav['id_tavolo'];
                    echo '<option value="'.$restv.'">'.$restv.'</option>';
                }
                echo '</select></td>';
                echo '<td><input type ="date" id="data" name ="data" value="'.date("Y-m-d").'" required> </input></td>';
                echo '<td><select id = "ora" name ="ora">';
                for ($i=19; $i<25; $i++){
                    echo ' <option value="'.$i.':00">'.$i.':00</option> ';
                }
                echo '</select></td>';
                echo '<td><input type ="text" id="cognome" name ="cognome" > </input></td>';
                echo '<td><input type ="text" id="telefono" name ="telefono" > </input></td>';
                echo '<td><input type ="text" id="nome" name ="nome" > </input></td>';
                echo '<td><input type ="text" id="intolleranze" name ="intolleranze" > </input></td>';
                echo '<td><input type ="numeric" id="numeropersone" name ="numeropersone" > </input></td>';
                echo '<td></td>';
                echo '<td><center><input type="button" onclick="checkFormTabellaTavoliStaff()" >Invia</button></center></td>';
                /*Questo qua è il secondo "caso" di form, esce quando ci sono righe*/ 
            echo "</form>";
            echo "</tr>";
            echo "<tr>";
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
        
        echo '<td><center><a href="prenotazione.php?idbook='.$idprenotazione.'"><button id="elimina">Elimina</button></a></center></td>';
        echo "</tr>";
        $counter++;
    }
    echo "</table>";
?>