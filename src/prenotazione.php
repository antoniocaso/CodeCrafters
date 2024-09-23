<!DOCTYPE html>
<html lang="it">
    <head>
        <title>Prenotazione-GreenPark</title>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <script type="text/javascript" src="prenotazione.js"></script>
		<link rel="stylesheet" type="text/css" href="navbar.css" />
		<link rel="stylesheet" type="text/css" href="prenotazioni.css" />
		<link rel="stylesheet" type="text/css" href="index.css" />
		<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined">
    </head>
    <body>
	<section id="footer_buster">
		<?php 
			session_start();
			if(isset($_SESSION['username'])){
				$usern = $_SESSION['username'];
			}else{
				$usern ="";
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
					<li><a href="index.php">Home</a></li>
					<li><a class="in_this_page" href="prenotazione.php">Prenotati</a></li>
					<li><a href="chiSiamo.php">Chi siamo</a></li>
				</ul>
			
			</nav>
			<?php 

				$menu = '
				<ul class="menu" id="right-menu">
					<li>	
						<a class="menu-item" href="areaUtente.php">
							Ciao, '.$usern.'
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


				if(isset($_SESSION['ruolo'])){ //Sarebbe forse meglio porre ruolo a "" quando non è settato, così che poi quando è settato gli si dia altro valore
					if($_SESSION['ruolo']=="staff"){ //Quando ancora non è fatta l'autenticazione la chiave RUOLO non è ancora definita, risolvere mostrando, se non è settato ruolo, direttamente la pagina light
						
						echo '<div id="tabellaTavoliStaffMain">';
							require 'tabellaTavoliStaff.php';
						echo '</div>';

						//HO PREMUTO IL TASTO DI CONFERMA PRENOTAZIONE E QUINDI INVIO AL DB I DATI(UTENTE E PRENOTAZIONE)
						echo '<div id="prenotazioneLite">';
							if(isset($_POST['cognome']) && isset($_POST['telefono']) && isset($_POST['posti']) && isset($_POST['ora'])){
								require 'confermaPrenotazioneLite.php';
							}else{
								require 'tavoloSelezionatoNonPrenotatoLite.php';
							}
						echo '</div>';
					} elseif ($_SESSION['ruolo']=="stdrd") {
						
							echo '<div id="calendario">';
								echo '<div class="calendario-item-1">SCEGLI LA DATA</div>';
								echo '<div class="calendario-item-2">';
								require 'dataPicker.php';
								echo '</div>';
								echo '<div class="calendario-item-3">DI PRENOTAZIONE</div>';
							echo '</div>';
						
						$query = " Select * From Tavolo;";
						$ret = pg_query($connection,$query);
						
							echo '<div id="tabellaTavoli">';
								require 'tabellaTavoli.php';
							echo '</div>';
						
							echo '<div id="prenotazioneStandard">';
								if(isset($_POST['posti']) && isset($_POST['ora'])){
									require 'confermaPrenotazioneStandard.php';
								}else{
									require 'tavoloSelezionatoNonPrenotatoStandard.php';
								}
							echo '</div>';
					}
					else{
							echo '<div id="calendario">';
								echo '<div class="calendario-item-1">SCEGLI LA DATA</div>';
								echo '<div class="calendario-item-2">';
									require 'dataPicker.php';
								echo '</div>';
								echo '<div class="calendario-item-3">DI PRENOTAZIONE</div>';
							echo '</div>';
						
						$query = " Select * From Tavolo;";
						$ret = pg_query($connection,$query);
						
							echo '<div id="tabellaTavoli">';
								require 'tabellaTavoli.php';
							echo '</div>';

						echo '<div id="prenotazioneLite">';
							if(isset($_POST['cognome']) && isset($_POST['telefono']) && isset($_POST['posti']) && isset($_POST['ora'])&& isset($_POST['trattamento_dati'])){
								require 'confermaPrenotazioneLite.php';
							}else{
								require 'tavoloSelezionatoNonPrenotatoLite.php';
							}
						echo '</div>';
						//INSERIRE REQUIRE DI COSE
					}
				} else {
						echo '<div id="calendario">';
								echo '<div class="calendario-item-1">SCEGLI LA DATA</div>';
								echo '<div class="calendario-item-2">';
								require 'dataPicker.php';
								echo '</div>';
								echo '<div class="calendario-item-3">DI PRENOTAZIONE</div>';
						echo '</div>';
					
					$query = " Select * From Tavolo;";
					$ret = pg_query($connection,$query);
					
						echo '<div id="tabellaTavoli">';
							require 'tabellaTavoli.php';
						echo '</div>';
					
						echo '<div id="prenotazioneLite">';
							if(isset($_POST['cognome']) && isset($_POST['telefono']) && isset($_POST['posti']) && isset($_POST['ora'])&& isset($_POST['trattamento_dati']) ){
								require 'confermaPrenotazioneLite.php';
							}else{
								require 'tavoloSelezionatoNonPrenotatoLite.php';
							}
						echo '</div>';
					//INSERIRE REQUIRE DI COSE
					//CONTROLLARE INTOLLERANZA LUNGA
				};
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




