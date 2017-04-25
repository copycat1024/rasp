var chart_wrapper;
var chart_content;
var chart_data;
var time_stamp = 0;
var device_name = "iolaPi";
var mode = "live";
var timer;
var cursor = 0;
var max = 0;

$(document).ready(function(){
   init();
}); 


function gebi(id) {
	return document.getElementById(id);
}

function init() {
	$(".device-option").click(function(){
		change_device(this.innerHTML);
	});
	$("#mode").click(function(){
		toggle_mode();
	});
	chart_content = chart_config();
	chart_wrapper = chart_init(chart_content);
	change_device($(".device-option").first().text());
	timer = setInterval(function() {update_chart();}, 500);
}

function chart_init(content) {
	return new CanvasJS.Chart("chartContainer", content);
}

function chart_config() {
	return {
		theme: "theme1",//theme1
		animationEnabled: false,
		axisY:{
			maximum:300,
		},
		data: [
		{
			type: "line",
			dataPoints: chart_data
		}
		]
	};
}

function chart_draw(data) {
	console_debug(data);
	if (time_stamp < data.key) {
		add_data(data.data);
		time_stamp = data.key;
	}
	set_status(data.status);
	chart_wrapper.render();
}

function chart_clear() {
	time_stamp = 0;
	chart_data = init_data();
	chart_content.data[0].dataPoints = chart_data;
}

function add_data(data) {
	var i=0;
	var data_lim = 100;
	if (chart_data.length > 0) {
		var a = chart_data.slice(-1)[0].x;
		for (i=0; i<data.length; i++)
			data[i].x = data[i].x + a;
	}
	for (i=0; i<data.length; i++)
		chart_data.push(data[i]);
	while (chart_data.length > data_lim) {
		chart_data.shift();
	}
}

function update_chart() {
	var res = [];
	var jqxhr = $.getJSON("live.php?name=".concat(device_name), function(data) {
		chart_draw(data);
		console.log( "success" );
	})
	.done(function() {
		console.log( "second success" );
	})
	.fail(function() {
		console.log( "error" );
	})
	.always(function() {
		console.log( "complete" );
	});
	return;
}

function init_data() {
	var l = [];
	return l;
}

function change_device(name) {
	$("#device").text(name);
	device_name = name;
	chart_clear();
}

function console_debug(data) {
	var b = gebi("console");
	var str = JSON.stringify(data).concat("<br />");
	for (var i=0; i<chart_data.length; i++) {
		str = str.concat(i.toString()," - ", chart_data[i].y.toString(), "<br />");
	}
	b.innerHTML = str;
}

function set_status(status) {
	var a=$("#status");
	a.text(status);
	if (status == "ONLINE") {
		a.css("background", "#008000");
	} else {
		a.css("background", "#ff0000");
	}
}

var reviewtab = "<div class=\"button button-sm\" id=\"previous\">Previous</div>";
reviewtab = reviewtab.concat("<div class=\"button button-sm\" id=\"next\">Next</div><div id=\"time\"></div>");

function toggle_mode() {
	console.log("Click");
	if (mode=="live") {
		clearInterval(timer);
		mode = "review";
		$("#mode").text("Review");
		$("#tab").html(reviewtab);
		start_review();
		$("#next").click(function(){
			change_review(1);
		});
		$("#previous").click(function(){
			change_review(-1);
		});
	} else {
		timer = setInterval(function() {update_chart();}, 500);		
		mode = "live";
		$("#mode").text("Live");
		$("#tab").html("Status: <div class=\"button button-sm\" id=\"status\"></div>");
	}
}

function start_review() {
	var jqxhr = $.getJSON("review.php?name=".concat(device_name.concat("&getmax=1")), function(data) {
		cursor = data;
		max = data;
		load_review();
		console.log( "success" );
	})
	.done(function() {
		console.log( "second success" );
	})
	.fail(function() {
		console.log( "error" );
	})
	.always(function() {
		console.log( "complete" );
	});
}

function load_review() {
	var url = "review.php?name=";
	url = url.concat(device_name);
	url = url.concat("&linenum=");
	url = url.concat(cursor.toString());
	var jqxhr = $.getJSON(url, function(data) {
		$("#time").text(data.key);
		console_debug(data.data);		
		chart_data = data.data;
		chart_wrapper.render();
		console.log( "success" );
	})
	.done(function() {
		console.log( "second success" );
	})
	.fail(function() {
		console.log( "error" );
	})
	.always(function() {
		console.log( "complete" );
	});	
}

function change_review(delta) {
	if ((cursor + delta < max + 1) && (cursor + delta > 0) && (mode == "review")) {
		cursor = cursor + delta;
		load_review();
	}
}