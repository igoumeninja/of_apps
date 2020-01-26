// Setup Graphical User Interafce for REACT project
// Aris Bezas 140506

GUI_react {
	classvar default;
	var <server;
	var window, text1,text2,text3,text4,text5,but00,but01,but03,but1,but2,but3,but4,but5,numBox1,numBox2,numBox3,numBox4,numBox5,numBox6,numBox7,numBox8,numBox9,numBox10,numBox11,numBox12,numBox13,numBox14,numBox15,numBox16,numBox17,numBox18,numBox19;
	*default {
		if (default.isNil) { default = this.new };
		^default;
	}
	*new { | server, addr, chan = 0|
		^super.new.init(server, addr, chan);
	}
	init { | argServer, argAddr, argChan = 0|
		"-Create GUI".postln;
		server = argServer ?? { Server.default };
	}
	create	{
		if (not(server.serverRunning)) { server.boot };
		server.doWhenBooted {
			window = Window.new("REACT - The God Article", Rect(200,200,500,500));

			// TEST OSC
			but00 = Button(window, Rect(350,10,120,20)).states_([
				["Post all OSC",Color.black,Color.white],
				["STOP Post",Color.black,Color.white]
			]);
			but00.action = { if ( but00.value.asBoolean,
				{ OSCFunc.trace(true); },
				{ OSCFunc.trace(false); }
			)};

			// OPEN MY OPENFRAMEWORK APPLICATION
			but01 = Button(window, Rect(350,40,120,20)).states_([
				["Open Test App",Color.black,Color.white],
				["Open App",Color.black,Color.white]
			]);
			but01.action = { if ( but01.value.asBoolean,
				{ ("open"+Platform.resourceDir++"/Apps/ofApp_140520.app").unixCmd; },
				{ "- Close the App manually".postln;}
			)};

			// LIST SERIAL DEVICES
			but03 = Button(window, Rect(350,70,120,20)).states_([
				["List Serial Devices",Color.black,Color.white],
				["List Serial Devices",Color.black,Color.white]
			]);
			but03.action = { if ( but01.value.asBoolean,
				{ SerialPort.listDevices; },
				{ SerialPort.listDevices;}
			)};

			// SERIAL COMMUNICATION
			text1 = StaticText(window, Rect(10, 10, 120, 20));
			text1.string = "Choose Serial Port:";
			but1 = Button(window, Rect(140,10,40,20)).states_([
				["[0]",Color.black,Color.white],
				["[0]",Color.black,Color.white]
			]);
			but1.action = { if ( but1.value.asBoolean,
				{ ("open"+Platform.resourceDir++"/Apps/Device_0.app").unixCmd; },
				{ "- Close the App manually".postln; }
			)};
			but2 = Button(window, Rect(200,10,40,20)).states_([
				["[1]",Color.black,Color.white],
				["[1]",Color.black,Color.white]
			]);
			but2.action = { if ( but2.value.asBoolean,
				{ ("open"+Platform.resourceDir++"/Apps/Device_1.app").unixCmd; },
				{ "- Close the App manually" }
			)};
			// DEFINE INPUT DEVICE
			text2 = StaticText(window, Rect(10, 40, 120, 20));
			text2.string = "Define Input Device:";
			numBox1 = NumberBox(window, Rect(140, 40, 30, 20));
			numBox1.value = 8;
			numBox1.action = {
				~sendAmpFreq = SendAmpFreq.new(chan: numBox1.value);
				~sendFFTdata = SendFFTdata.new(numBox1.value);
				~sendLoudness = SendLoudness.new(numBox1.value);
				~sendOnsets = SendOnsets.new(numBox1.value);
				~sendSpecCentroid = SendSpecCentroid.new(numBox1.value);
				~sendSpecFlatness = SendSpecFlatness.new(numBox1.value);

				"Input Device set at: ".post;
				numBox1.value.postln
			};
			// SEND ARDUINO DATA
			text3 = StaticText(window, Rect(10, 70, 120, 20));
			text3.string = "Send Arduino Data:";
			but3 = Button(window, Rect(140,70,40,20)).states_([
				["Start",Color.black,Color.white],
				["Stop",Color.white,Color.black]
			]);
			but3.action = { if ( but3.value.asBoolean,
				{
					~routeArduinoValues.start;
					"Send OSC msg with Arduino Data to port: 12345".postln;
				},
				{
					~routeArduinoValues.stop;
					"Stop Sending OSC.".postln;
				}
			)};

			but4 = Button(window, Rect(200,70,40,20)).states_([
				["Test",Color.black,Color.white],
				["Stop",Color.white,Color.black]
			]);
			but4.action = { if ( but4.value.asBoolean,
				{
					~routeArduinoValues.test;
					"Send OSC msg with Arduino Data to port: 12345".postln;
				},
				{
					~routeArduinoValues.stop;
					"Stop Sending OSC.".postln;
				}
			)};

			// SEND AUDIO DESCRIPTORS
			text4 = StaticText(window, Rect(10, 100, 140, 20));
			text4.string = "Send Audio Descriptors:";
			but5 = Button(window, Rect(160,100,40,20)).states_([
				["Start",Color.black,Color.white],
				["Stop",Color.white,Color.black]
			]);
			but5.action = { if ( but5.value.asBoolean,
				{

					~sendAmpFreq.start;
					~sendFFTdata.start;
					~sendLoudness.start;
					~sendOnsets.start;
					~sendSpecCentroid.start;
					~sendSpecFlatness.start;

					"Send OSC msg with Audio Descriptors to port: 12345".postln;
				},
				{
					"Stop Sending OSC.".postln;
				}
			)};

			// MAP ARDUINO VALUES
			text5 = StaticText(window, Rect(0, 130, 130, 20));
			text5.background = Color.gray;
			text5.string = "  Map Sensor Values";

			StaticText(window, Rect(10, 170, 140, 20)).string = "hole1:    from";
			numBox2 = NumberBox(window, Rect(100, 170, 40, 20));
			numBox2.value = 30;
			numBox2.action = {~hole1D = numBox2.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 170, 140, 20)).string = "to";
			numBox3 = NumberBox(window, Rect(180, 170, 40, 20));
			numBox3.value = 60;
			numBox3.action = {~hole1U = numBox3.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 200, 140, 20)).string = "hole2:    from";
			numBox4 = NumberBox(window, Rect(100, 200, 40, 20));
			numBox4.value = 30;
			numBox4.action = {~hole2D = numBox4.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 200, 140, 20)).string = "to";
			numBox5 = NumberBox(window, Rect(180, 200, 40, 20));
			numBox5.value = 60;
			numBox5.action = {~hole2U = numBox5.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 230, 140, 20)).string = "hole3:    from";
			numBox6 = NumberBox(window, Rect(100, 230, 40, 20));
			numBox6.value = 30;
			numBox6.action = {~hole3D = numBox6.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 230, 140, 20)).string = "to";
			numBox7 = NumberBox(window, Rect(180, 230, 40, 20));
			numBox7.value = 60;
			numBox7.action = {~hole3U = numBox7.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 260, 140, 20)).string = "hole4:    from";
			numBox8 = NumberBox(window, Rect(100, 260, 40, 20));
			numBox8.value = 30;
			numBox8.action = {~hole4D = numBox8.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 260, 140, 20)).string = "to";
			numBox9 = NumberBox(window, Rect(180, 260, 40, 20));
			numBox9.value = 60;
			numBox9.action = {~hole4U = numBox9.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 290, 140, 20)).string = "hole5:    from";
			numBox10 = NumberBox(window, Rect(100, 290, 40, 20));
			numBox10.value = 30;
			numBox10.action = {~hole5D = numBox10.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 290, 140, 20)).string = "to";
			numBox11 = NumberBox(window, Rect(180, 290, 40, 20));
			numBox11.value = 60;
			numBox11.action = {~hole5U = numBox11.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 320, 140, 20)).string = "hole6:    from";
			numBox12 = NumberBox(window, Rect(100, 320, 40, 20));
			numBox12.value = 30;
			numBox12.action = {~hole6D = numBox12.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 320, 140, 20)).string = "to";
			numBox13 = NumberBox(window, Rect(180, 320, 40, 20));
			numBox13.value = 60;
			numBox13.action = {~hole6U = numBox13.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 350, 140, 20)).string = "hole5:    from";
			numBox14 = NumberBox(window, Rect(100, 350, 40, 20));
			numBox14.value = 30;
			numBox14.action = {~hole7D = numBox14.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 350, 140, 20)).string = "to";
			numBox15 = NumberBox(window, Rect(180, 350, 40, 20));
			numBox15.value = 60;
			numBox15.action = {~hole7U = numBox15.value;~routeArduinoValues.start;};

			StaticText(window, Rect(10, 380, 140, 20)).string = "Air Pressure:";
			numBox16 = NumberBox(window, Rect(100, 380, 40, 20));
			numBox16.value = 30;
			numBox16.action = {~airD = numBox16.value;~routeArduinoValues.start;};
			StaticText(window, Rect(150, 380, 140, 20)).string = "to";
			numBox17 = NumberBox(window, Rect(180, 380, 40, 20));
			numBox17.value = 60;
			numBox17.action = {~airU = numBox17.value;~routeArduinoValues.start;};

			window.front;
		};
	}
	stop	{
	}
}
