o = OSCresponderNode(nil, '/test', { |t, r, msg| msg.postln }).add;

m = NetAddr("127.0.0.1", 12345); // the url should be the one of computer of app 1
m.sendMsg("/background");
