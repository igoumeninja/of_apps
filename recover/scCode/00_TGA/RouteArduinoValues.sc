/*
Aris Bezas Mon, 15 05 2014 @ Cardiff
a = RouteArduinoValues.new
OSCFunc.trace(true)
OSCFunc.trace(false)
a.init
a.start
a.init
*/

RouteArduinoValues {
	classvar default;
	*default {
		if (default.isNil) { default = this.new };
		^default;
	}
	*new {
		^super.new.init();
	}
	init {
		~ofPort = NetAddr("127.0.0.1", 12345);
		~hole1D = 0;~hole1U = 100;
		~hole2D = 0;~hole2U = 100;
		~hole3D = 0;~hole3U = 100;
		~hole4D = 0;~hole4U = 100;
		~hole5D = 0;~hole5U = 100;
		~hole6D = 0;~hole6U = 100;
		~hole7D = 0;~hole7U = 100;
		~airD = 0;	~airU = 100;

	}
	start {
		~arduinoResponder.remove;
		~arduinoResponder = OSCresponderNode(nil, '/arduinoData',{
			arg time,responder,msg;
			~arduinoArray = msg.asString.split($,);
			//~arduinoArray.size.postln;
			if ( ~arduinoArray.size == 9 ,
			    {
					//~arduinoArray = msg.asString.split($,);
					~ofPort.sendMsg("/Arduino/Hole1",~arduinoArray[1].asFloat.linlin(~hole1D,~hole1U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Hole2",~arduinoArray[2].asFloat.linlin(~hole2D,~hole2U,0.0001, 0.999));
					~ofPort.sendMsg("/Arduino/Hole3",~arduinoArray[3].asFloat.linlin(~hole3D,~hole3U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Hole4",~arduinoArray[4].asFloat.linlin(~hole4D,~hole4U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Hole5",~arduinoArray[5].asFloat.linlin(~hole5D,~hole5U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Hole6",~arduinoArray[6].asFloat.linlin(~hole6D,~hole6U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Hole7",~arduinoArray[7].asFloat.linlin(~hole7D,~hole7U,0.0001, 0.9999));
					~ofPort.sendMsg("/Arduino/Pressure",~arduinoArray[8].asFloat.linlin(~airD,~airU ,0.0001, 0.9999));
				},    // true function
				    { "Message with Error syntax".postln }    // false function
			);

		}).add;
	}
	test {
		~arduinoResponder.remove;
		~arduinoResponder = OSCresponderNode(nil, '/arduinoData',{
			arg time,responder,msg;
			~arduinoArray = msg.asString.split($,).postln;
		}).add;
	}
	stop {
		~arduinoResponder.remove;
	}
}

