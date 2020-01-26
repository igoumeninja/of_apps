/*
Aris Bezas Mon, 12 12 2012, 20:36
SpecCentroid for machine listening.

//Class implementation
c = SendSpecCentroid.new
c.dump
c.start
c.impulseRate(1)
c.stop;
*/


SendSpecCentroid {
	classvar default;
	var <synthListenCentroid;	//	the listening Onsets process
	var <chan = 0;			//	the channel that we detect
	var <responders;			//	responders

	*default {
		if (default.isNil) { default = this.new };  // create default
		^default;
	}

	*new { |chan|
		^super.new.init(chan);
	}
	init { |argChan|
		"-SendSpecCentroid".postln;
		chan = argChan;
	}

	start	{
		if (not(Server.default.serverRunning)) { Server.default.boot };
		Server.default.doWhenBooted {
			 synthListenCentroid = SynthDef(\centroidSynth, { |thres = 1, impulseRate = 24|
				var sig, chain, onsets, pips,buf, centroid, trig;
				trig = Impulse.kr(impulseRate);
				buf = Buffer.alloc(Server.default, 512);
				sig = SoundIn.ar(chan);
				chain = FFT(buf, sig);
				centroid = SpecCentroid.kr(chain);
				SendTrig.kr(trig, 3, centroid);
			}).play(Server.default);
		};

	}
	stop	{
		synthListenCentroid.free;
	}
	impulseRate	{ |impulseRateArg|
		synthListenCentroid.set(\impulseRate, impulseRateArg);
	}
}

