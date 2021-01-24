$(document).ready(function(){

	var ip = '127.0.0.1:5000';
	var mode = 1;
	var com_port = '0'
	var recognition = new webkitSpeechRecognition();
	recognition.continuous = true;

	$("#recognition").click(function(){
		recognition.onresult = function(event) { 
			console.log(event);
			var res = "";
			for(var i=0; i<event.results.length; i++){
				res = res + event.results[i][0].transcript + " ";
				console.log(event.results[i][0].transcript);
			}
			$("#custom_command_text").val(res);
			recognition.stop();
		}
		recognition.start();
	})

	$("#connect").click(function(){
		com_port = $("#com").val();
		$.post('http://'+ip+'/connect',{'com':com_port});
	})

	$("#custom_command").click(function(){
		var command = $("#custom_command_text").val();
		$("#custom_command_text").val("");
		if (command != ''){
			$("#log").append("-- "+command+"\n");
			$.post('http://'+ip+'/command',{'command':command});
			command = '';
		}	
	})

	$("#send").click(function(){
		var x = $("#x").val();
		var y = $("#y").val();
		var z = $("#z").val();
		$.post('http://'+ip+'/coord',{'x':x,'y':y,'z':z});
		$.post('http://'+ip+'/command',{'command':'1 2'});
	})

	$("#button_default").click(function(){
		$.post('http://'+ip+'/command',{'command':'default'})
	})

	$("#stop_button").click(function(){
		$.post('http://'+ip+'/command',{'command':'stop'});
	})

	$("#visual").click(function(){
		$.post('http://'+ip+'/visual',{'1':'1'});	
	})
})