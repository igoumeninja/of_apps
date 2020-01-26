/*
This class is used as a startup file

Aris Bezas Cardiff 140326

~mySendFFTdata.changeIntensity(1)
*/

Startup_The_God_Article_001 {

	*initClass {
		StartUp add: {
			this.startupTheGodArticle;
		}
	}

	*startupTheGodArticle {
		Task({
			if (not(Server.default.serverRunning)) { Server.default.boot };
			Server.default.doWhenBooted {
				~reactGUI = GUI_react.new;
				0.04.wait;
				~reactGUI.create;
				0.04.wait;
				~routeArduinoValues = RouteArduinoValues.new;
				0.04.wait;
				~makeResponders = MakeResponders.new;
				0.04.wait;
				~makeResponders.all;

			};
		}).play;
	}

}