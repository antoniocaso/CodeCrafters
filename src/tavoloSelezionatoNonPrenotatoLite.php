
<?php
if(isset($_GET['id'] )){

	$id_tavolo_selezionato = $_GET['id'];
	echo "Hai selezionato il tavolo con ID: ".$id_tavolo_selezionato.' per la data: '.$dataPrenotazione;
	echo '<br><br>';
	$query_check_orario_prenotazione = "select * from Prenotazione where data='". $dataPrenotazione."'"." and id_tavolo = ".$id_tavolo_selezionato;
	$ret = pg_query($connection, $query_check_orario_prenotazione);

	$stampaOrario = array();
	$stampaOrario[19] = true;
	$stampaOrario[20] = true;
	$stampaOrario[21] = true;
	$stampaOrario[22] = true;
	$stampaOrario[23] = true;
	$stampaOrario[24] = true;

	while(($ora_occupata = pg_fetch_assoc($ret)) != false){
		if($ora_occupata['orario'] == "19:00:00") $stampaOrario[19] = false;
		if($ora_occupata['orario'] == "20:00:00") $stampaOrario[20] = false;
		if($ora_occupata['orario'] == "21:00:00") $stampaOrario[21] = false;
		if($ora_occupata['orario'] == "22:00:00") $stampaOrario[22] = false; 
		if($ora_occupata['orario'] == "23:00:00") $stampaOrario[23] = false; 
		if($ora_occupata['orario'] == "24:00:00") $stampaOrario[24] = false; 
	}
?>
<div id="form_pren">
	<center>
	<form id="formPrenotazioneLite" method="post" action="prenotazione.php<?php echo '?id='.$id_tavolo_selezionato.'&dataPrenotazione='.$dataPrenotazione;?>"> 
		<label for="cognome">Cognome<br>
			<input class="inputForm" minlength="2" oninput="lengthCheck(this, 20)" autofocus id="cognome" name="cognome" type="text" onkeypress="return onlyCharKey(event)" required/>
		</label>
		<br><br>
		<label for="telefono">Telefono<br> 
			<select class="inputForm">
				<?php for($i = 30; $i <= 50; $i++){
					echo '<option value ="';
					echo $i;
					echo '"';
					if ($i == 39) echo " selected";
					echo ">+".$i."</option>";
				}?>
			</select>
		</label>
		<input class="inputForm" autofocus id="telefono" name="telefono" type="tel"  minlength="9" oninput="lengthCheck(this, 10)" onkeypress="return onlyNumberKey(event)" required/></label>

		<br><br>

		<?php 
			$query_num_posti = "Select * From Tavolo Where id_tavolo='".$id_tavolo_selezionato."'";
			$ret_num_posti = pg_query($connection,$query_num_posti);
			$num_posti = pg_fetch_assoc($ret_num_posti);         
		?>
		<label for="posti">Posti<br>
			<input class="inputForm" autofocus onKeyDown="return false" id="posti" name="posti" type="number" step="1" min="<?php echo ($num_posti['posti'])-1;?>" max="<?php echo $num_posti['posti'];?>" value="<?php echo $num_posti['posti'];?>" required/>
		</label>

		<br><br>

		<label for="ora">Ora<br>
			<select class="inputForm" id = "ora" name ="ora">
					<?php
						for ($i=19; $i<25; $i++){
							if($stampaOrario[$i] == true) echo ' <option value="'.$i.':00">'.$i.':00</option> ';
						}
					?>                       
			</select>
		</label>

		<br><br>

		<label for="note" >Note<br>
			<input class="inputForm" autofocus id="note" name="note" TYPE="text" placeholder="Inserire eventuali intolleranze o preferenze"/>
		</label>

		<br><br>

		<input type="checkbox" name="trattamento_dati" id="trattamento_dati" required  value="true"> Acconsento al trattamento dei dati personali</input>

		<br><br>

		<input type="button" onclick="checkFormPrenotazioneLight()" name="invio">Conferma prenotazione</button>
		<br>
	</form>
</center>
</div>
<?php } ?>
