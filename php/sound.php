<?php

error_reporting(~E_ALL);

function getsec() {
	$res = explode(" ",microtime());
	$mir = explode(".",$res[0]);
	return $res[1].".".$mir[1];
}

function openfile($file){
	if (file_exists($file))
		$fp = fopen($file,"a");
	else
		$fp = fopen($file,"w");
	return $fp;
}

$record = getsec();
$record .= ";".$_SERVER["REMOTE_ADDR"];

if (isset($_POST["data"])) {
	$file = "log/unknown.log";

	if (isset($_POST["name"])) {
		$file = "log/".$_POST["name"].".log";
	}

	$record .= ";".$_POST["data"];
	$record .= "\r\n";

	$fp = openfile($file);
	fwrite($fp,$record);
	fclose($fp);
	echo "Data received.";
} else echo "No data\n";
?>
