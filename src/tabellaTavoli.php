<?php
    echo "<table border=1>";
    echo "<tr>";
     
    $countSteps = 0;
    while(($tavolo = pg_fetch_assoc($ret)) != false){    
        if($countSteps >=3){
            echo "<tr>";
        }
        $id_tavolo = $tavolo['id_tavolo'];
        $query_tavolo = "select count(*) from prenotazione where data ='".$dataPrenotazione."' and id_tavolo='".$id_tavolo."'";
        $retavolo = pg_query($connection,$query_tavolo);
        $numPrenotazioni = pg_fetch_assoc($retavolo);
 
        if(!($numPrenotazioni['count']>=$numOrariDisponibili)){
			
            echo '<td><a id="tavolo'.$id_tavolo.'" href="prenotazione.php?id='.$id_tavolo.'&dataPrenotazione='.$dataPrenotazione.'"><center>';
			
			//echo "<td><center>";
			echo $tavolo["nome"];
			echo "<br>";
			echo "Posti: ".$tavolo['posti'];
			echo "<br>";
			//$query_prenotazione = 'Select * From Prenotazione Where id_tavolo = '.$id_tavolo;
        }
        echo "</center></a></td>";
        $countSteps++;
        if($countSteps >=3){
            $countSteps = 0;
            echo "</tr>";
        }
    }
    echo "</table>";
?>