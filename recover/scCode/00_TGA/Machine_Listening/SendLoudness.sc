/*
Aris Bezas Mon, 16 12 2012, 19:36
Loudness for machine listening.

e = SendLoudness.new
e.start
e.impulseRate(1)
e.stop
*/

SendLoudness {
	classvar default;
	var <synthListenLoudness;			// the listening Onsets process
	var <chan = 0;		// the channel that we detect

	*default {
		if (default.isNil) { default = this.new };  // create default
		^default;
	}

	*new { |chan|
		^super.new.init(chan);
	}
	init { |argChan|
		"-SendLoudness".postln;
		chan = argChan;
	}

	start	{
		if (not(Server.default.serverRunning)) { Server.default.boot };
		Server.default.doWhenBooted {
			 synthListenLoudness = SynthDef(\loudness, { |thres = 1, impulseRate = 24|
				var sig, chain, onsets, pips,buf, loudness, trig;
				trig = Impulse.kr(impulseRate);
				buf = Buffer.alloc(Server.default, 512);
				sig = SoundIn.ar(chan);
				chain = FFT(buf, sig);
				loudness=Loudness.kr(chain);
				SendTrig.kr(trig, 5, loudness);
			}).play(Server.default);
		};

	}
	stop	{
		synthListenLoudness.free;
	}
	impulseRate	{ |impulseRateArg|
		synthListenLoudness.set(\impulseRate, impulseRateArg);
	}
}

