<?php
ini_set('display_startup_errors',1);
ini_set('display_errors',1);
error_reporting(-1);
?>
<?php
if (!isset($_GET["name"])) {
	echo "No name";
	die();
} else {
	$name = $_GET["name"];
}

function getstatus($time) {
	if ((microtime(TRUE)-(double) $time)<2)
		$res="ONLINE";
	else
		$res="OFFLINE";
	return $res;
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
$lastline = getLine("log/$name.log", -1);
$d = explode(";",$lastline);


for ($i=0;$i<count($d)-3;$i++) {
	$data = new point_data;
	$data->x = $i+1;
	$data->y = (double) trim($d[$i+2]);
	$res[]=$data;
}

$pack = [
	"data" => $res,
	"key" => (double) $d[0],
	"status" => getstatus($d[0])
];

echo json_encode($pack);

?>
