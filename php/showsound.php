<?php
ini_set('display_startup_errors',1);
ini_set('display_errors',1);
error_reporting(-1);
?>
<?php
function printdevices() {
	$devices = scandir("./log");
	$c = count($devices);
	for ($i = 0; $i < $c; $i++) {
		$file = explode(".",$devices[$i]);
		if ($file[1]=="log")
			echo  "<div class=\"device-option\">".$file[0]."</div>";
	}
}
?>

<!DOCTYPE html>
<html>
<head>
<title>Catch the bug !</title>

<meta name="viewport" content="width=device-width, initial-scale=1">

<link rel="stylesheet" type="text/css" href="showsound.css">

<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.1.1/jquery.min.js"></script>
<script src="http://canvasjs.com/assets/script/canvasjs.min.js"></script>
<script src="showsound.js"></script>

<style>


</style>

</head>
<body>

<div class="row">
	<div id="sideBar" class="col-1">
		Select device:
		<div class="dropdown">
			<div class="button button-sm" id="device">Dropdown</div>
			<div class="dropdown-content"><?php printdevices(); ?></div>
		</div> <br /> <br />
		Mode:<div class="button button-sm right" id="mode">Live</div>
		<hr />
		<div id="tab">Status: <div class="button button-sm" id="status"></div></div>
		<hr />
		<div class="button button-sm" onclick="chart_clear();" >Clear</div>

	</div>

	<div id="myCanvas" class="col-3">
		<div id="chartContainer" ></div>
	</div>
</div>

<div class="row col-4" id="console">
aaaaaaaaaaa
</div>
</body>
</html>
