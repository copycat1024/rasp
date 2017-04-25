<?php
if (!isset($_GET["name"])) {
	echo "No name";
	die();
} else {
	$name = $_GET["name"];
}

if (isset($_GET["getmax"])) {
	$res = filesize("log/$name.log")/117;
	echo $res;
	die();
}

if (!isset($_GET["linenum"])) {
	echo "No line number";
	die();
} else {
	$linenum = $_GET["linenum"];
}

function getsec() {
	$res = explode(" ",microtime());
	return $res[1];
}

class point_data {
	var $x, $y;
}

function getLine($filename, $line) {
	$linelen = 117;
	$size = filesize($filename);
	if ($line < 0) 
		$line += $size/$linelen + 1;
	$fh = fopen($filename, "r");
	if (!$fh) {
		echo "Error open file $filename";
		return;
	}
	fseek($fh, ($line-1)*$linelen);
	$res = fread($fh,$linelen);
	fclose($fh);
	return $res;
}

$res=[];
$lastline = getLine("log/$name.log", $linenum);
$d = explode(";",$lastline);


for ($i=0;$i<count($d)-3;$i++) {
	$data = new point_data;
	$data->x = $i+1;
	$data->y = (double) trim($d[$i+2]);
	$res[]=$data;
}

$pack = [
	"data" => $res,
	"key" => date("d-m-y h:m:s",(double) $d[0])
];

echo json_encode($pack);
?>
