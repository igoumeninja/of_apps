NetAddr.langPort;
NetAddr.localAddr;

thisProcess.openUDPPort(1121); // attempt to open 1121
thisProcess.openPorts;        // list all open ports

~netAddr = NetAddr.new("127.0.0.1", 57120);
(
~fftTaskResp = OSCFunc({
	arg msg, time, addr, recvPort;
	if (msg[1] == 0, { ~fftTask.stop; }, {~fftTask.start; });
	[msg, time, addr, recvPort].postln; }, '/startFFT');
)
~fftTaskResp.free;    // remove the OSCFunc when you are done.



f = OSCFunc({ arg msg, time, addr, recvPort; [msg, time, addr, recvPort].postln; }, '/test', n);
o.free;    // remove the OSCFunc when you are done.

b = NetAddr.new("127.0.0.1", 57120);    // create the NetAddr
b.sendMsg("/startFFT", "there");    // send the application the message "hello" with the parameter "there