NetAddr.langPort;
NetAddr.localAddr;

thisProcess.openUDPPort(46100); // attempt to open 46100
thisProcess.openPorts;        // list all open ports

~scNetAddr = NetAddr.new("127.0.0.1", 46100);
(
~fftTaskResp = OSCFunc({
	arg msg, time, addr, recvPort;
	if (msg[1] == 0, { ~fftTask.stop; }, {~fftTask.start; });
	[msg, time, addr, recvPort].postln; }, '/startFFT', ~scNetAddr);
)
~fftTaskResp.free;    // remove the OSCFunc when you are done.



f = OSCFunc({ arg msg, time, addr, recvPort; [msg, t,ime, addr, recvPort].postln; }, '/test', n);
o.free;    // remove the OSCFunc when you are done.

b = NetAddr.new("127.0.0.1", 46100);    // create the NetAddr
b.sendMsg("/startFFT");    // send the application the message "hello" with the parameter "there, 