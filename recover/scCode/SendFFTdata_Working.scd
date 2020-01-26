/*
FFT study

Usefull Classes:
-FFT : PV_ChainUGen
-PackFFT
-PV_ChainUGen: provide convenient ways to process audio in the frequency domain
-UnpackFFT
-Demand

Aris Bezas 130112 Igoumeninja
130117 Meeting with IZ
*/


~rate = 0.04;
~intensity = 1;
~fftbuf = Buffer.alloc(Server.default, 1024);
~synthdef = SynthDef(\fft, { | in = 8, buf = 0 |	FFT(buf, SoundIn.ar(0));}).add;
~fftSyth = Synth(\fft, [\in, 8, \buf, ~fftbuf.bufnum],Server.default);

//object.onStart({ this.notify(\synthStarted); });
//object.rsyncs({
(
{
	var magnitudes, imaginary, real;
	loop {
		~fftbuf.getn(0, ~fftbuf.numFrames,
		{ | buf |
				#real, imaginary = buf.clump(2).flop;
				magnitudes = Complex(Signal.newFrom(real), Signal.newFrom(imaginary)).magnitude;
				//magnitudes.postln;
				magnitudes = (1 + magnitudes).log10.clip(0, 1) * ~intensity;
				NetAddr("127.0.0.1", 12345).sendMsg("/fftData", *magnitudes)
				//OF.mlab('fftData', *magnitudes);

				//dependants do: _.update(index, buf, magnitudes);
				//index = index + 1;
		});
		~rate.wait;
	};
}.fork
)