<!DOCTYPE html>

<html lang="it">
	<head>
		
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width,initial-scale=1">
		<title>Green Park-Bio Resturant</title>
		<link rel="stylesheet" type="text/css" href="chiSiamo.css" />
		<link rel="stylesheet" type="text/css" href="navbar.css" />
		<link rel="stylesheet" type="text/css" href="index.css" />
		<script type="text/javascript" src="index.js"></script>
		<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
        <link rel="stylesheet" href="https://fonts.googleapis.com/css2?family=Material+Symbols+Outlined">
		<link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons">
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
						<li><a href="prenotazione.php">Prenotati</a></li>
						<li><a class="in_this_page" href="chiSiamo.php">Chi siamo</a></li>
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

			<div id="body">
				<div id="main">
					<center>
					<div class="sezione-descrizioni" id="descrizione">
						<div id="descrizione-item-1">
							<h3> GREEN PARK BIO EVENTI </h3>
							<br><br>
							<p>Il GreenPark è un luogo unico. Un meraviglioso agriturismo
								incastonato tra il verde ed il blu della costiera cilentana.
								A soli 1 km dal Volo dell'Angelo è un luogo perfetto per chi ama 
								la natura in tutta la sua essenza. 
								Dotato di un ampio orto bio, il ristorante propone solamente piatti 
								con materia prima di propria produzione.
								Un'ode alla bellezza e alla modernità, il GreenPark è un connubio 
								perfetto tra la tradizione e la contemporaneità.</p>
							
						</div>
						<div id="descrizione-item-2">
							<img src="img/slide/slide1.jpg">
						</div>
					</div>
					</center>
					<div class="empty-div"></div>
					<center>
					<div class="sezione-descrizioni" id="piatti">
						<div id="piatti-item-1">
							<img src="img/piatti1.JPG">
						</div>
						<div id="piatti-item-2">
							<img src="img/piatti2.JPG">
						</div>
						<div id="piatti-item-3">
							<img src="img/piatti3.JPG">
						</div>
					</div>
					</center>
					<div class="empty-div"></div>
					<center>
					<div class="sezione-descrizioni" id="contatti">
						<div id="contatti-item-1">
							<h3>CONTATTACI ORA</h3>
						</div>
						<div id="contatti-item-2">
						<a href="https://www.facebook.com/GreenParkEventi" id="facebook"><i class="material-icons">facebook</i></a><br><br>
							<i class="material-icons">phone</i>: 0828.831486<br><br>
							<i class="material-icons">email</i>: agriturismogreenpark70@gmail.com<br><br>
						</div>
						<div id="contatti-item-3">
							<iframe src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d2554.4553360542272!2d15.111265179056703!3d40.41380263421586!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x1339573ba4b1bc83%3A0x9b4e8364412037ab!2sBio%20Agriturismo%20Green%20Park!5e0!3m2!1sit!2sit!4v1653689671948!5m2!1sit!2sit" width="600" height="400" style="border:0;" allowfullscreen="" loading="lazy" referrerpolicy="no-referrer-when-downgrade"></iframe>
						</div>
					</div>
					</center>
					<div class="empty-div"></div>
				</div>
			</div>
		</section>
		<footer>
			<div>Universit&agrave; degli studi di Salerno, DIEM A.A 21/22 </div>
			<div>Battipaglia Valerio, Caso Antonio, D'Angelo Antonio, Dell'Orto Giuseppe Maria</div>
    	</footer>
	</body>
</html>
