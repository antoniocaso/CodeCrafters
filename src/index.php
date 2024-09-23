<!DOCTYPE html>

<html lang="it">
	<head>
		
		<meta charset="utf-8">
		<meta name="viewport" content="width=device-width,initial-scale=1">
		<title>Green Park-Bio Resturant</title>
		<link rel="stylesheet" type="text/css" href="slideshow.css" />
		<link rel="stylesheet" type="text/css" href="navbar.css" />
		<link rel="stylesheet" type="text/css" href="index.css" />
		<script type="text/javascript" src="index.js" ></script>
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
				
		<ul class = "slideshow"> 
			<li> 
				<span> Immagine 01 </span> 
			</li> 
			<li>
				<span> Immagine 02 </span>
			</li> 
			<li>
				<span> Immagine 03 </span>
			</li> 
			<li> 
				<span> Immagine 04 </span> 
			</li> 
			<li>
				<span> Immagine 05 </span> 
			</li> 
			<li>
				<span> Immagine 06 </span> 
			</li> 
		</ul>
	</body>
	</section>
	<footer>
        <div>Universit&agrave; degli studi di Salerno, DIEM A.A 21/22 </div>
        <div>Battipaglia Valerio, Caso Antonio, D'Angelo Antonio, Dell'Orto Giuseppe Maria</div>
    </footer>
</html>
