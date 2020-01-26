/*
Onset Aris Bezas Mon, 12 12 2012, 20:36
*/

SendOnsets {
	classvar default;
	var <synthListenOnsets;			// the listening Onsets process
	var <chan = 0;		// the channel that we detect

	*default {
		if (default.isNil) { default = this.new };  // create default
		^default;
	}

	*new { |chan|
		^super.new.init(chan);
	}
	init { |argChan|
		"-SendOnsets".postln;
		chan = argChan;
	}
	start	{
		if (not(Server.default.serverRunning)) { Server.default.boot };
		Server.default.doWhenBooted {
			 synthListenOnsets = SynthDef(\onsetSynth, { |thres = 1|
				var sig, chain, onsets, pips,buf;
				buf = Buffer.alloc(Server.default, 512);
				sig = SoundIn.ar(chan);
				chain = FFT(buf, sig);
				thres.postln;
				onsets = Onsets.kr(chain, thres, \rcomplex);
				SendReply.kr(onsets, \onset);
			}).play(Server.default);
		};
	}
	stop	{
		synthListenOnsets.free;
	}
	threshold		{ |threshold|
		synthListenOnsets.set(\thres, threshold);
	}
}

