$(function(){

	var ip = '127.0.0.1:5000';
	var mode = 1;

	$("#connect").click(function(){
		var com_port = $("#com").val();
		$.post('http://'+ip+'/connect',{'com':com_port});
		$("#log").append("Trying connecting");
	})

	$("#custom_command").click(function(){
		var command = $("#custom_command_text").val();
		$("#custom_command_text").val("");
		$("#log").append("-- "+command+"\n");
		if (command != ''){
			$.post('http://'+ip+'/command',{'command':command});
			command = '';
		}	
	})

	$("#xyz_coord").click(function(){
		mode = 1;
		$("#coord_1").text("X");
		$("#coord_2").text("Y");
		$("#coord_3").text("Z");
	})

	$("#some_coord").click(function(){
		mode = 2;
		$("#coord_1").text("A");
		$("#coord_2").text("B");
		$("#coord_3").text("C");
	})

})