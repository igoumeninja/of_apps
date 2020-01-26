/*
SpecFlatness for machine listening. Aris Bezas Mon, 15 12 2012, 20:36
*/

SendSpecFlatness {
	classvar default;
	var <synthListenSpecFlatness;	// the listening Onsets process
	var <chan = 0;				// the channel that we detect

	*default {
		if (default.isNil) { default = this.new };  // create default
		^default;
	}

	*new { |chan|
		^super.new.init(chan);
	}

	init { |argChan|
		"-SendSpecFlatness".postln;
		chan = argChan;
	}

	start	{
		if (not(Server.default.serverRunning)) { Server.default.boot };
		Server.default.doWhenBooted {
			 synthListenSpecFlatness = SynthDef(\specFlatness, { |thres = 1, impulseRate = 24|
				var sig, chain, onsets, pips,buf, flat, flatdb, flatdbsquish, trig;
				trig = Impulse.kr(impulseRate);
				buf = Buffer.alloc(Server.default, 512);
				sig = SoundIn.ar(chan);
				chain = FFT(buf, sig);
				flat = SpecFlatness.kr(chain);
				flatdb = 10 * flat.log; // Convert to decibels
				flatdbsquish = LinLin.kr(flatdb, -45, -1.6, 0, 1).max(-10); // Rescale db E {0,1}
				SendTrig.kr(trig, 4, flatdbsquish);
			}).play(Server.default);
		};
	}

	stop	{
		synthListenSpecFlatness.free;
	}

	impulseRate	{ |impulseRateArg|
		synthListenSpecFlatness.set(\impulseRate, impulseRateArg);
	}
}

